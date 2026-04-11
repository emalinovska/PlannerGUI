/********************************************************************************
** Form generated from reading UI file 'RegisterWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *cardFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QLabel *errorLabel;
    QLineEdit *usernameEdit;
    QFormLayout *formLayout;
    QLineEdit *passwordEdit;
    QLineEdit *confirmEdit;
    QCheckBox *showConfirmCheckBox;
    QCheckBox *showPasswordCheckBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *registerButton;

    void setupUi(QDialog *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->setWindowModality(Qt::WindowModality::ApplicationModal);
        RegisterWindow->resize(506, 459);
        RegisterWindow->setMinimumSize(QSize(400, 260));
        verticalLayout = new QVBoxLayout(RegisterWindow);
        verticalLayout->setObjectName("verticalLayout");
        cardFrame = new QFrame(RegisterWindow);
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
        title->setEnabled(true);
        QFont font;
        font.setFamilies({QString::fromUtf8("Ink Free")});
        font.setPointSize(24);
        title->setFont(font);
        title->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(title);

        errorLabel = new QLabel(cardFrame);
        errorLabel->setObjectName("errorLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ink Free")});
        font1.setBold(true);
        font1.setItalic(false);
        errorLabel->setFont(font1);
        errorLabel->setStyleSheet(QString::fromUtf8(""));
        errorLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        errorLabel->setWordWrap(true);

        verticalLayout_2->addWidget(errorLabel);

        usernameEdit = new QLineEdit(cardFrame);
        usernameEdit->setObjectName("usernameEdit");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ink Free")});
        usernameEdit->setFont(font2);
        usernameEdit->setStyleSheet(QString::fromUtf8(""));
        usernameEdit->setMaxLength(64);
        usernameEdit->setClearButtonEnabled(true);

        verticalLayout_2->addWidget(usernameEdit);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        passwordEdit = new QLineEdit(cardFrame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setMinimumSize(QSize(300, 0));
        passwordEdit->setFont(font2);
        passwordEdit->setStyleSheet(QString::fromUtf8(""));
        passwordEdit->setMaxLength(64);
        passwordEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, passwordEdit);

        confirmEdit = new QLineEdit(cardFrame);
        confirmEdit->setObjectName("confirmEdit");
        confirmEdit->setMinimumSize(QSize(300, 0));
        confirmEdit->setFont(font2);
        confirmEdit->setStyleSheet(QString::fromUtf8(""));
        confirmEdit->setMaxLength(64);
        confirmEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, confirmEdit);

        showConfirmCheckBox = new QCheckBox(cardFrame);
        showConfirmCheckBox->setObjectName("showConfirmCheckBox");
        showConfirmCheckBox->setFont(font2);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, showConfirmCheckBox);

        showPasswordCheckBox = new QCheckBox(cardFrame);
        showPasswordCheckBox->setObjectName("showPasswordCheckBox");
        showPasswordCheckBox->setFont(font2);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, showPasswordCheckBox);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(cardFrame);
        cancelButton->setObjectName("cancelButton");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Ink Free")});
        font3.setBold(true);
        cancelButton->setFont(font3);
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(cancelButton);

        registerButton = new QPushButton(cardFrame);
        registerButton->setObjectName("registerButton");
        registerButton->setFont(font3);
        registerButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(registerButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(cardFrame);


        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QDialog *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "Create Account", nullptr));
        title->setText(QCoreApplication::translate("RegisterWindow", "Create Account", nullptr));
        errorLabel->setText(QString());
        usernameEdit->setText(QString());
        usernameEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "Enter username", nullptr));
        passwordEdit->setText(QString());
        passwordEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "Enter password", nullptr));
        confirmEdit->setText(QString());
        confirmEdit->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "Confirm password", nullptr));
        showConfirmCheckBox->setText(QCoreApplication::translate("RegisterWindow", "Show Password", nullptr));
        showPasswordCheckBox->setText(QCoreApplication::translate("RegisterWindow", "Show Password", nullptr));
        cancelButton->setText(QCoreApplication::translate("RegisterWindow", "Cancel", nullptr));
        registerButton->setText(QCoreApplication::translate("RegisterWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
