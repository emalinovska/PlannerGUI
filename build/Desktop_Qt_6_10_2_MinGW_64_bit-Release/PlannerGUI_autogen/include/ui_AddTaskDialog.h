/********************************************************************************
** Form generated from reading UI file 'AddTaskDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTASKDIALOG_H
#define UI_ADDTASKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTaskDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *titleEdit;
    QDateEdit *dueDateEdit;
    QSpinBox *prioritySpin;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *saveButton;

    void setupUi(QDialog *AddTaskDialog)
    {
        if (AddTaskDialog->objectName().isEmpty())
            AddTaskDialog->setObjectName("AddTaskDialog");
        AddTaskDialog->resize(732, 601);
        AddTaskDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(AddTaskDialog);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        title = new QLabel(AddTaskDialog);
        title->setObjectName("title");
        QFont font;
        font.setFamilies({QString::fromUtf8("Ink Free")});
        font.setPointSize(24);
        title->setFont(font);
        title->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(title);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(AddTaskDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_2);

        label_3 = new QLabel(AddTaskDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_3);

        label_4 = new QLabel(AddTaskDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_4);

        titleEdit = new QLineEdit(AddTaskDialog);
        titleEdit->setObjectName("titleEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, titleEdit);

        dueDateEdit = new QDateEdit(AddTaskDialog);
        dueDateEdit->setObjectName("dueDateEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, dueDateEdit);

        prioritySpin = new QSpinBox(AddTaskDialog);
        prioritySpin->setObjectName("prioritySpin");
        prioritySpin->setMinimum(1);
        prioritySpin->setMaximum(5);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, prioritySpin);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(AddTaskDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        saveButton = new QPushButton(AddTaskDialog);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddTaskDialog);

        QMetaObject::connectSlotsByName(AddTaskDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTaskDialog)
    {
        AddTaskDialog->setWindowTitle(QCoreApplication::translate("AddTaskDialog", "Dialog", nullptr));
        title->setText(QCoreApplication::translate("AddTaskDialog", "Add / Edit Task", nullptr));
        label_2->setText(QCoreApplication::translate("AddTaskDialog", "Task title :", nullptr));
        label_3->setText(QCoreApplication::translate("AddTaskDialog", "Due Date :", nullptr));
        label_4->setText(QCoreApplication::translate("AddTaskDialog", "Priority :", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddTaskDialog", "Cancel", nullptr));
        saveButton->setText(QCoreApplication::translate("AddTaskDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTaskDialog: public Ui_AddTaskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTASKDIALOG_H
