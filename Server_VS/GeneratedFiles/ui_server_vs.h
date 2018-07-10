/********************************************************************************
** Form generated from reading UI file 'server_vs.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_VS_H
#define UI_SERVER_VS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include"SrvTableWidget.h"
QT_BEGIN_NAMESPACE

class Ui_Server_VSClass
{
public:
    QAction *actionDMTM;
    QAction *action1;
    QAction *action_SYSLog;
    QAction *action_DataLog;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *DeleteBtn;
    QPushButton *RunBtn;
	SrvTableWidget *ServerList;
    QGroupBox *groupBox_2;
    QTableWidget *clientList;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *StatusLabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *Server_VSClass)
    {
        if (Server_VSClass->objectName().isEmpty())
            Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
        Server_VSClass->resize(1280, 768);
        actionDMTM = new QAction(Server_VSClass);
        actionDMTM->setObjectName(QStringLiteral("actionDMTM"));
        action1 = new QAction(Server_VSClass);
        action1->setObjectName(QStringLiteral("action1"));
        action_SYSLog = new QAction(Server_VSClass);
        action_SYSLog->setObjectName(QStringLiteral("action_SYSLog"));
        action_DataLog = new QAction(Server_VSClass);
        action_DataLog->setObjectName(QStringLiteral("action_DataLog"));
        centralWidget = new QWidget(Server_VSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 241, 641));
        DeleteBtn = new QPushButton(groupBox);
        DeleteBtn->setObjectName(QStringLiteral("DeleteBtn"));
        DeleteBtn->setGeometry(QRect(80, 610, 41, 23));
        RunBtn = new QPushButton(groupBox);
        RunBtn->setObjectName(QStringLiteral("RunBtn"));
        RunBtn->setGeometry(QRect(10, 610, 41, 23));
        ServerList = new SrvTableWidget(groupBox);
        ServerList->setObjectName(QStringLiteral("ServerList"));
        ServerList->setGeometry(QRect(10, 20, 221, 581));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(260, 10, 1011, 641));
        clientList = new QTableWidget(groupBox_2);
        clientList->setObjectName(QStringLiteral("clientList"));
        clientList->setGeometry(QRect(10, 20, 991, 611));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 660, 1271, 51));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 54, 16));
        StatusLabel = new QLabel(groupBox_3);
        StatusLabel->setObjectName(QStringLiteral("StatusLabel"));
        StatusLabel->setGeometry(QRect(70, 20, 500, 16));
        Server_VSClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Server_VSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Server_VSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Server_VSClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Server_VSClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(Server_VSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        Server_VSClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionDMTM);
        menu_2->addAction(action_SYSLog);
        menu_2->addAction(action_DataLog);

        retranslateUi(Server_VSClass);

        QMetaObject::connectSlotsByName(Server_VSClass);
    } // setupUi

    void retranslateUi(QMainWindow *Server_VSClass)
    {
        Server_VSClass->setWindowTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\346\234\215\345\212\241\345\271\263\345\217\260\350\275\257\344\273\266", nullptr));
        actionDMTM->setText(QApplication::translate("Server_VSClass", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDMTM->setToolTip(QApplication::translate("Server_VSClass", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
#endif // QT_NO_TOOLTIP
        action1->setText(QApplication::translate("Server_VSClass", "1", nullptr));
        action_SYSLog->setText(QApplication::translate("Server_VSClass", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        action_DataLog->setText(QApplication::translate("Server_VSClass", "\346\225\260\346\215\256\346\227\245\345\277\227", nullptr));
        groupBox->setTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\347\247\215\347\261\273\345\210\227\350\241\250", nullptr));
        DeleteBtn->setText(QApplication::translate("Server_VSClass", "-", nullptr));
        RunBtn->setText(QApplication::translate("Server_VSClass", "+", nullptr));
        groupBox_2->setTitle(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QApplication::translate("Server_VSClass", "\347\212\266\346\200\201\346\240\217", nullptr));
        label->setText(QApplication::translate("Server_VSClass", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
        StatusLabel->setText(QApplication::translate("Server_VSClass", "\350\277\220\350\241\214\346\255\243\345\270\270", nullptr));
        menu->setTitle(QApplication::translate("Server_VSClass", "\345\212\237\350\203\275", nullptr));
        menu_2->setTitle(QApplication::translate("Server_VSClass", "\346\237\245\347\234\213\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server_VSClass: public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_VS_H
