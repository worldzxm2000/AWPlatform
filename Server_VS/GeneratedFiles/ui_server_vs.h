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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "SrvTableWidget.h"
QT_BEGIN_NAMESPACE

class Ui_Server_VSClass
{
public:
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Server_VSClass)
    {
        if (Server_VSClass->objectName().isEmpty())
            Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
        Server_VSClass->resize(1280, 768);
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
        menuBar = new QMenuBar(Server_VSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
        Server_VSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Server_VSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Server_VSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Server_VSClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Server_VSClass->setStatusBar(statusBar);

        retranslateUi(Server_VSClass);

        QMetaObject::connectSlotsByName(Server_VSClass);
    } // setupUi

    void retranslateUi(QMainWindow *Server_VSClass)
    {
        Server_VSClass->setWindowTitle(QApplication::translate("Server_VSClass", "\346\234\215\345\212\241\345\231\250\347\256\241\347\220\206", nullptr));
        groupBox->setTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\347\247\215\347\261\273\345\210\227\350\241\250", nullptr));
        DeleteBtn->setText(QApplication::translate("Server_VSClass", "-", nullptr));
        RunBtn->setText(QApplication::translate("Server_VSClass", "+", nullptr));
        groupBox_2->setTitle(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QApplication::translate("Server_VSClass", "\347\212\266\346\200\201\346\240\217", nullptr));
        label->setText(QApplication::translate("Server_VSClass", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
        StatusLabel->setText(QApplication::translate("Server_VSClass", "\350\277\220\350\241\214\346\255\243\345\270\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server_VSClass: public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_VS_H
