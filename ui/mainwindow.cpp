#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddTaskDialog.h"
#include "LoginWindow.h"

#include <QMessageBox>
#include <QDir>
#include <QCloseEvent>
#include <QDate>
#include <QBrush>
#include <QColor>
#include <QFile>
#include <QSettings>
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>

// ================= TIME FORMAT =================
QString formatTime(qint64 seconds)
{
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;

    return QString("%1h %2m %3s")
        .arg(h)
        .arg(m)
        .arg(s);
}

// ================= THEME =================
QString getThemeName()
{
    QSettings settings("PlannerGUI", "PlannerGUI");
    QString path = settings.value("theme").toString();

    if (path.contains("dark")) return "dark";
    if (path.contains("blue")) return "blue";
    if (path.contains("pastel")) return "pastel";

    return "light";
}

// ================= CONSTRUCTOR =================
MainWindow::MainWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentUser(username)
{
    ui->setupUi(this);

    // ================= WINDOW SIZE =================
    resize(1200, 700);

    // ================= TABLE =================
    ui->taskTable->setColumnCount(7);

    ui->taskTable->setHorizontalHeaderLabels({
        "",
        "Done",
        "Title",
        "Due Date",
        "Priority",
        "Time",
        "Control"
    });

    ui->taskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->taskTable->verticalHeader()->setVisible(false);

    ui->taskTable->verticalHeader()->setDefaultSectionSize(45);

    ui->taskTable->setColumnWidth(0, 70);
    ui->taskTable->setColumnWidth(1, 70);
    ui->taskTable->setColumnWidth(2, 260);
    ui->taskTable->setColumnWidth(3, 140);
    ui->taskTable->setColumnWidth(4, 100);
    ui->taskTable->setColumnWidth(5, 140);
    ui->taskTable->setColumnWidth(6, 260);

    ui->taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->taskTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ================= THEME =================
    QSettings settings("PlannerGUI", "PlannerGUI");

    QString savedTheme =
        settings.value("theme", ":/themes/light.qss").toString();

    applyTheme(savedTheme);

    connect(ui->actionThemesBlue, &QAction::triggered,
            this, [this]() {
                applyTheme(":/new/prefix1/themes/blue.qss");
            });

    connect(ui->actionThemesDark, &QAction::triggered,
            this, [this]() {
                applyTheme(":/new/prefix1/themes/dark.qss");
            });

    connect(ui->actionThemesLight, &QAction::triggered,
            this, [this]() {
                applyTheme(":/new/prefix1/themes/light.qss");
            });

    connect(ui->actionThemesPastel, &QAction::triggered,
            this, [this]() {
                applyTheme(":/new/prefix1/themes/pastel.qss");
            });

    // ================= LOAD =================
    QString basePath =
        QCoreApplication::applicationDirPath()
        + "/data/users/" + currentUser + "/";

    QDir().mkpath(basePath);

    planner.loadFromBinaryFile(basePath + "tasks.dat");

    // ================= SORT =================
    planner.sortByPriority();

    // ================= TIMER =================
    liveTimer = new QTimer(this);

    connect(liveTimer, &QTimer::timeout,
            this, [this]() {
                updateTable();
            });

    liveTimer->start(1000);

    updateLegend();
    updateTable();
}

// ================= DESTRUCTOR =================
MainWindow::~MainWindow()
{
    delete ui;
}

// ================= SAVE =================
void MainWindow::saveTasks()
{
    QString basePath =
        QCoreApplication::applicationDirPath()
        + "/data/users/" + currentUser + "/";

    planner.saveToBinaryFile(basePath + "tasks.dat");
}

