/********************************************************************************
** Form generated from reading UI file 'ControlDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLDLG_H
#define UI_CONTROLDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_ControlDlg
{
public:
	QGroupBox *groupBox_4;
	QLabel *label;
	QLabel *label_4;
	QGroupBox *groupBox;
	QLabel *NameLabel;
	QLabel *StationIDLabel;
	QLabel *SrvNameLabel;
	QGroupBox *groupBox_2;
	QWidget *verticalLayoutWidget;
	QVBoxLayout *verticalLayout;
	QPushButton *R_BASEINFO_Btn;
	QPushButton *R_DATETIME_Btn;
	QPushButton *R_LONG_Btn;
	QPushButton *R_LAT_Btn;
	QPushButton *R_ALT_Btn;
	QPushButton *R_SNAPSHOT_Btn;
	QGroupBox *groupBox_3;
	QWidget *verticalLayoutWidget_3;
	QVBoxLayout *verticalLayout_3;
	QPushButton *W_DATETIME_Btn;
	QPushButton *W_LONG_Btn;
	QPushButton *W_LAT_Btn;
	QPushButton *W_ALT_Btn;
	QLineEdit *ParamsEdit;
	QGroupBox *groupBox_5;
	QDateTimeEdit *dateTimeEdit_B;
	QDateTimeEdit *dateTimeEdit_E;
	QPushButton *R_DMTD_Btn;
	QGroupBox *groupBox_6;
	QScrollArea *ScrollArea_MinBtn;
	QWidget *ScrollAreaWidgetContents_MinBtn;
	MyButton *MinBtn;
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;

	void setupUi(QWidget *ControlDlg)
	{
		if (ControlDlg->objectName().isEmpty())
			ControlDlg->setObjectName(QStringLiteral("ControlDlg"));
		ControlDlg->resize(390, 472);
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(10);
		ControlDlg->setFont(font);
		QIcon icon;
		icon.addFile(QStringLiteral("../Image/png/control.png"), QSize(), QIcon::Normal, QIcon::Off);
		ControlDlg->setWindowIcon(icon);
		ControlDlg->setStyleSheet(QStringLiteral(""));
		groupBox_4 = new QGroupBox(ControlDlg);
		groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
		groupBox_4->setGeometry(QRect(0, 0, 390, 471));
		groupBox_4->setStyleSheet(QStringLiteral("background:rgb(77, 77, 77);color:white"));
		label = new QLabel(groupBox_4);
		label->setObjectName(QStringLiteral("label"));
		label->setGeometry(QRect(5, 2, 32, 32));
		label->setPixmap(QPixmap(QString::fromUtf8("../Image/png/control.png")));
		label_4 = new QLabel(groupBox_4);
		label_4->setObjectName(QStringLiteral("label_4"));
		label_4->setGeometry(QRect(40, 8, 80, 15));
		label_4->setFont(font);
		groupBox = new QGroupBox(groupBox_4);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(10, 40, 361, 421));
		NameLabel = new QLabel(groupBox);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(10, 12, 80, 16));
		StationIDLabel = new QLabel(groupBox);
		StationIDLabel->setObjectName(QStringLiteral("StationIDLabel"));
		StationIDLabel->setGeometry(QRect(95, 12, 100, 16));
		SrvNameLabel = new QLabel(groupBox);
		SrvNameLabel->setObjectName(QStringLiteral("SrvNameLabel"));
		SrvNameLabel->setGeometry(QRect(200, 12, 150, 16));
		groupBox_2 = new QGroupBox(groupBox);
		groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
		groupBox_2->setGeometry(QRect(20, 50, 141, 271));
		verticalLayoutWidget = new QWidget(groupBox_2);
		verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
		verticalLayoutWidget->setGeometry(QRect(30, 20, 88, 241));
		verticalLayout = new QVBoxLayout(verticalLayoutWidget);
		verticalLayout->setSpacing(6);
		verticalLayout->setContentsMargins(11, 11, 11, 11);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		R_BASEINFO_Btn = new QPushButton(verticalLayoutWidget);
		R_BASEINFO_Btn->setObjectName(QStringLiteral("R_BASEINFO_Btn"));

		verticalLayout->addWidget(R_BASEINFO_Btn);

		R_DATETIME_Btn = new QPushButton(verticalLayoutWidget);
		R_DATETIME_Btn->setObjectName(QStringLiteral("R_DATETIME_Btn"));

		verticalLayout->addWidget(R_DATETIME_Btn);

		R_LONG_Btn = new QPushButton(verticalLayoutWidget);
		R_LONG_Btn->setObjectName(QStringLiteral("R_LONG_Btn"));

		verticalLayout->addWidget(R_LONG_Btn);

		R_LAT_Btn = new QPushButton(verticalLayoutWidget);
		R_LAT_Btn->setObjectName(QStringLiteral("R_LAT_Btn"));

		verticalLayout->addWidget(R_LAT_Btn);

		R_ALT_Btn = new QPushButton(verticalLayoutWidget);
		R_ALT_Btn->setObjectName(QStringLiteral("R_ALT_Btn"));

		verticalLayout->addWidget(R_ALT_Btn);

		R_SNAPSHOT_Btn = new QPushButton(verticalLayoutWidget);
		R_SNAPSHOT_Btn->setObjectName(QStringLiteral("R_SNAPSHOT_Btn"));

		verticalLayout->addWidget(R_SNAPSHOT_Btn);

		groupBox_3 = new QGroupBox(groupBox);
		groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
		groupBox_3->setGeometry(QRect(180, 50, 151, 271));
		verticalLayoutWidget_3 = new QWidget(groupBox_3);
		verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
		verticalLayoutWidget_3->setGeometry(QRect(40, 50, 88, 211));
		verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
		verticalLayout_3->setSpacing(6);
		verticalLayout_3->setContentsMargins(11, 11, 11, 11);
		verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
		verticalLayout_3->setContentsMargins(0, 0, 0, 0);
		W_DATETIME_Btn = new QPushButton(verticalLayoutWidget_3);
		W_DATETIME_Btn->setObjectName(QStringLiteral("W_DATETIME_Btn"));

		verticalLayout_3->addWidget(W_DATETIME_Btn);

		W_LONG_Btn = new QPushButton(verticalLayoutWidget_3);
		W_LONG_Btn->setObjectName(QStringLiteral("W_LONG_Btn"));

		verticalLayout_3->addWidget(W_LONG_Btn);

		W_LAT_Btn = new QPushButton(verticalLayoutWidget_3);
		W_LAT_Btn->setObjectName(QStringLiteral("W_LAT_Btn"));

		verticalLayout_3->addWidget(W_LAT_Btn);

		W_ALT_Btn = new QPushButton(verticalLayoutWidget_3);
		W_ALT_Btn->setObjectName(QStringLiteral("W_ALT_Btn"));

		verticalLayout_3->addWidget(W_ALT_Btn);

		ParamsEdit = new QLineEdit(groupBox_3);
		ParamsEdit->setObjectName(QStringLiteral("ParamsEdit"));
		ParamsEdit->setGeometry(QRect(20, 20, 121, 20));
		groupBox_5 = new QGroupBox(groupBox);
		groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
		groupBox_5->setGeometry(QRect(20, 329, 311, 71));
		dateTimeEdit_B = new QDateTimeEdit(groupBox_5);
		dateTimeEdit_B->setObjectName(QStringLiteral("dateTimeEdit_B"));
		dateTimeEdit_B->setGeometry(QRect(10, 10, 194, 22));
		dateTimeEdit_E = new QDateTimeEdit(groupBox_5);
		dateTimeEdit_E->setObjectName(QStringLiteral("dateTimeEdit_E"));
		dateTimeEdit_E->setGeometry(QRect(10, 40, 194, 22));
		R_DMTD_Btn = new QPushButton(groupBox_5);
		R_DMTD_Btn->setObjectName(QStringLiteral("R_DMTD_Btn"));
		R_DMTD_Btn->setGeometry(QRect(210, 20, 86, 27));
		groupBox_6 = new QGroupBox(groupBox_4);
		groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
		groupBox_6->setGeometry(QRect(340, 5, 46, 26));
		ScrollArea_MinBtn = new QScrollArea(groupBox_6);
		ScrollArea_MinBtn->setObjectName(QStringLiteral("ScrollArea_MinBtn"));
		ScrollArea_MinBtn->setGeometry(QRect(2, 3, 20, 20));
		ScrollArea_MinBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MinBtn = new QWidget();
		ScrollAreaWidgetContents_MinBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MinBtn"));
		ScrollAreaWidgetContents_MinBtn->setGeometry(QRect(0, 0, 18, 18));
		MinBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MinBtn);
		MinBtn->setObjectName(QStringLiteral("MinBtn"));
		MinBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_MinBtn->setWidget(ScrollAreaWidgetContents_MinBtn);
		ScrollArea_CloseBtn = new QScrollArea(groupBox_6);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(24, 3, 20, 20));
		ScrollArea_CloseBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_CloseBtn = new QWidget();
		ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
		ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 18, 18));
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
		CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
		CloseBtn->setGeometry(QRect(1, 1, 16, 16));
		ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);

		retranslateUi(ControlDlg);

		QMetaObject::connectSlotsByName(ControlDlg);
	} // setupUi

	void retranslateUi(QWidget *ControlDlg)
	{
		ControlDlg->setWindowTitle(QApplication::translate("ControlDlg", "\346\216\247\345\210\266\350\256\276\345\244\207", nullptr));
#ifndef QT_NO_STATUSTIP
		ControlDlg->setStatusTip(QApplication::translate("ControlDlg", "\345\221\275\344\273\244\346\216\247\345\210\266", nullptr));
#endif // QT_NO_STATUSTIP
		groupBox_4->setTitle(QString());
		label->setText(QString());
		label_4->setText(QApplication::translate("ControlDlg", "\350\256\276\345\244\207\346\216\247\345\210\266", nullptr));
		groupBox->setTitle(QString());
		NameLabel->setText(QApplication::translate("ControlDlg", "\345\275\223\345\211\215\351\200\211\346\213\251\347\253\231\347\202\271\357\274\232", nullptr));
		StationIDLabel->setText(QString());
		SrvNameLabel->setText(QApplication::translate("ControlDlg", "\347\261\273\345\236\213\357\274\232", nullptr));
		groupBox_2->setTitle(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\345\221\275\344\273\244", nullptr));
		R_BASEINFO_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\345\237\272\346\234\254\344\277\241\346\201\257", nullptr));
		R_DATETIME_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\346\227\266\351\222\237", nullptr));
		R_LONG_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\347\273\217\345\272\246", nullptr));
		R_LAT_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\347\272\254\345\272\246", nullptr));
		R_ALT_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\346\265\267\346\213\224\351\253\230\345\272\246", nullptr));
		R_SNAPSHOT_Btn->setText(QApplication::translate("ControlDlg", "\350\257\273\345\217\226\346\225\260\346\215\256", nullptr));
		groupBox_3->setTitle(QApplication::translate("ControlDlg", "\350\256\276\347\275\256\345\221\275\344\273\244", nullptr));
		W_DATETIME_Btn->setText(QApplication::translate("ControlDlg", "\350\256\276\347\275\256\346\227\266\351\222\237", nullptr));
		W_LONG_Btn->setText(QApplication::translate("ControlDlg", "\350\256\276\347\275\256\347\273\217\345\272\246", nullptr));
		W_LAT_Btn->setText(QApplication::translate("ControlDlg", "\350\256\276\347\275\256\347\272\254\345\272\246", nullptr));
		W_ALT_Btn->setText(QApplication::translate("ControlDlg", "\350\256\276\347\275\256\346\265\267\346\213\224\351\253\230\345\272\246", nullptr));
		groupBox_5->setTitle(QString());
		R_DMTD_Btn->setText(QApplication::translate("ControlDlg", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
		groupBox_6->setTitle(QString());
		MinBtn->setText(QApplication::translate("ControlDlg", "PushButton", nullptr));
		CloseBtn->setText(QApplication::translate("ControlDlg", "PushButton", nullptr));
	} // retranslateUi

};

namespace Ui {
	class ControlDlg : public Ui_ControlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLDLG_H
