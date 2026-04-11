/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionThemesBlue;
    QAction *actionThemesDark;
    QAction *actionThemesLight;
    QAction *actionThemesPastel;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *dateFilterBox;
    QComboBox *priorityFilterBox;
    QTableWidget *taskTable;
    QLabel *summaryLabel;
    QLabel *legendLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *logoutButton;
    QMenuBar *menubar;
    QMenu *menuThemes;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(681, 683);
        actionThemesBlue = new QAction(MainWindow);
        actionThemesBlue->setObjectName("actionThemesBlue");
        actionThemesDark = new QAction(MainWindow);
        actionThemesDark->setObjectName("actionThemesDark");
        actionThemesLight = new QAction(MainWindow);
        actionThemesLight->setObjectName("actionThemesLight");
        actionThemesPastel = new QAction(MainWindow);
        actionThemesPastel->setObjectName("actionThemesPastel");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        dateFilterBox = new QComboBox(centralwidget);
        dateFilterBox->addItem(QString());
        dateFilterBox->addItem(QString());
        dateFilterBox->addItem(QString());
        dateFilterBox->addItem(QString());
        dateFilterBox->setObjectName("dateFilterBox");
        dateFilterBox->setMinimumSize(QSize(10, 0));
        dateFilterBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(dateFilterBox);

        priorityFilterBox = new QComboBox(centralwidget);
        priorityFilterBox->addItem(QString());
        priorityFilterBox->addItem(QString());
        priorityFilterBox->addItem(QString());
        priorityFilterBox->addItem(QString());
        priorityFilterBox->addItem(QString());
        priorityFilterBox->addItem(QString());
        priorityFilterBox->setObjectName("priorityFilterBox");
        priorityFilterBox->setMinimumSize(QSize(10, 0));
        priorityFilterBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(priorityFilterBox);


        verticalLayout->addLayout(horizontalLayout_3);

        taskTable = new QTableWidget(centralwidget);
        if (taskTable->columnCount() < 5)
            taskTable->setColumnCount(5);
        taskTable->setObjectName("taskTable");
        taskTable->setStyleSheet(QString::fromUtf8(""));
        taskTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        taskTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        taskTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        taskTable->setShowGrid(false);
        taskTable->setColumnCount(5);
        taskTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(taskTable);

        summaryLabel = new QLabel(centralwidget);
        summaryLabel->setObjectName("summaryLabel");

        verticalLayout->addWidget(summaryLabel);

        legendLabel = new QLabel(centralwidget);
        legendLabel->setObjectName("legendLabel");

        verticalLayout->addWidget(legendLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");
        editButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(editButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(deleteButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");

        horizontalLayout->addWidget(logoutButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 681, 25));
        menuThemes = new QMenu(menubar);
        menuThemes->setObjectName("menuThemes");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuThemes->menuAction());
        menuThemes->addAction(actionThemesBlue);
        menuThemes->addAction(actionThemesDark);
        menuThemes->addAction(actionThemesLight);
        menuThemes->addAction(actionThemesPastel);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionThemesBlue->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        actionThemesDark->setText(QCoreApplication::translate("MainWindow", "Dark", nullptr));
        actionThemesLight->setText(QCoreApplication::translate("MainWindow", "Light", nullptr));
        actionThemesPastel->setText(QCoreApplication::translate("MainWindow", "Pastel", nullptr));
        dateFilterBox->setItemText(0, QCoreApplication::translate("MainWindow", "All dates", nullptr));
        dateFilterBox->setItemText(1, QCoreApplication::translate("MainWindow", "Today", nullptr));
        dateFilterBox->setItemText(2, QCoreApplication::translate("MainWindow", "Overdue", nullptr));
        dateFilterBox->setItemText(3, QCoreApplication::translate("MainWindow", "Future", nullptr));

        priorityFilterBox->setItemText(0, QCoreApplication::translate("MainWindow", "All priorities", nullptr));
        priorityFilterBox->setItemText(1, QCoreApplication::translate("MainWindow", "Priority \342\211\245 1", nullptr));
        priorityFilterBox->setItemText(2, QCoreApplication::translate("MainWindow", "Priority \342\211\245 2", nullptr));
        priorityFilterBox->setItemText(3, QCoreApplication::translate("MainWindow", "Priority \342\211\245 3", nullptr));
        priorityFilterBox->setItemText(4, QCoreApplication::translate("MainWindow", "Priority \342\211\245 4", nullptr));
        priorityFilterBox->setItemText(5, QCoreApplication::translate("MainWindow", "Priority = 5", nullptr));

        summaryLabel->setText(QString());
        legendLabel->setText(QString());
        addButton->setText(QCoreApplication::translate("MainWindow", "Add Task", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "Edit Task", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete Task", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        menuThemes->setTitle(QCoreApplication::translate("MainWindow", "Themes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