// ================= UPDATE TABLE =================
// ================= UPDATE TABLE =================
void MainWindow::updateTable()
{
    ui->taskTable->blockSignals(true);

    ui->taskTable->setRowCount(0);

    const QVector<Task> &tasks = planner.getTasks();

    int dateFilter = ui->dateFilterBox->currentIndex();
    int priorityFilter = ui->priorityFilterBox->currentIndex();

    QDate today = QDate::currentDate();

    QString theme = getThemeName();

    // ================= SUMMARY =================
    int visibleTotal = 0;
    int visibleCompleted = 0;
    int prioritySum = 0;
    qint64 timeSum = 0;

    // ================= LOOP =================
    for (int i = 0; i < tasks.size(); ++i) {

        const Task &t = tasks[i];

        // ================= FILTERING =================
        bool show = true;

        // PRIORITY FILTER
        if (priorityFilter > 0) {

            show &= (t.getPriority() >= priorityFilter);
        }

        // DATE FILTER
        switch (dateFilter) {

        case 1:
            show &= (t.getDueDate() == today);
            break;

        case 2:
            show &= (t.getDueDate() < today);
            break;

        case 3:
            show &= (t.getDueDate() > today);
            break;

        default:
            break;
        }

        if (!show)
            continue;

        // ================= SUMMARY =================
        visibleTotal++;

        if (t.isCompleted())
            visibleCompleted++;

        prioritySum += t.getPriority();

        timeSum += t.getCurrentTimeSpent();

        // ================= NEW ROW =================
        int row = ui->taskTable->rowCount();

        ui->taskTable->insertRow(row);

        // ================= ITEMS =================
        QTableWidgetItem *barItem =
            new QTableWidgetItem();

        QTableWidgetItem *checkItem =
            new QTableWidgetItem();

        QTableWidgetItem *titleItem =
            new QTableWidgetItem(t.getTitle());

        QTableWidgetItem *dateItem =
            new QTableWidgetItem(
                t.getDueDate().toString("yyyy-MM-dd"));

        QTableWidgetItem *priorityItem =
            new QTableWidgetItem(
                QString::number(t.getPriority()));

        QTableWidgetItem *timeItem =
            new QTableWidgetItem(
                formatTime(t.getCurrentTimeSpent()));

        // ================= TIMER ICON =================
        if (t.isTimerRunning()) {

            timeItem->setText(
                timeItem->text() + " ⏱");
        }

        // ================= CHECKBOX =================
        checkItem->setFlags(
            Qt::ItemIsUserCheckable |
            Qt::ItemIsEnabled);

        checkItem->setCheckState(
            t.isCompleted()
                ? Qt::Checked
                : Qt::Unchecked);

        // ================= REAL INDEX =================
        barItem->setData(Qt::UserRole, i);
        checkItem->setData(Qt::UserRole, i);
        titleItem->setData(Qt::UserRole, i);
        dateItem->setData(Qt::UserRole, i);
        priorityItem->setData(Qt::UserRole, i);
        timeItem->setData(Qt::UserRole, i);

        // ================= COLORS =================
        QColor priorityLow;
        QColor priorityMedium;
        QColor priorityHigh;

        QColor dateOverdue;
        QColor dateToday;
        QColor dateNormal;

        if (theme == "dark") {

            priorityLow = QColor("#6C8CFF");
            priorityMedium = QColor("#FFD166");
            priorityHigh = QColor("#FF6B6B");

            dateOverdue = QColor("#FF4D4D");
            dateToday = QColor("#FFC857");
            dateNormal = QColor("#AAAAAA");
        }
        else if (theme == "blue") {

            priorityLow = QColor("#4A90E2");
            priorityMedium = QColor("#5DADE2");
            priorityHigh = QColor("#E74C3C");

            dateOverdue = QColor("#C0392B");
            dateToday = QColor("#F39C12");
            dateNormal = QColor("#7FB3D5");
        }
        else if (theme == "pastel") {

            priorityLow = QColor("#A3C4F3");
            priorityMedium = QColor("#FFD6A5");
            priorityHigh = QColor("#FFADAD");

            dateOverdue = QColor("#FF8B94");
            dateToday = QColor("#FFD6A5");
            dateNormal = QColor("#BDB2FF");
        }
        else {

            priorityLow = QColor("#6B8AFD");
            priorityMedium = QColor("#FFB84D");
            priorityHigh = QColor("#FF7A7A");

            dateOverdue = QColor("#D63031");
            dateToday = QColor("#F39C12");
            dateNormal = QColor("#555555");
        }

        // ================= PRIORITY COLOR =================
        QColor priorityColor;

        if (t.getPriority() <= 2)
            priorityColor = priorityLow;

        else if (t.getPriority() == 3)
            priorityColor = priorityMedium;

        else
            priorityColor = priorityHigh;

        // ================= DATE COLOR =================
        bool isOverdue = t.getDueDate() < today;
        bool isToday = t.getDueDate() == today;

        QColor dateColor;

        if (isOverdue)
            dateColor = dateOverdue;

        else if (isToday)
            dateColor = dateToday;

        else
            dateColor = dateNormal;

        // ================= GRADIENT =================
        QLinearGradient gradient(0, 0, 100, 0);

        gradient.setColorAt(0, dateColor);
        gradient.setColorAt(1, priorityColor);

        barItem->setBackground(QBrush(gradient));

        // ================= TEXT COLOR =================
        QColor textColor =
            (theme == "dark")
                ? QColor("#EAEAF0")
                : QColor("#1A1A1A");

        titleItem->setData(Qt::ForegroundRole, textColor);
        dateItem->setData(Qt::ForegroundRole, textColor);
        priorityItem->setData(Qt::ForegroundRole, textColor);
        timeItem->setData(Qt::ForegroundRole, textColor);

        // ================= COMPLETED STYLE =================
        if (t.isCompleted()) {

            QFont font = titleItem->font();

            font.setStrikeOut(true);

            titleItem->setFont(font);
            dateItem->setFont(font);
            priorityItem->setFont(font);
            timeItem->setFont(font);

            QColor doneColor =
                (theme == "dark")
                    ? QColor("#777777")
                    : QColor("#999999");

            titleItem->setForeground(doneColor);
            dateItem->setForeground(doneColor);
            priorityItem->setForeground(doneColor);
            timeItem->setForeground(doneColor);

            barItem->setBackground(QColor("#CCCCCC"));
        }

        // ================= TIMER BUTTONS =================
        QWidget *controlWidget = new QWidget();

        QHBoxLayout *layout =
            new QHBoxLayout(controlWidget);

        layout->setContentsMargins(0,0,0,0);

        QPushButton *startBtn =
            new QPushButton("▶");

        QPushButton *pauseBtn =
            new QPushButton("⏸");

        startBtn->setProperty("row", i);
        pauseBtn->setProperty("row", i);

        // ================= START =================
        connect(startBtn, &QPushButton::clicked,
                this, [this, startBtn]() {

                    int row =
                        startBtn->property("row").toInt();

                    planner.startTaskTimer(row);

                    saveTasks();

                    updateTable();
                });

        // ================= STOP =================
        connect(pauseBtn, &QPushButton::clicked,
                this, [this, pauseBtn]() {

                    int row =
                        pauseBtn->property("row").toInt();

                    planner.stopTaskTimer(row);

                    saveTasks();

                    updateTable();
                });

        layout->addWidget(startBtn);
        layout->addWidget(pauseBtn);

        // ================= ADD ITEMS =================
        ui->taskTable->setItem(row, 0, barItem);
        ui->taskTable->setItem(row, 1, checkItem);
        ui->taskTable->setItem(row, 2, titleItem);
        ui->taskTable->setItem(row, 3, dateItem);
        ui->taskTable->setItem(row, 4, priorityItem);
        ui->taskTable->setItem(row, 5, timeItem);

        ui->taskTable->setCellWidget(
            row,
            6,
            controlWidget);
    }

    // ================= SUMMARY =================
    double avgPriority =
        visibleTotal == 0
            ? 0
            : static_cast<double>(prioritySum)
                  / visibleTotal;

    qint64 avgTime =
        visibleTotal == 0
            ? 0
            : timeSum / visibleTotal;

    QString avgTimeStr =
        formatTime(avgTime);

    ui->summaryLabel->setText(

        "Total: "
        + QString::number(visibleTotal)

        + " | Completed: "
        + QString::number(visibleCompleted)

        + " | Avg priority: "
        + QString::number(avgPriority, 'f', 1)

        + " | ⏱ Avg time: "
        + avgTimeStr
        );

    ui->taskTable->blockSignals(false);
}

