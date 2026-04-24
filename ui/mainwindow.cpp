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


QString formatTime(qint64 seconds)
{
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    return QString("%1h %2m").arg(h).arg(m);
}

QString getThemeName()
{
    QSettings settings("PlannerGUI", "PlannerGUI");
    QString path = settings.value("theme").toString();

    if (path.contains("dark")) return "dark";
    if (path.contains("blue")) return "blue";
    if (path.contains("pastel")) return "pastel";
    return "light";
}

QColor mix(const QColor &c1, const QColor &c2, double ratio)
{
    int r = c1.red()   * (1 - ratio) + c2.red()   * ratio;
    int g = c1.green() * (1 - ratio) + c2.green() * ratio;
    int b = c1.blue()  * (1 - ratio) + c2.blue()  * ratio;
    return QColor(r, g, b);
}
MainWindow::MainWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentUser(username)
{
    ui->setupUi(this);
    ui->taskTable->setColumnWidth(0, 100);   // цветная полоска
    ui->taskTable->setColumnWidth(1, 60);   // Done
    ui->taskTable->setColumnWidth(2, 200);  // Title
    ui->taskTable->setColumnWidth(3, 120);  // Due Date
    ui->taskTable->setColumnWidth(4, 80);   // Priority
    ui->taskTable->setColumnWidth(5, 120);  // Time
    ui->taskTable->setColumnWidth(6, 260);  // Control (кнопки)
    QSettings settings("PlannerGUI", "PlannerGUI");
    QString savedTheme = settings.value("theme", ":/themes/light.qss").toString();
    applyTheme(savedTheme);
    connect(ui->actionThemesBlue, &QAction::triggered, this, [this]() {
        applyTheme(":/new/prefix1/themes/blue.qss");
    });

    connect(ui->actionThemesDark, &QAction::triggered, this, [this](){
        applyTheme(":/new/prefix1/themes/dark.qss");
    });

    connect(ui->actionThemesLight, &QAction::triggered, this, [this](){
        applyTheme(":/new/prefix1/themes/light.qss");
    });

    connect(ui->actionThemesPastel, &QAction::triggered, this, [this](){
        applyTheme(":/new/prefix1/themes/pastel.qss");
    });

    ui->taskTable->setColumnCount(7);
    ui->taskTable->setHorizontalHeaderLabels({
        "", "Done", "Title", "Due Date", "Priority", "Time", "Control" });
    ui->taskTable->horizontalHeader()->setStretchLastSection(false);
    ui->taskTable->verticalHeader()->setVisible(false);
    ui->taskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->taskTable->verticalHeader()->setDefaultSectionSize(45);
    ui->taskTable->setColumnWidth(0, 70);   // цветная полоска
    ui->taskTable->setColumnWidth(1, 60);   // Done
    ui->taskTable->setColumnWidth(2, 200);  // Title
    ui->taskTable->setColumnWidth(3, 120);  // Due Date
    ui->taskTable->setColumnWidth(4, 80);   // Priority
    ui->taskTable->setColumnWidth(5, 100);  // Time
    ui->taskTable->setColumnWidth(6, 200);  // Control (кнопки)
    ui->taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->taskTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->taskTable->setSortingEnabled(true);
    updateLegend();
    updateSummary(planner.getTasks());
    liveTimer = new QTimer(this);

    connect(liveTimer, &QTimer::timeout, this, [this]() {
        updateTable();
    });

    liveTimer->start(1000);


    QString basePath = QCoreApplication::applicationDirPath()
                       + "/data/users/" + currentUser + "/";

    QDir().mkpath(basePath);
    planner.loadFromBinaryFile(basePath + "tasks.dat");

    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{
    ui->taskTable->blockSignals(true);

    ui->taskTable->setSortingEnabled(false);
    ui->taskTable->setRowCount(0);

    const QVector<Task> &tasks = planner.getTasks();

    int dateFilter = ui->dateFilterBox->currentIndex();
    int priorityFilter = ui->priorityFilterBox->currentIndex();
    QDate today = QDate::currentDate();

    QString theme = getThemeName();

    // 🔥 SUMMARY COUNTERS
    int visibleTotal = 0;
    int visibleCompleted = 0;
    int prioritySum = 0; // 🔥 добавили
    qint64 timeSum = 0;

    for (int i = 0; i < tasks.size(); ++i) {

        const Task &t = tasks[i];
        bool show = true;

        // ===== FILTERS =====
        switch (dateFilter) {
        case 1: show &= (t.getDueDate() == today); break;
        case 2: show &= (t.getDueDate() < today); break;
        case 3: show &= (t.getDueDate() > today); break;
        default: break;
        }

        switch (priorityFilter) {
        case 1: show &= (t.getPriority() >= 1); break;
        case 2: show &= (t.getPriority() >= 2); break;
        case 3: show &= (t.getPriority() >= 3); break;
        case 4: show &= (t.getPriority() >= 4); break;
        case 5: show &= (t.getPriority() == 5); break;
        default: break;
        }

        if (!show)
            continue;

        // 🔥 SUMMARY UPDATE
        visibleTotal++;

        if (t.isCompleted())
            visibleCompleted++;

        prioritySum += t.getPriority();
        timeSum += t.getCurrentTimeSpent();

        int row = ui->taskTable->rowCount();
        ui->taskTable->insertRow(row);

        // ===== ITEMS =====
        QTableWidgetItem *barItem = new QTableWidgetItem();
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        QTableWidgetItem *titleItem = new QTableWidgetItem(t.getTitle());
        QTableWidgetItem *dateItem  = new QTableWidgetItem(t.getDueDate().toString("yyyy-MM-dd"));
        QTableWidgetItem *priorityItem = new QTableWidgetItem(QString::number(t.getPriority()));

        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(t.isCompleted() ? Qt::Checked : Qt::Unchecked);

        // индекс (ВАЖНО)
        barItem->setData(Qt::UserRole, i);
        checkItem->setData(Qt::UserRole, i);
        titleItem->setData(Qt::UserRole, i);
        dateItem->setData(Qt::UserRole, i);
        priorityItem->setData(Qt::UserRole, i);

        // ===== THEME COLORS =====
        QColor priorityLow, priorityMedium, priorityHigh;
        QColor dateOverdue, dateToday, dateNormal;

        if (theme == "dark") {
            priorityLow    = QColor("#6B8AFD");
            priorityMedium = QColor("#FFB84D");
            priorityHigh   = QColor("#FF7A7A");

            dateOverdue = QColor("#D63031");
            dateToday   = QColor("#F39C12");
            dateNormal  = QColor("#555555");
        }
        else if (theme == "blue") {
            priorityLow    = QColor("#4A90E2");
            priorityMedium = QColor("#5DADE2");
            priorityHigh   = QColor("#E74C3C");

            dateOverdue = QColor("#C0392B");
            dateToday   = QColor("#F39C12");
            dateNormal  = QColor("#7FB3D5");
        }
        else if (theme == "pastel") {
            priorityLow    = QColor("#A3C4F3");
            priorityMedium = QColor("#FFD6A5");
            priorityHigh   = QColor("#FFADAD");

            dateOverdue = QColor("#FF8B94");
            dateToday   = QColor("#FFD6A5");
            dateNormal  = QColor("#BDB2FF");
        }
        else { // light
            priorityLow    = QColor("#6C8CFF");
            priorityMedium = QColor("#FFD166");
            priorityHigh   = QColor("#FF6B6B");

            dateOverdue = QColor("#FF4D4D");
            dateToday   = QColor("#FFC857");
            dateNormal  = QColor("#AAAAAA");
        }

        // ===== PRIORITY =====
        QColor priorityColor;
        if (t.getPriority() <= 2)
            priorityColor = priorityLow;
        else if (t.getPriority() == 3)
            priorityColor = priorityMedium;
        else
            priorityColor = priorityHigh;

        // ===== DATE =====
        bool isOverdue = t.getDueDate() < today;
        bool isToday   = t.getDueDate() == today;

        QColor dateColor;
        if (isOverdue)
            dateColor = dateOverdue;
        else if (isToday)
            dateColor = dateToday;
        else
            dateColor = dateNormal;

        // ===== GRADIENT BAR =====
        QLinearGradient gradient(0, 0, 100, 0);
        gradient.setColorAt(0, dateColor);
        gradient.setColorAt(1, priorityColor);

        barItem->setBackground(QBrush(gradient));
        barItem->setFlags(Qt::ItemIsEnabled);

        // ===== TEXT =====
        QColor textColor = (theme == "dark") ? QColor("#EAEAF0") : QColor("#1A1A1A");

        titleItem->setData(Qt::ForegroundRole, textColor);
        dateItem->setData(Qt::ForegroundRole, textColor);
        priorityItem->setData(Qt::ForegroundRole, textColor);

        // ===== COMPLETED =====
        if (t.isCompleted()) {
            QFont font = titleItem->font();
            font.setStrikeOut(true);

            titleItem->setFont(font);
            dateItem->setFont(font);
            priorityItem->setFont(font);

            QColor doneColor = (theme == "dark")
                                   ? QColor("#777777")
                                   : QColor("#999999");

            titleItem->setForeground(doneColor);
            dateItem->setForeground(doneColor);
            priorityItem->setForeground(doneColor);

            barItem->setBackground(QColor("#CCCCCC"));
        }
        QTableWidgetItem *timeItem =
            new QTableWidgetItem(formatTime(t.getCurrentTimeSpent()));
        if (t.isTimerRunning()) {
            timeItem->setText(timeItem->text() + " ⏱");
        }

        QWidget *controlWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(controlWidget);
        layout->setContentsMargins(0,0,0,0);

        QPushButton *startBtn = new QPushButton("Start");
        QPushButton *pauseBtn = new QPushButton("Pause");


        // 🔥 сохраняем индекс задачи
        startBtn->setProperty("row", i);
        pauseBtn->setProperty("row", i);

        // ===== CONNECT =====
        connect(startBtn, &QPushButton::clicked, this, [this, startBtn]() {
            int row = startBtn->property("row").toInt();
            planner.startTaskTimer(row); // ⚠️ ниже исправим
            updateTable();
        });

        connect(pauseBtn, &QPushButton::clicked, this, [this, pauseBtn]() {
            int row = pauseBtn->property("row").toInt();
            planner.stopTaskTimer(row); // ⚠️ ниже исправим
            updateTable();
        });

        layout->addWidget(startBtn);
        layout->addWidget(pauseBtn);
        // ===== ADD =====
        ui->taskTable->setItem(row, 0, barItem);
        ui->taskTable->setItem(row, 1, checkItem);
        ui->taskTable->setItem(row, 2, titleItem);
        ui->taskTable->setItem(row, 3, dateItem);
        ui->taskTable->setItem(row, 4, priorityItem);
        ui->taskTable->setItem(row, 5, timeItem);
        ui->taskTable->setCellWidget(row, 6, controlWidget);
    }

    ui->taskTable->setSortingEnabled(true);

    // ===== ROW NUMBERS =====
    for (int row = 0; row < ui->taskTable->rowCount(); ++row) {
        QTableWidgetItem *vh = new QTableWidgetItem(QString::number(row + 1));
        ui->taskTable->setVerticalHeaderItem(row, vh);
    }

    // 🔥 FINAL SUMMARY UPDATE
    double avgPriority = (visibleTotal == 0)
                             ? 0
                             : static_cast<double>(prioritySum) / visibleTotal;

    qint64 avgTime = (visibleTotal == 0)
                         ? 0
                         : timeSum / visibleTotal;
    QString avgTimeStr = formatTime(avgTime);

    ui->summaryLabel->setText(
        "Total: " + QString::number(visibleTotal) +
        " | Completed: " + QString::number(visibleCompleted) +
        " | Avg priority: " + QString::number(avgPriority, 'f', 1) +
        "|⏱ Avg time: " + avgTimeStr
        );

    ui->taskTable->blockSignals(false);
}


void MainWindow::on_addButton_clicked()
{
    AddTaskDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        planner.addTask(dialog.getTask());
        updateTable();
    }
}

