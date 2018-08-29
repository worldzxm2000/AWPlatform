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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include<QScrollArea>
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_ControlDlg
{
public:
    QGroupBox *groupBox_4;
    QLabel *label;
    QLabel *label_4;
    QGroupBox *groupBox;
    QLabel *SrvNameLabel;
    QLabel *StationIDLabel;
    QLabel *NameLabel;
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
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;

	QScrollArea *ScrollArea_MiniBtn;
	QWidget *ScrollAreaWidgetContents_MiniBtn;
	MyButton *MiniBtn;
    void setupUi(QWidget *ControlDlg)
    {
        if (ControlDlg->objectName().isEmpty())
            ControlDlg->setObjectName(QStringLiteral("ControlDlg"));
        ControlDlg->resize(398, 400);
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
        groupBox_4->setGeometry(QRect(0, 0, 391, 391));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(5, 2, 32, 32));
        label->setPixmap(QPixmap(QString::fromUtf8("../Image/png/control.png")));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 8, 50, 15));
        QFont font1;
        font1.setPointSize(8);
        label_4->setFont(font1);
        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 361, 331));
        SrvNameLabel = new QLabel(groupBox);
        SrvNameLabel->setObjectName(QStringLiteral("SrvNameLabel"));
        SrvNameLabel->setGeometry(QRect(230, 12, 100, 16));
        StationIDLabel = new QLabel(groupBox);
        StationIDLabel->setObjectName(QStringLiteral("StationIDLabel"));
        StationIDLabel->setGeometry(QRect(80, 12, 100, 16));
		NameLabel = new QLabel(groupBox);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(20, 12, 50, 16));
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

		groupBox_5 = new QGroupBox(ControlDlg);
		groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
		groupBox_5->setGeometry(QRect(335, 2, 50, 26));
		groupBox_5->setStyleSheet(QString("QGroupBox{color:white}"));
		groupBox_5->setFont(font);
		//关闭窗体
		ScrollArea_CloseBtn = new QScrollArea(groupBox_5);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(27, 2, 20, 20));
		ScrollArea_CloseBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_CloseBtn = new QWidget();
		ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
		ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 20, 20));
		ScrollAreaWidgetContents_CloseBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
		CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
		CloseBtn->setGeometry(QRect(1, 1, 16, 16));

		//最小化窗体
		ScrollArea_MiniBtn = new QScrollArea(groupBox_5);
		ScrollArea_MiniBtn->setObjectName(QStringLiteral("ScrollArea_MiniBtn"));
		ScrollArea_MiniBtn->setGeometry(QRect(2, 2, 20, 20));
		ScrollArea_MiniBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MiniBtn = new QWidget();
		ScrollAreaWidgetContents_MiniBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MiniBtn"));
		ScrollAreaWidgetContents_MiniBtn->setGeometry(QRect(0, 0, 20, 20));
		ScrollAreaWidgetContents_MiniBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_MiniBtn->setWidget(ScrollAreaWidgetContents_MiniBtn);
		MiniBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MiniBtn);
		MiniBtn->setObjectName(QStringLiteral("MiniBtn"));
		MiniBtn->setGeometry(QRect(1, 1, 16, 16));
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
		NameLabel->setText(QString::fromLocal8Bit("站点号："));
       // SrvNameLabel->setText(QApplication::translate("ControlDlg", "\347\253\231\347\202\271\345\217\267", nullptr));
      //  StationIDLabel->setText(QApplication::translate("ControlDlg", "\345\275\223\345\211\215\351\200\211\346\213\251\347\253\231\347\202\271\357\274\232", nullptr));
		//NameLabel->setText(QApplication::translate("ControlDlg", "\347\261\273\345\236\213\357\274\232", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class ControlDlg: public Ui_ControlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLDLG_H
