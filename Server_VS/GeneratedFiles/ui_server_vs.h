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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include"SrvTableWidget.h"
#include"MyDockWidget.h"
#include"MyButton.h"
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
	SrvTableWidget *ServerList;
	QLabel *OnLineCountLabel;
	QGroupBox *groupBox_2;
	QTableWidget *ClientList;
	QLabel *ImageLabel;
	QLabel *NameLabel;
	QGroupBox *groupBox_SL;
	QScrollArea *ScrollArea_AddBtn;
	QWidget *ScrollAreaWidgetContents_AddBtn;
	MyButton *AddBtn;
	QScrollArea *ScrollArea_RemoveBtn;
	QWidget *ScrollAreaWidgetContents_RemoveBtn;
	MyButton *RemoveBtn;
	//QScrollArea *ScrollArea_UpLoadBtn;
	//QWidget *ScrollAreaWidgetContents_UpLoadBtn;
	//MyButton *UpLoadBtn;
	QGroupBox *groupBox_SYSStatus;
	QScrollArea *ScrollArea_ControlBtn;
	QWidget *ScrollAreaWidgetContents_ControlBtn;
	MyButton *ControlBtn;
	QScrollArea *ScrollArea_LogBtn;
	QWidget *ScrollAreaWidgetContents_LogBtn;
	MyButton *LogBtn;

	QScrollArea *ScrollArea_MQBtn;
	QWidget *ScrollAreaWidgetContents_MQBtn;
	MyButton *MQBtn;

	QScrollArea *ScrollArea_TerminalBtn;
	QWidget *ScrollAreaWidgetContents_TerminalBtn;
	MyButton *TerminalBtn;

	QGroupBox *groupBox_SrvGB;
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;
	QScrollArea *ScrollArea_MinBtn;
	QWidget *ScrollAreaWidgetContents_MinBtn;
	MyButton *MinBtn;
	QScrollArea *ScrollArea_WarningBtn;
	QWidget *ScrollAreaWidgetContents_WarningBtn;
	MyButton *WarningBtn;
	MyDockWidget *WarningDockWidget;

	void setupUi(QMainWindow *Server_VSClass)
	{
		if (Server_VSClass->objectName().isEmpty())
			Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
		Server_VSClass->resize(1280, 666);
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(10);
		Server_VSClass->setFont(font);
		QIcon icon;
		icon.addFile(QStringLiteral("../Image/png/Weather.ico"), QSize(), QIcon::Normal, QIcon::Off);
		Server_VSClass->setWindowIcon(icon);
		Server_VSClass->setWindowOpacity(1);
		Server_VSClass->setStyleSheet(QStringLiteral("background:rgb(100,100,100);color:white "));
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
		centralWidget->setAutoFillBackground(false);
		centralWidget->setStyleSheet(QStringLiteral(""));
		groupBox = new QGroupBox(centralWidget);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(5, 120, 241, 531));

		groupBox->setFont(font);
		ServerList = new SrvTableWidget(groupBox);
		ServerList->setObjectName(QStringLiteral("ServerList"));
		ServerList->setGeometry(QRect(10, 30, 221, 461));
		OnLineCountLabel = new QLabel(groupBox);
		OnLineCountLabel->setObjectName(QStringLiteral("OnLineCountLabel"));
		OnLineCountLabel->setGeometry(QRect(10, 499, 211, 21));
		groupBox_2 = new QGroupBox(centralWidget);
		groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
		groupBox_2->setGeometry(QRect(250, 120, 1011, 531));
		groupBox_2->setFont(font);
		ClientList = new QTableWidget(groupBox_2);
		ClientList->setObjectName(QStringLiteral("ClientList"));
		ClientList->setGeometry(QRect(10, 30, 991, 491));
		ClientList->setStyleSheet(QStringLiteral("QTableWidget{background:rgb(100,100,100);color:white;selection-background-color:rgb(50,50,50);selection-color:white;gridline-color:white }"));
		ImageLabel = new QLabel(centralWidget);
		ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
		ImageLabel->setGeometry(QRect(0, 0, 31, 31));
		ImageLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/weather.png")));
		NameLabel = new QLabel(centralWidget);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(40, 8, 250, 16));

		NameLabel->setFont(font);
		groupBox_SL = new QGroupBox(centralWidget);
		groupBox_SL->setObjectName(QStringLiteral("groupBox_SL"));
		groupBox_SL->setGeometry(QRect(5, 38, 95, 70));
		groupBox_SL->setFont(font);
		ScrollArea_AddBtn = new QScrollArea(groupBox_SL);
		ScrollArea_AddBtn->setObjectName(QStringLiteral("ScrollArea_AddBtn"));
		ScrollArea_AddBtn->setGeometry(QRect(5, 20, 40, 40));
		ScrollArea_AddBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_AddBtn = new QWidget();
		ScrollAreaWidgetContents_AddBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_AddBtn"));
		ScrollAreaWidgetContents_AddBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_AddBtn->setMaximumSize(QSize(40, 40));
		AddBtn = new MyButton("../Image/png/Add.png", 1, ScrollAreaWidgetContents_AddBtn);
		AddBtn->setObjectName(QStringLiteral("AddBtn"));
		AddBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_AddBtn->setWidget(ScrollAreaWidgetContents_AddBtn);
		ScrollArea_RemoveBtn = new QScrollArea(groupBox_SL);
		ScrollArea_RemoveBtn->setObjectName(QStringLiteral("ScrollArea_RemoveBtn"));
		ScrollArea_RemoveBtn->setGeometry(QRect(50, 20, 40, 40));
		ScrollArea_RemoveBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_RemoveBtn = new QWidget();
		ScrollAreaWidgetContents_RemoveBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_RemoveBtn"));
		ScrollAreaWidgetContents_RemoveBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_RemoveBtn->setMaximumSize(QSize(40, 40));
		RemoveBtn = new MyButton("../Image/png/Remove.png", 1, ScrollAreaWidgetContents_RemoveBtn);
		RemoveBtn->setObjectName(QStringLiteral("RemoveBtn"));
		RemoveBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_RemoveBtn->setWidget(ScrollAreaWidgetContents_RemoveBtn);
		/*ScrollArea_UpLoadBtn = new QScrollArea(groupBox_SL);
		ScrollArea_UpLoadBtn->setObjectName(QStringLiteral("ScrollArea_UpLoadBtn"));
		ScrollArea_UpLoadBtn->setGeometry(QRect(95, 20, 40, 40));
		ScrollArea_UpLoadBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_UpLoadBtn = new QWidget();
		ScrollAreaWidgetContents_UpLoadBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_UpLoadBtn"));
		ScrollAreaWidgetContents_UpLoadBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_UpLoadBtn->setMaximumSize(QSize(40, 40));
		UpLoadBtn = new MyButton("../Image/png/UpLoad.png", 1, ScrollAreaWidgetContents_UpLoadBtn);
		UpLoadBtn->setObjectName(QStringLiteral("UpLoadBtn"));
		UpLoadBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_UpLoadBtn->setWidget(ScrollAreaWidgetContents_UpLoadBtn);*/
		groupBox_SYSStatus = new QGroupBox(centralWidget);
		groupBox_SYSStatus->setObjectName(QStringLiteral("groupBox_SYSStatus"));
		groupBox_SYSStatus->setGeometry(QRect(105, 38, 185, 70));
		groupBox_SYSStatus->setFont(font);
		ScrollArea_ControlBtn = new QScrollArea(groupBox_SYSStatus);
		ScrollArea_ControlBtn->setObjectName(QStringLiteral("ScrollArea_ControlBtn"));
		ScrollArea_ControlBtn->setGeometry(QRect(95, 20, 40, 40));
		ScrollArea_ControlBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_ControlBtn = new QWidget();
		ScrollAreaWidgetContents_ControlBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_ControlBtn"));
		ScrollAreaWidgetContents_ControlBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_ControlBtn->setMaximumSize(QSize(40, 40));
		ControlBtn = new MyButton("../Image/png/Control.png", 1, ScrollAreaWidgetContents_ControlBtn);
		ControlBtn->setObjectName(QStringLiteral("ControlBtn"));
		ControlBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_ControlBtn->setWidget(ScrollAreaWidgetContents_ControlBtn);
		ScrollArea_LogBtn = new QScrollArea(groupBox_SYSStatus);
		ScrollArea_LogBtn->setObjectName(QStringLiteral("ScrollArea_LogBtn"));
		ScrollArea_LogBtn->setGeometry(QRect(5, 20, 40, 40));
		ScrollArea_LogBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_LogBtn = new QWidget();
		ScrollAreaWidgetContents_LogBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_LogBtn"));
		ScrollAreaWidgetContents_LogBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_LogBtn->setMaximumSize(QSize(40, 40));
		LogBtn = new MyButton("../Image/png/Log.png", 1, ScrollAreaWidgetContents_LogBtn);
		LogBtn->setObjectName(QStringLiteral("LogBtn"));
		LogBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_LogBtn->setWidget(ScrollAreaWidgetContents_LogBtn);

		ScrollArea_TerminalBtn = new QScrollArea(groupBox_SYSStatus);
		ScrollArea_TerminalBtn->setObjectName(QStringLiteral("ScrollArea_TerminalBtn"));
		ScrollArea_TerminalBtn->setGeometry(QRect(50, 20, 40, 40));
		ScrollArea_TerminalBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_TerminalBtn = new QWidget();
		ScrollAreaWidgetContents_TerminalBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_TerminalBtn"));
		ScrollAreaWidgetContents_TerminalBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_TerminalBtn->setMaximumSize(QSize(40, 40));
		TerminalBtn = new MyButton("../Image/png/Terminal.png", 1, ScrollAreaWidgetContents_TerminalBtn);
		TerminalBtn->setObjectName(QStringLiteral("TerminalBtn"));
		TerminalBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_TerminalBtn->setWidget(ScrollAreaWidgetContents_TerminalBtn);

		ScrollArea_MQBtn = new QScrollArea(groupBox_SYSStatus);
		ScrollArea_MQBtn->setObjectName(QStringLiteral("ScrollArea_MQBtn"));
		ScrollArea_MQBtn->setGeometry(QRect(140, 20, 40, 40));
		ScrollArea_MQBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MQBtn = new QWidget();
		ScrollAreaWidgetContents_MQBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MQBtn"));
		ScrollAreaWidgetContents_MQBtn->setGeometry(QRect(0, 0, 38, 38));
		ScrollAreaWidgetContents_MQBtn->setMaximumSize(QSize(40, 40));
		MQBtn = new MyButton("../Image/png/MQ.png", 1, ScrollAreaWidgetContents_MQBtn);
		MQBtn->setObjectName(QStringLiteral("TerminalBtn"));
		MQBtn->setGeometry(QRect(2, 2, 32, 32));
		ScrollArea_MQBtn->setWidget(ScrollAreaWidgetContents_MQBtn);

		groupBox_SrvGB = new QGroupBox(centralWidget);
		groupBox_SrvGB->setObjectName(QStringLiteral("groupBox_SrvGB"));
		groupBox_SrvGB->setGeometry(QRect(1200, 5, 75, 26));
		ScrollArea_CloseBtn = new QScrollArea(groupBox_SrvGB);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(52, 2, 20, 20));
		ScrollArea_CloseBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_CloseBtn = new QWidget();
		ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
		ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 18, 18));
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
		CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
		CloseBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);
		ScrollArea_MinBtn = new QScrollArea(groupBox_SrvGB);
		ScrollArea_MinBtn->setObjectName(QStringLiteral("ScrollArea_MinBtn"));
		ScrollArea_MinBtn->setGeometry(QRect(27, 2, 20, 20));
		ScrollArea_MinBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MinBtn = new QWidget();
		ScrollAreaWidgetContents_MinBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MinBtn"));
		ScrollAreaWidgetContents_MinBtn->setGeometry(QRect(0, 0, 18, 18));
		MinBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MinBtn);
		MinBtn->setObjectName(QStringLiteral("MinBtn"));
		MinBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_MinBtn->setWidget(ScrollAreaWidgetContents_MinBtn);
		ScrollArea_WarningBtn = new QScrollArea(groupBox_SrvGB);
		ScrollArea_WarningBtn->setObjectName(QStringLiteral("ScrollArea_WarningBtn"));
		ScrollArea_WarningBtn->setGeometry(QRect(2, 2, 20, 20));
		ScrollArea_WarningBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_WarningBtn = new QWidget();
		ScrollAreaWidgetContents_WarningBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_WarningBtn"));
		ScrollAreaWidgetContents_WarningBtn->setGeometry(QRect(0, 0, 18, 18));
		WarningBtn = new MyButton("../Image/png/flag.png", 1, ScrollAreaWidgetContents_WarningBtn);
		WarningBtn->setObjectName(QStringLiteral("WarningBtn"));
		WarningBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_WarningBtn->setWidget(ScrollAreaWidgetContents_WarningBtn);
		Server_VSClass->setCentralWidget(centralWidget);
		WarningDockWidget = new MyDockWidget(QString("±¨¾¯ÐÅÏ¢"));
		WarningDockWidget->setGeometry(1100, 40, 40, 600);
		WarningDockWidget->setStyleSheet("QWidget{background:rgb(100,100,100);color:white}QToolTip { color: white; background-color:rgb(77,77,77); border: none;}");


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
		groupBox->setTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\345\210\227\350\241\250", nullptr));
		OnLineCountLabel->setText(QApplication::translate("Server_VSClass", "TextLabel", nullptr));
		groupBox_2->setTitle(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
		ImageLabel->setText(QString());
		NameLabel->setText(QApplication::translate("Server_VSClass", "\346\260\224\350\261\241\344\270\223\344\270\232\345\271\263\345\217\260", nullptr));
		groupBox_SL->setTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\347\256\241\347\220\206", nullptr));
		AddBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		RemoveBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		//UpLoadBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		groupBox_SYSStatus->setTitle(QApplication::translate("Server_VSClass", "\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
		ControlBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		LogBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		TerminalBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		groupBox_SrvGB->setTitle(QString());
		CloseBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		MinBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
		WarningBtn->setText(QApplication::translate("Server_VSClass", "PushButton", nullptr));
	} // retranslateUi

};

namespace Ui {
	class Server_VSClass : public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_VS_H