void MainWindow::on_editButton_clicked()
{
    int row = ui->taskTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Warning", "Please select a task to edit");
        return;
    }

    QTableWidgetItem *item = ui->taskTable->item(row, 2);


    int realIndex = item->data(Qt::UserRole).toInt();

    Task task = planner.getTasks()[realIndex];

    AddTaskDialog dialog(this);
    dialog.setTask(task);

    if (dialog.exec() == QDialog::Accepted) {
        planner.updateTask(row, dialog.getTask());
        updateTable();
    }
}

void MainWindow::on_logoutButton_clicked()
{
    QString basePath = QCoreApplication::applicationDirPath()
    + "/data/users/" + currentUser + "/";

    // 💾 СНАЧАЛА сохраняем
    planner.saveToBinaryFile(basePath + "tasks.dat");

    // ❗ ЗАКРЫВАЕМ текущее окно СРАЗУ
    this->close();

    // 🔓 потом логин
    LoginWindow login;

    if (login.exec() == QDialog::Accepted) {
        MainWindow *newWindow = new MainWindow(login.getUsername());
        newWindow->show();
    }
}

void MainWindow::on_taskTable_itemChanged(QTableWidgetItem *item)
{
    if (item->column() != 1)
        return;

    disconnect(ui->taskTable, &QTableWidget::itemChanged,
               this, &MainWindow::on_taskTable_itemChanged);

    int realIndex = item->data(Qt::UserRole).toInt();
    bool done = (item->checkState() == Qt::Checked);

    planner.setCompleted(realIndex, done);
    QString basePath = QCoreApplication::applicationDirPath()
                       + "/data/users/" + currentUser + "/";
    planner.saveToBinaryFile(basePath + "tasks.dat");

    updateTable();


    connect(ui->taskTable, &QTableWidget::itemChanged,
            this, &MainWindow::on_taskTable_itemChanged);
}

