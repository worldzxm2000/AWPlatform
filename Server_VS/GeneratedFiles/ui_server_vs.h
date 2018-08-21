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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "SrvTableWidget.h"
#include "MyButton.h"
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
	QGroupBox *groupBox_2;
	QGroupBox *groupBox_3;
	QGroupBox *groupBox_4;
	SrvTableWidget *ServerList;

	QTableWidget *ClientList;


	QLabel *ImageLabel;
	QLabel *NameLabel;

	QScrollArea *ScrollArea_AddBtn;
	QWidget *ScrollAreaWidgetContents_AddBtn;
	MyButton *AddBtn;


	QScrollArea *ScrollArea_RemoveBtn;
	QWidget *ScrollAreaWidgetContents_RemoveBtn;
	MyButton *RemoveBtn;


	//QScrollArea *ScrollArea_RunBtn;
	//QWidget *ScrollAreaWidgetContents_RunBtn;
	//MyButton *RunBtn;


	//QScrollArea *ScrollArea_PauseBtn;
	//QWidget *ScrollAreaWidgetContents_PauseBtn;
	//MyButton *PauseBtn;

	QScrollArea *ScrollArea_LogBtn;
	QWidget *ScrollAreaWidgetContents_LogBtn;
	MyButton *LogBtn;

	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;

	QScrollArea *ScrollArea_MiniBtn;
	QWidget *ScrollAreaWidgetContents_MiniBtn;
	MyButton *MiniBtn;
	void setupUi(QMainWindow *Server_VSClass)
	{
		if (Server_VSClass->objectName().isEmpty())
			Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
		Server_VSClass->resize(1280, 768);
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(10);
		QIcon icon("../Image/Weather.ico");
		Server_VSClass->setWindowIcon(icon);
		Server_VSClass->setWindowIconText("气象专业平台");
		Server_VSClass->setFont(font);
		Server_VSClass->setWindowOpacity(1);
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
		Server_VSClass->setStyleSheet(QString("QMainWindow{ background:rgb(100,100,100);color:white }"));
		//centralWidget->setStyleSheet(QString("QWidget{color:white}"));
		groupBox = new QGroupBox(centralWidget);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(5, 120, 241, 531));
		groupBox->setStyleSheet(QString("QGroupBox{color:white}"));

		groupBox->setFont(font);
		ServerList = new SrvTableWidget(groupBox);
		ServerList->setObjectName(QStringLiteral("ServerList"));
		ServerList->setGeometry(QRect(10, 30, 221, 491));
		ServerList->setStyleSheet(QStringLiteral("QTableWidget{background:rgb(100,100,100);color:white;selection-background-color:rgb(50,50,50)}"));
		//ServerList->setStyleSheet(QStringLiteral("QTableWidget::item{ selection-background-color: red}"));
		groupBox_2 = new QGroupBox(centralWidget);
		groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
		groupBox_2->setGeometry(QRect(250, 120, 1011, 531));
		groupBox_2->setFont(font);
		groupBox_2->setStyleSheet(QString("QGroupBox{color:white}"));
		ClientList = new QTableWidget(groupBox_2);
		ClientList->setObjectName(QStringLiteral("ClientList"));
		ClientList->setGeometry(QRect(10, 30, 991, 481));
		ClientList->setStyleSheet(QStringLiteral("QTableWidget{background:rgb(100,100,100);color:white;}"));

		ImageLabel = new QLabel(centralWidget);
		ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
		ImageLabel->setGeometry(QRect(5, 2, 31, 31));
		ImageLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/7.png")));
		NameLabel = new QLabel(centralWidget);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(40, 5, 200, 20));
		NameLabel->setStyleSheet(QString("QLabel{color:white}"));
		QFont font_NameLabel;
		font_NameLabel.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font_NameLabel.setPointSize(10);
		NameLabel->setFont(font_NameLabel);

		//业务管理
		groupBox_3 = new QGroupBox(centralWidget);
		groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
		groupBox_3->setGeometry(QRect(5, 38, 185, 70));
		groupBox_3->setStyleSheet(QString("QGroupBox{color:white}"));
		groupBox_3->setFont(font);

		//系统运行
		groupBox_4 = new QGroupBox(centralWidget);
		groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
		groupBox_4->setGeometry(QRect(195, 38, 185, 70));
		groupBox_4->setStyleSheet(QString("QGroupBox{color:white}"));
		groupBox_4->setFont(font);

		//添加按钮
		ScrollArea_AddBtn = new QScrollArea(groupBox_3);
		ScrollArea_AddBtn->setObjectName(QStringLiteral("ScrollArea_AddBtn"));
		ScrollArea_AddBtn->setGeometry(QRect(5, 20, 40, 40));
		ScrollArea_AddBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_AddBtn = new QWidget();
		ScrollAreaWidgetContents_AddBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_AddBtn"));
		ScrollAreaWidgetContents_AddBtn->setGeometry(QRect(0, 0, 40, 40));
		ScrollArea_AddBtn->setWidget(ScrollAreaWidgetContents_AddBtn);
		ScrollAreaWidgetContents_AddBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		AddBtn = new MyButton("../Image/png/Add.png", 1, ScrollAreaWidgetContents_AddBtn);
		AddBtn->setObjectName(QStringLiteral("AddBtn"));
		AddBtn->setGeometry(QRect(2, 2, 32, 32));

		//移除按钮
		ScrollArea_RemoveBtn = new QScrollArea(groupBox_3);
		ScrollArea_RemoveBtn->setObjectName(QStringLiteral("ScrollArea_RemoveBtn"));
		ScrollArea_RemoveBtn->setGeometry(QRect(50, 20, 40, 40));
		ScrollArea_RemoveBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_RemoveBtn = new QWidget();
		ScrollAreaWidgetContents_RemoveBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_RemoveBtn"));
		ScrollAreaWidgetContents_RemoveBtn->setGeometry(QRect(0, 0, 40, 40));
		ScrollArea_RemoveBtn->setWidget(ScrollAreaWidgetContents_RemoveBtn);
		ScrollAreaWidgetContents_RemoveBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		RemoveBtn = new MyButton("../Image/png/Remove.png", 1, ScrollAreaWidgetContents_RemoveBtn);
		RemoveBtn->setObjectName(QStringLiteral("RemoveBtn"));
		RemoveBtn->setGeometry(QRect(2, 2, 32, 32));

		////启动按钮
		//ScrollArea_RunBtn = new QScrollArea(groupBox_3);
		//ScrollArea_RunBtn->setObjectName(QStringLiteral("ScrollArea_RunBtn"));
		//ScrollArea_RunBtn->setGeometry(QRect(95, 20, 40, 40));
		//ScrollArea_RunBtn->setWidgetResizable(true);
		//ScrollAreaWidgetContents_RunBtn = new QWidget();
		//ScrollAreaWidgetContents_RunBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_RunBtn"));
		//ScrollAreaWidgetContents_RunBtn->setGeometry(QRect(0, 0, 40, 40));
		//ScrollAreaWidgetContents_RunBtn->setStyleSheet(QString("QWidget{ background:black }"));
		//ScrollArea_RunBtn->setWidget(ScrollAreaWidgetContents_RunBtn);
		//RunBtn = new MyButton("../Image/png/Run.png", 1, ScrollAreaWidgetContents_RunBtn);
		//RunBtn->setObjectName(QStringLiteral("RunBtn"));
		//RunBtn->setGeometry(QRect(2, 2, 32, 32));

		////暂停按钮
		//ScrollArea_PauseBtn = new QScrollArea(groupBox_3);
		//ScrollArea_PauseBtn->setObjectName(QStringLiteral("ScrollArea_PauseBtn"));
		//ScrollArea_PauseBtn->setGeometry(QRect(140, 20, 40, 40));
		//ScrollArea_PauseBtn->setWidgetResizable(true);
		//ScrollAreaWidgetContents_PauseBtn = new QWidget();
		//ScrollAreaWidgetContents_PauseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_PauseBtn"));
		//ScrollAreaWidgetContents_PauseBtn->setGeometry(QRect(0, 0, 40, 40));
		//ScrollAreaWidgetContents_PauseBtn->setStyleSheet(QString("QWidget{ background:black }"));
		//ScrollArea_PauseBtn->setWidget(ScrollAreaWidgetContents_PauseBtn);
		//PauseBtn = new MyButton("../Image/png/Pause.png", 1, ScrollAreaWidgetContents_PauseBtn);
		//PauseBtn->setObjectName(QStringLiteral("PauseBtn"));
		//PauseBtn->setGeometry(QRect(2, 2, 32, 32));

		//日志显示
		ScrollArea_LogBtn = new QScrollArea(groupBox_4);
		ScrollArea_LogBtn->setObjectName(QStringLiteral("ScrollArea_LogBtn"));
		ScrollArea_LogBtn->setGeometry(QRect(5, 20, 40, 40));
		ScrollArea_LogBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_LogBtn = new QWidget();
		ScrollAreaWidgetContents_LogBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_LogBtn"));
		ScrollAreaWidgetContents_LogBtn->setGeometry(QRect(0, 0, 40, 40));
		ScrollAreaWidgetContents_LogBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_LogBtn->setWidget(ScrollAreaWidgetContents_LogBtn);
		LogBtn = new MyButton("../Image/png/Log.png", 1, ScrollAreaWidgetContents_LogBtn);
		LogBtn->setObjectName(QStringLiteral("LogBtn"));
		LogBtn->setGeometry(QRect(2, 2, 32, 32));


		//关闭窗体
		ScrollArea_CloseBtn = new QScrollArea(centralWidget);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(1258, 2, 20, 20));
		ScrollArea_CloseBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_CloseBtn = new QWidget();
		ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
		ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 20, 20));
		ScrollAreaWidgetContents_CloseBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
		CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
		CloseBtn->setGeometry(QRect(2, 2, 16, 16));

		//最小化窗体
		ScrollArea_MiniBtn = new QScrollArea(centralWidget);
		ScrollArea_MiniBtn->setObjectName(QStringLiteral("ScrollArea_MiniBtn"));
		ScrollArea_MiniBtn->setGeometry(QRect(1236, 2, 20, 20));
		ScrollArea_MiniBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MiniBtn = new QWidget();
		ScrollAreaWidgetContents_MiniBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MiniBtn"));
		ScrollAreaWidgetContents_MiniBtn->setGeometry(QRect(0, 0, 20, 20));
		ScrollAreaWidgetContents_MiniBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_MiniBtn->setWidget(ScrollAreaWidgetContents_MiniBtn);
		MiniBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MiniBtn);
		MiniBtn->setObjectName(QStringLiteral("MiniBtn"));
		MiniBtn->setGeometry(QRect(2, 2, 16, 16));
		Server_VSClass->setCentralWidget(centralWidget);
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
		groupBox_2->setTitle(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
		groupBox_3->setTitle("业务管理");
		groupBox_4->setTitle("系统状态");
		ImageLabel->setText(QString());
		NameLabel->setText(QApplication::translate("Server_VSClass", "\346\260\224\350\261\241\344\270\223\344\270\232\345\271\263\345\217\260", nullptr));
		AddBtn->setToolTipName("添加新业务");
		RemoveBtn->setToolTipName("移除业务");
	/*	RunBtn->setToolTipName("运行");
		PauseBtn->setToolTipName("暂停");*/
		LogBtn->setToolTipName("查看日志");
		CloseBtn->setToolTipName("关闭");
		MiniBtn->setToolTipName("最小化");
		// label->setText(QApplication::translate("Server_VSClass", "\346\226\260\345\242\236\344\270\232\345\212\241", nullptr));
	} // retranslateUi

};

namespace Ui {
	class Server_VSClass : public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_VS_H