// ================= ADD =================
void MainWindow::on_addButton_clicked()
{
    AddTaskDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {

        planner.addTask(dialog.getTask());

        saveTasks();

        updateTable();
    }
}

// ================= EDIT =================
void MainWindow::on_editButton_clicked()
{
    int row = ui->taskTable->currentRow();

    if (row < 0) {
        QMessageBox::warning(
            this,
            "Warning",
            "Please select a task to edit");

        return;
    }

    QTableWidgetItem *item =
        ui->taskTable->item(row, 2);

    int realIndex =
        item->data(Qt::UserRole).toInt();

    Task task =
        planner.getTasks()[realIndex];

    AddTaskDialog dialog(this);

    dialog.setTask(task);

    if (dialog.exec() == QDialog::Accepted) {

        planner.updateTask(
            realIndex,
            dialog.getTask());

        saveTasks();

        updateTable();
    }
}

// ================= DELETE =================
void MainWindow::on_deleteButton_clicked()
{
    int row = ui->taskTable->currentRow();

    if (row < 0) {

        QMessageBox::warning(
            this,
            "Warning",
            "Please select a task to delete");

        return;
    }

    QTableWidgetItem *item =
        ui->taskTable->item(row, 2);

    int realIndex =
        item->data(Qt::UserRole).toInt();

    planner.removeTask(realIndex);

    saveTasks();

    updateTable();
}