void MainWindow::on_deleteButton_clicked()
{
    int row = ui->taskTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Warning", "Please select a task to delete");
        return;
    }

    planner.removeTask(row);
    updateTable();
}
void MainWindow::on_dateFilterBox_currentIndexChanged(int)
{
    updateTable();
}

void MainWindow::on_priorityFilterBox_currentIndexChanged(int)
{
    updateTable();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
void MainWindow::applyTheme(const QString &themePath)
{
    QFile file(themePath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Не удалось открыть файл:" << themePath;
        return;
    }

    QString style = file.readAll();
    qApp->setStyleSheet(style);

    QSettings settings("PlannerGUI", "PlannerGUI");
    settings.setValue("theme", themePath);

    updateLegend();
    updateTable();
}
void MainWindow::updateLegend()
{
    QString theme = getThemeName();

    QString low, medium, high, today, overdue;

    if (theme == "dark") {
        low = "#6C8CFF"; medium = "#FFD166"; high = "#FF6B6B";
        today = "#FFC857"; overdue = "#FF4D4D";
    }
    else if (theme == "blue") {
        low = "#4A90E2"; medium = "#5DADE2"; high = "#E74C3C";
        today = "#F39C12"; overdue = "#C0392B";
    }
    else if (theme == "pastel") {
        low = "#A3C4F3"; medium = "#FFD6A5"; high = "#FFADAD";
        today = "#FFD6A5"; overdue = "#FF8B94";
    }
    else {
        low = "#6B8AFD"; medium = "#FFB84D"; high = "#FF7A7A";
        today = "#F39C12"; overdue = "#D63031";
    }

    ui->legendLabel->setText(QString(R"(
        ⏰ <span style='color:%4;'>Today</span>&nbsp;&nbsp;
        ⚠ <span style='color:%5;'>Overdue</span>
        &nbsp;|&nbsp;
        <span style='color:%1;'>●</span> Low&nbsp;&nbsp;
        <span style='color:%2;'>●</span> Medium&nbsp;&nbsp;
        <span style='color:%3;'>●</span> High&nbsp;&nbsp;


    )").arg(low, medium, high, today, overdue));

    ui->legendLabel->setTextFormat(Qt::RichText);
}

void MainWindow::updateSummary(const QVector<Task> &tasks) {
    int total = tasks.size();
    int completed = 0;

    for(const Task&task : tasks) {
        if(task.isCompleted()) {
            completed++;
        }
    }
    ui->summaryLabel->setText("Total: " + QString::number(total) + " | Completed: " + QString::number(completed));
}
void MainWindow::updateRowNumbers()
{
    for (int row = 0; row < ui->taskTable->rowCount(); ++row) {
        QTableWidgetItem *item = ui->taskTable->verticalHeaderItem(row);

        if (!item)
            item = new QTableWidgetItem();

        item->setText(QString::number(row + 1));
        ui->taskTable->setVerticalHeaderItem(row, item);
    }
}
