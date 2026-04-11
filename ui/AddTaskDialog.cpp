#include "AddTaskDialog.h"
#include "ui_AddTaskDialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);

    ui->dueDateEdit->setDate(QDate::currentDate());
    ui->prioritySpin->setRange(1, 5);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

Task AddTaskDialog::getTask() const
{
    return Task(
        ui->titleEdit->text(),
        ui->dueDateEdit->date(),
        ui->prioritySpin->value()
        );
}

void AddTaskDialog::setTask(const Task &task)
{
    ui->titleEdit->setText(task.getTitle());
    ui->dueDateEdit->setDate(task.getDueDate());
    ui->prioritySpin->setValue(task.getPriority());
}

void AddTaskDialog::on_saveButton_clicked()
{
    if (ui->titleEdit->text().isEmpty()) {
        // Можно добавить errorLabel, если хочешь
        return;
    }

    accept();
}

void AddTaskDialog::on_cancelButton_clicked()
{
    reject();
}