// ================= CHECKBOX =================
void MainWindow::on_taskTable_itemChanged(
    QTableWidgetItem *item)
{
    if (item->column() != 1)
        return;

    int realIndex =
        item->data(Qt::UserRole).toInt();

    bool done =
        item->checkState() == Qt::Checked;

    planner.setCompleted(realIndex, done);

    saveTasks();
}

// ================= LOGOUT =================
void MainWindow::on_logoutButton_clicked()
{
    saveTasks();

    this->close();

    LoginWindow login;

    if (login.exec() == QDialog::Accepted) {

        MainWindow *newWindow =
            new MainWindow(login.getUsername());

        newWindow->show();
    }
}

// ================= FILTERS =================
void MainWindow::on_dateFilterBox_currentIndexChanged(int)
{
    updateTable();
}

void MainWindow::on_priorityFilterBox_currentIndexChanged(int)
{
    updateTable();
}
//================= SORTING =================
void MainWindow::on_sortBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 1:
        planner.sortByPriority();
        break;

    case 2:
        planner.sortByDate();
        break;

    case 3:
        planner.sortByTitle();
        break;

    default:
        break;
    }

    updateTable();
}
// ================= CLOSE =================
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveTasks();

    event->accept();
}

// ================= THEME =================
void MainWindow::applyTheme(const QString &themePath)
{
    QFile file(themePath);

    if (!file.open(QFile::ReadOnly)) {

        qDebug() << "Cannot open theme:"
                 << themePath;

        return;
    }

    QString style = file.readAll();

    qApp->setStyleSheet(style);

    QSettings settings("PlannerGUI", "PlannerGUI");

    settings.setValue("theme", themePath);

    updateLegend();

    updateTable();
}

// ================= LEGEND =================
void MainWindow::updateLegend()
{
    QString theme = getThemeName();

    QString low, medium, high, today, overdue;

    if (theme == "dark") {

        low = "#6C8CFF";
        medium = "#FFD166";
        high = "#FF6B6B";

        today = "#FFC857";
        overdue = "#FF4D4D";
    }
    else if (theme == "blue") {

        low = "#4A90E2";
        medium = "#5DADE2";
        high = "#E74C3C";

        today = "#F39C12";
        overdue = "#C0392B";
    }
    else if (theme == "pastel") {

        low = "#A3C4F3";
        medium = "#FFD6A5";
        high = "#FFADAD";

        today = "#FFD6A5";
        overdue = "#FF8B94";
    }
    else {

        low = "#6B8AFD";
        medium = "#FFB84D";
        high = "#FF7A7A";

        today = "#F39C12";
        overdue = "#D63031";
    }

    ui->legendLabel->setText(QString(R"(

        ⏰ <span style='color:%4;'>Today</span>

        &nbsp;&nbsp;

        ⚠ <span style='color:%5;'>Overdue</span>

        &nbsp;|&nbsp;

        <span style='color:%1;'>●</span> Low

        &nbsp;&nbsp;

        <span style='color:%2;'>●</span> Medium

        &nbsp;&nbsp;

        <span style='color:%3;'>●</span> High

    )").arg(low, medium, high, today, overdue));

    ui->legendLabel->setTextFormat(Qt::RichText);
}