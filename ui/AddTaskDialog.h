#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include "core/Task.h"

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);
    ~AddTaskDialog();

    Task getTask() const;
    void setTask(const Task &task);

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::AddTaskDialog *ui;
};

#endif // ADDTASKDIALOG_H
