/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *themeBox;
    QFrame *cardFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QLabel *errorLabel;
    QLineEdit *username;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *password;
    QCheckBox *showPasswordCheckBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerButton;
    QPushButton *loginButton;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->setWindowModality(Qt::WindowModality::ApplicationModal);
        LoginWindow->resize(526, 444);
        LoginWindow->setMinimumSize(QSize(380, 240));
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        themeBox = new QComboBox(LoginWindow);
        themeBox->addItem(QString());
        themeBox->addItem(QString());
        themeBox->addItem(QString());
        themeBox->addItem(QString());
        themeBox->addItem(QString());
        themeBox->setObjectName("themeBox");
        QFont font;
        font.setFamilies({QString::fromUtf8("Ink Free")});
        themeBox->setFont(font);

        verticalLayout->addWidget(themeBox);

        cardFrame = new QFrame(LoginWindow);
        cardFrame->setObjectName("cardFrame");
        cardFrame->setStyleSheet(QString::fromUtf8(""));
        cardFrame->setFrameShape(QFrame::Shape::NoFrame);
        cardFrame->setFrameShadow(QFrame::Shadow::Plain);
        verticalLayout_2 = new QVBoxLayout(cardFrame);
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(20, 20, 20, 20);
        title = new QLabel(cardFrame);
        title->setObjectName("title");
        title->setMinimumSize(QSize(462, 189));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ink Free")});
        font1.setPointSize(24);
        font1.setBold(true);
        title->setFont(font1);
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(title);

        errorLabel = new QLabel(cardFrame);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setStyleSheet(QString::fromUtf8(""));
        errorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        errorLabel->setWordWrap(true);

        verticalLayout_2->addWidget(errorLabel);

        username = new QLineEdit(cardFrame);
        username->setObjectName("username");
        username->setFont(font);
        username->setStyleSheet(QString::fromUtf8(""));
        username->setMaxLength(64);
        username->setClearButtonEnabled(true);

        verticalLayout_2->addWidget(username);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        password = new QLineEdit(cardFrame);
        password->setObjectName("password");
        password->setFont(font);
        password->setStyleSheet(QString::fromUtf8(""));
        password->setMaxLength(64);
        password->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(password);

        showPasswordCheckBox = new QCheckBox(cardFrame);
        showPasswordCheckBox->setObjectName("showPasswordCheckBox");
        showPasswordCheckBox->setFont(font);

        horizontalLayout_2->addWidget(showPasswordCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 0, 10, -1);
        registerButton = new QPushButton(cardFrame);
        registerButton->setObjectName("registerButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ink Free")});
        font2.setBold(true);
        registerButton->setFont(font2);
        registerButton->setStyleSheet(QString::fromUtf8(""));
        registerButton->setAutoDefault(false);

        horizontalLayout->addWidget(registerButton);

        loginButton = new QPushButton(cardFrame);
        loginButton->setObjectName("loginButton");
        loginButton->setFont(font2);
        loginButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(loginButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(cardFrame);


        retranslateUi(LoginWindow);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        themeBox->setItemText(0, QCoreApplication::translate("LoginWindow", "Themes", nullptr));
        themeBox->setItemText(1, QCoreApplication::translate("LoginWindow", "Light", nullptr));
        themeBox->setItemText(2, QCoreApplication::translate("LoginWindow", "Dark", nullptr));
        themeBox->setItemText(3, QCoreApplication::translate("LoginWindow", "Blue", nullptr));
        themeBox->setItemText(4, QCoreApplication::translate("LoginWindow", "Pastel", nullptr));

        title->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        errorLabel->setText(QString());
        username->setText(QString());
        username->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter username", nullptr));
        password->setText(QString());
        password->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter password", nullptr));
        showPasswordCheckBox->setText(QCoreApplication::translate("LoginWindow", "Show password", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
