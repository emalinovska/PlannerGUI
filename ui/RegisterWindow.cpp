#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_registerButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirm  = ui->confirmEdit->text();

    // Проверка пустых полей
    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        ui->errorLabel->setText("Please fill in all fields");
        ui->errorLabel->setVisible(true);
        return;
    }

    // Проверка совпадения паролей
    if (password != confirm) {
        ui->errorLabel->setText("Passwords do not match");
        ui->errorLabel->setVisible(true);
        return;
    }

    // Проверка существования пользователя
    if (!userManager.registerUser(username, password)) {
        ui->errorLabel->setText("User already exists");
        ui->errorLabel->setVisible(true);
        return;
    }

    QMessageBox::information(this, "Success", "Account created successfully");
    this->close();
}

void RegisterWindow::on_cancelButton_clicked()
{
    this->close();
}
void RegisterWindow::on_showPasswordCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
}

void RegisterWindow::on_showConfirmCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        ui->confirmEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->confirmEdit->setEchoMode(QLineEdit::Password);
}
