/********************************************************************************
** Form generated from reading UI file 'MQConfigDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQCONFIG_H
#define UI_MQCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_MQConfig
{
public:
	QLabel *TitleLabel_Image;
	QLabel *TitleLabel_Name;
	QGroupBox *groupBox;
	QGroupBox *groupBox_url;
	QPushButton *SetURLBtn;
	QLineEdit *lineEdit_URL;
	QGroupBox *groupBox_admin;
	QPushButton *SetAdminBtn;
	QLineEdit *lineEdit_admin;
	QGroupBox *groupBox_password;
	QPushButton *SetPasswordBtn;
	QLineEdit *lineEdit_password;
	QGroupBox *groupBox_1;
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;
	QScrollArea *ScrollArea_MinBtn;
	QWidget *ScrollAreaWidgetContents_MinBtn;
	MyButton *MinBtn;

	void setupUi(QWidget *MQConfig)
	{
		if (MQConfig->objectName().isEmpty())
			MQConfig->setObjectName(QStringLiteral("MQConfig"));
		MQConfig->setWindowModality(Qt::WindowModal);
		MQConfig->resize(302, 380);
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(9);
		MQConfig->setFont(font);
		QIcon icon;
		icon.addFile(QStringLiteral("../Image/png/mq.png"), QSize(), QIcon::Normal, QIcon::Off);
		MQConfig->setWindowIcon(icon);
		MQConfig->setStyleSheet(QStringLiteral("background:rgb(77,77,77);color:white"));

		TitleLabel_Image = new QLabel(MQConfig);
		TitleLabel_Image->setObjectName(QStringLiteral("TitleLabel_Image"));
		TitleLabel_Image->setGeometry(QRect(10, 5, 32, 32));
		TitleLabel_Image->setPixmap(QPixmap(QString::fromUtf8("../Image/png/control.png")));
		TitleLabel_Name = new QLabel(MQConfig);
		TitleLabel_Name->setObjectName(QStringLiteral("TitleLabel_Name"));
		TitleLabel_Name->setGeometry(QRect(45, 10, 100, 16));
		TitleLabel_Name->setText(QString::fromLocal8Bit("消息中间件"));
		groupBox = new QGroupBox(MQConfig);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(10, 40, 281, 311));
		groupBox_url = new QGroupBox(groupBox);
		groupBox_url->setObjectName(QStringLiteral("groupBox_url"));
		groupBox_url->setGeometry(QRect(10, 10, 251, 91));
		SetURLBtn = new QPushButton(groupBox_url);
		SetURLBtn->setObjectName(QStringLiteral("SetURLBtn"));
		SetURLBtn->setGeometry(QRect(10, 50, 75, 23));
		lineEdit_URL = new QLineEdit(groupBox_url);
		lineEdit_URL->setObjectName(QStringLiteral("lineEdit_URL"));
		lineEdit_URL->setGeometry(QRect(10, 20, 181, 20));
		groupBox_admin = new QGroupBox(groupBox);
		groupBox_admin->setObjectName(QStringLiteral("groupBox_admin"));
		groupBox_admin->setGeometry(QRect(10, 110, 171, 91));
		SetAdminBtn = new QPushButton(groupBox_admin);
		SetAdminBtn->setObjectName(QStringLiteral("SetAdminBtn"));
		SetAdminBtn->setGeometry(QRect(10, 50, 75, 23));
		lineEdit_admin = new QLineEdit(groupBox_admin);
		lineEdit_admin->setObjectName(QStringLiteral("lineEdit_admin"));
		lineEdit_admin->setGeometry(QRect(10, 20, 151, 20));
		groupBox_password = new QGroupBox(groupBox);
		groupBox_password->setObjectName(QStringLiteral("groupBox_password"));
		groupBox_password->setGeometry(QRect(10, 210, 171, 91));
		SetPasswordBtn = new QPushButton(groupBox_password);
		SetPasswordBtn->setObjectName(QStringLiteral("SetPasswordBtn"));
		SetPasswordBtn->setGeometry(QRect(10, 50, 75, 23));
		lineEdit_password = new QLineEdit(groupBox_password);
		lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
		lineEdit_password->setGeometry(QRect(10, 20, 151, 20));

		groupBox_1 = new QGroupBox(MQConfig);
		groupBox_1->setObjectName(QStringLiteral("groupBox_1"));
		groupBox_1->setGeometry(QRect(240, 5, 52, 26));
		ScrollArea_CloseBtn = new QScrollArea(groupBox_1);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(27, 2, 20, 20));
		ScrollArea_CloseBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_CloseBtn = new QWidget();
		ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
		ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 18, 18));
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
		CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
		CloseBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);
		ScrollArea_MinBtn = new QScrollArea(groupBox_1);
		ScrollArea_MinBtn->setObjectName(QStringLiteral("ScrollArea_MinBtn"));
		ScrollArea_MinBtn->setGeometry(QRect(4, 2, 20, 20));
		ScrollArea_MinBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MinBtn = new QWidget();
		ScrollAreaWidgetContents_MinBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MinBtn"));
		ScrollAreaWidgetContents_MinBtn->setGeometry(QRect(0, 0, 18, 18));
		MinBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MinBtn);
		MinBtn->setObjectName(QStringLiteral("MinBtn"));
		MinBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_MinBtn->setWidget(ScrollAreaWidgetContents_MinBtn);
		QWidget::setTabOrder(lineEdit_URL, SetURLBtn);
		QWidget::setTabOrder(SetURLBtn, lineEdit_admin);
		QWidget::setTabOrder(lineEdit_admin, SetAdminBtn);
		QWidget::setTabOrder(SetAdminBtn, lineEdit_password);
		QWidget::setTabOrder(lineEdit_password, SetPasswordBtn);

		retranslateUi(MQConfig);

		QMetaObject::connectSlotsByName(MQConfig);
	} // setupUi

	void retranslateUi(QWidget *MQConfig)
	{
		MQConfig->setWindowTitle(QApplication::translate("MQConfig", "\347\273\210\347\253\257\346\216\247\345\210\266", nullptr));
		groupBox->setTitle(QString());
		groupBox_url->setTitle(QApplication::translate("MQConfig", "ULR", nullptr));
		SetURLBtn->setText(QApplication::translate("MQConfig", "\350\256\276\347\275\256", nullptr));
		lineEdit_URL->setText(QApplication::translate("MQConfig", "tcp://117.158.216.250:61616", nullptr));
		groupBox_admin->setTitle(QApplication::translate("MQConfig", "\350\264\246\346\210\267\345\220\215", nullptr));
		SetAdminBtn->setText(QApplication::translate("MQConfig", "\350\256\276\347\275\256", nullptr));
		groupBox_password->setTitle(QApplication::translate("MQConfig", "\345\257\206\347\240\201", nullptr));
		SetPasswordBtn->setText(QApplication::translate("MQConfig", "\350\256\276\347\275\256", nullptr));
	} // retranslateUi

};

namespace Ui {
	class MQConfigDlg : public Ui_MQConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQCONFIG_H
