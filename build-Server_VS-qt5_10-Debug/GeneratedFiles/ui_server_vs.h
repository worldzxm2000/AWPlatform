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

QT_BEGIN_NAMESPACE

class Ui_Server_VSClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *DeleteBtn;
    QPushButton *RunBtn;
    QTableWidget *ServerList;
    QGroupBox *groupBox_2;
    QTableWidget *clientList;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *StatusLabel;
    QGroupBox *groupBox_4;
    QPushButton *SetTimeBtn;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Server_VSClass)
    {
        if (Server_VSClass->objectName().isEmpty())
            Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
        Server_VSClass->resize(1024, 768);
        centralWidget = new QWidget(Server_VSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 60, 141, 591));
        DeleteBtn = new QPushButton(groupBox);
        DeleteBtn->setObjectName(QStringLiteral("DeleteBtn"));
        DeleteBtn->setGeometry(QRect(90, 550, 41, 23));
        RunBtn = new QPushButton(groupBox);
        RunBtn->setObjectName(QStringLiteral("RunBtn"));
        RunBtn->setGeometry(QRect(10, 550, 41, 23));
        ServerList = new QTableWidget(groupBox);
        ServerList->setObjectName(QStringLiteral("ServerList"));
        ServerList->setGeometry(QRect(10, 20, 121, 521));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 60, 861, 591));
        clientList = new QTableWidget(groupBox_2);
        clientList->setObjectName(QStringLiteral("clientList"));
        clientList->setGeometry(QRect(10, 20, 841, 561));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 660, 1001, 51));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 54, 16));
        StatusLabel = new QLabel(groupBox_3);
        StatusLabel->setObjectName(QStringLiteral("StatusLabel"));
        StatusLabel->setGeometry(QRect(70, 20, 341, 16));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 1001, 51));
        SetTimeBtn = new QPushButton(groupBox_4);
        SetTimeBtn->setObjectName(QStringLiteral("SetTimeBtn"));
        SetTimeBtn->setGeometry(QRect(10, 20, 75, 23));
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 20, 75, 23));
        pushButton_3 = new QPushButton(groupBox_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(190, 20, 75, 23));
        pushButton_4 = new QPushButton(groupBox_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(270, 20, 75, 23));
        pushButton_5 = new QPushButton(groupBox_4);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(360, 20, 75, 23));
        pushButton_6 = new QPushButton(groupBox_4);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(440, 20, 81, 23));
        pushButton_7 = new QPushButton(groupBox_4);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(530, 20, 81, 23));
        pushButton_8 = new QPushButton(groupBox_4);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(620, 20, 81, 23));
        pushButton_9 = new QPushButton(groupBox_4);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(710, 20, 81, 23));
        Server_VSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Server_VSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
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
        groupBox_4->setTitle(QApplication::translate("Server_VSClass", "\347\273\210\347\253\257\345\221\275\344\273\244\346\216\247\345\210\266", nullptr));
        SetTimeBtn->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\346\227\266\351\227\264", nullptr));
        pushButton_2->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\345\214\272\347\253\231\345\217\267", nullptr));
        pushButton_3->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\347\272\254\345\272\246", nullptr));
        pushButton_4->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\347\273\217\345\272\246", nullptr));
        pushButton_5->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\346\265\267\346\213\224", nullptr));
        pushButton_6->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\351\207\207\351\233\206\346\227\266\351\227\264", nullptr));
        pushButton_7->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\351\207\207\351\233\206\351\227\264\351\232\224", nullptr));
        pushButton_8->setText(QApplication::translate("Server_VSClass", "\351\207\215\345\220\257\351\207\207\351\233\206\345\231\250", nullptr));
        pushButton_9->setText(QApplication::translate("Server_VSClass", "\350\256\276\347\275\256\351\207\207\351\233\206\351\227\264\351\232\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server_VSClass: public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_VS_H
