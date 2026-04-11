#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H


#include <QDialog>
#include "core/UserManager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QString getUsername() const;

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_showPasswordCheckBox_stateChanged(int state);
    void onThemeChanged(const QString &themeName);

private:
    Ui::LoginWindow *ui;
    UserManager userManager;
    void showError(const QString &message);
    void clearError();

};

#endif // LOGINWINDOW_H

