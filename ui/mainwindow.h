#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "core/Planner.h"
#include <QTableWidgetItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &username, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_dateFilterBox_currentIndexChanged(int index);
    void on_priorityFilterBox_currentIndexChanged(int index);
    void on_taskTable_itemChanged(QTableWidgetItem *item);
    void on_logoutButton_clicked();


private:
    void updateTable();
    void updateLegend();
    void updateSummary(const QVector<Task> &tasks);
    void updateRowNumbers();
    void applyTheme(const QString &themePath);

private:
    Ui::MainWindow *ui;
    Planner planner;

    // ⭐ ЭТО ВАЖНО — ЭТОГО У ТЕБЯ НЕ ХВАТАЕТ
    QString currentUser;
    QTimer *liveTimer;
};

#endif // MAINWINDOW_H
