#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegisterWindow.h"
#include "MainWindow.h"

#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // error label
    ui->errorLabel->setVisible(false);
    ui->errorLabel->clear();

    // password
    ui->password->setEchoMode(QLineEdit::Password);
    ui->showPasswordCheckBox->setChecked(false);

    ui->loginButton->setDefault(true);

    // =========================
    // THEME
    // =========================
    QSettings settings("PlannerGUI", "PlannerGUI");
    QString currentTheme = settings.value("theme", ":/themes/light.qss").toString();

    if (currentTheme.contains("dark"))
        ui->themeBox->setCurrentText("Dark");
    else if (currentTheme.contains("blue"))
        ui->themeBox->setCurrentText("Blue");
    else if (currentTheme.contains("pastel"))
        ui->themeBox->setCurrentText("Pastel");
    else
        ui->themeBox->setCurrentText("Light");

    // connect theme change
    connect(ui->themeBox, &QComboBox::currentTextChanged,
            this, &LoginWindow::onThemeChanged);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

// =========================
// ERROR HANDLING
// =========================
void LoginWindow::showError(const QString &message)
{
    ui->errorLabel->setText("⚠ " + message);
    ui->errorLabel->setVisible(true);
}

void LoginWindow::clearError()
{
    ui->errorLabel->clear();
    ui->errorLabel->setVisible(false);
}

// =========================
// LOGIN
// =========================
void LoginWindow::on_loginButton_clicked()
{
    clearError();

    QString username = ui->username->text().trimmed();
    QString password = ui->password->text();

    if (username.isEmpty()) {
        showError("Username cannot be empty");
        return;
    }

    if (password.isEmpty()) {
        showError("Password cannot be empty");
        return;
    }

    if (userManager.login(username, password)) {
        MainWindow *mw = new MainWindow(username);
        mw->show();
        this->close();
        return; // 💥 важно
    }

    showError("Incorrect username or password");
}

// =========================
// REGISTER
// =========================
void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow reg;
    reg.exec();
}

// =========================
// SHOW PASSWORD
// =========================
void LoginWindow::on_showPasswordCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        ui->password->setEchoMode(QLineEdit::Normal);
    else
        ui->password->setEchoMode(QLineEdit::Password);
}

// =========================
// THEME CHANGE
// =========================
void LoginWindow::onThemeChanged(const QString &themeName)
{
    QString path;

    if (themeName == "Dark")
        path = ":/new/prefix1/themes/dark.qss";
    else if (themeName == "Blue")
        path = ":/new/prefix1/themes/blue.qss";
    else if (themeName == "Pastel")
        path = ":/new/prefix1/themes/pastel.qss";
    else
        path = ":/new/prefix1/themes/light.qss";

    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Theme load error:" << path;
        return;
    }

    QString style = file.readAll();
    qApp->setStyleSheet(style);

    QSettings settings("PlannerGUI", "PlannerGUI");
    settings.setValue("theme", path);
}

QString LoginWindow::getUsername() const {
    return getUsername();
}
