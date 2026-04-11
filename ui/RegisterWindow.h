#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include "core/UserManager.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_registerButton_clicked();
    void on_cancelButton_clicked();
    void on_showPasswordCheckBox_stateChanged(int state);
    void on_showConfirmCheckBox_stateChanged(int state);

private:
    Ui::RegisterWindow *ui;
    UserManager userManager;
};

#endif // REGISTERWINDOW_H

