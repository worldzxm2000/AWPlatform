/********************************************************************************
** Form generated from reading UI file 'SYSLogDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSLOGDLG_H
#define UI_SYSLOGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_SYSLogDlg
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *CurrentPageLabel;
    QLabel *TotalPageabel;
    QPushButton *PageToBeginBtn;
    QPushButton *PageDownBtn;
    QPushButton *PageUpBtn;
    QPushButton *PageToEndBtn;
    QTableWidget *DataListTable;
    QLabel *ImageLabel;
    QLabel *NameLabel;
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;

	QScrollArea *ScrollArea_MiniBtn;
	QWidget *ScrollAreaWidgetContents_MiniBtn;
	MyButton *MiniBtn;
    void setupUi(QDialog *SYSLogDlg)
    {
        if (SYSLogDlg->objectName().isEmpty())
            SYSLogDlg->setObjectName(QStringLiteral("SYSLogDlg"));
        SYSLogDlg->setWindowModality(Qt::NonModal);
        SYSLogDlg->setEnabled(true);
        SYSLogDlg->resize(623, 482);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        SYSLogDlg->setFont(font);
		QIcon icon("../Image/setup.ico");
		SYSLogDlg->setWindowIcon(icon);
        SYSLogDlg->setStyleSheet(QStringLiteral("background:rgb(77, 77, 77);color:white"));
        horizontalLayoutWidget = new QWidget(SYSLogDlg);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(90, 430, 431, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        CurrentPageLabel = new QLabel(horizontalLayoutWidget);
        CurrentPageLabel->setObjectName(QStringLiteral("CurrentPageLabel"));

        horizontalLayout->addWidget(CurrentPageLabel);

        TotalPageabel = new QLabel(horizontalLayoutWidget);
        TotalPageabel->setObjectName(QStringLiteral("TotalPageabel"));

        horizontalLayout->addWidget(TotalPageabel);

        PageToBeginBtn = new QPushButton(horizontalLayoutWidget);
        PageToBeginBtn->setObjectName(QStringLiteral("PageToBeginBtn"));

        horizontalLayout->addWidget(PageToBeginBtn);

        PageDownBtn = new QPushButton(horizontalLayoutWidget);
        PageDownBtn->setObjectName(QStringLiteral("PageDownBtn"));

        horizontalLayout->addWidget(PageDownBtn);

        PageUpBtn = new QPushButton(horizontalLayoutWidget);
        PageUpBtn->setObjectName(QStringLiteral("PageUpBtn"));

        horizontalLayout->addWidget(PageUpBtn);

        PageToEndBtn = new QPushButton(horizontalLayoutWidget);
        PageToEndBtn->setObjectName(QStringLiteral("PageToEndBtn"));

        horizontalLayout->addWidget(PageToEndBtn);

        DataListTable = new QTableWidget(SYSLogDlg);
        DataListTable->setObjectName(QStringLiteral("DataListTable"));
        DataListTable->setGeometry(QRect(10, 40, 601, 371));
		ImageLabel = new QLabel(SYSLogDlg);
		ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
		ImageLabel->setGeometry(QRect(5, 2, 31, 31));
		ImageLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/logicon.png")));
		NameLabel = new QLabel(SYSLogDlg);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(40, 5, 200, 20));
		NameLabel->setStyleSheet(QString("QLabel{color:white}"));
		NameLabel->setText(QString::fromLocal8Bit("系统日志"));

		//关闭窗体
		ScrollArea_CloseBtn = new QScrollArea(SYSLogDlg);
		ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
		ScrollArea_CloseBtn->setGeometry(QRect(600, 2, 20, 20));
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
		ScrollArea_MiniBtn = new QScrollArea(SYSLogDlg);
		ScrollArea_MiniBtn->setObjectName(QStringLiteral("ScrollArea_MiniBtn"));
		ScrollArea_MiniBtn->setGeometry(QRect(575, 2, 20, 20));
		ScrollArea_MiniBtn->setWidgetResizable(true);
		ScrollAreaWidgetContents_MiniBtn = new QWidget();
		ScrollAreaWidgetContents_MiniBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MiniBtn"));
		ScrollAreaWidgetContents_MiniBtn->setGeometry(QRect(0, 0, 20, 20));
		ScrollAreaWidgetContents_MiniBtn->setStyleSheet(QString("QWidget{ background:rgb(100,100,100) }"));
		ScrollArea_MiniBtn->setWidget(ScrollAreaWidgetContents_MiniBtn);
		MiniBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MiniBtn);
		MiniBtn->setObjectName(QStringLiteral("MiniBtn"));
		MiniBtn->setGeometry(QRect(2, 2, 16, 16));
        retranslateUi(SYSLogDlg);

        QMetaObject::connectSlotsByName(SYSLogDlg);
    } // setupUi

    void retranslateUi(QDialog *SYSLogDlg)
    {
        SYSLogDlg->setWindowTitle(QApplication::translate("SYSLogDlg", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        CurrentPageLabel->setText(QApplication::translate("SYSLogDlg", "\347\254\2540\351\241\265", nullptr));
        TotalPageabel->setText(QApplication::translate("SYSLogDlg", "\345\205\2610\351\241\265", nullptr));
        PageToBeginBtn->setText(QApplication::translate("SYSLogDlg", "\351\246\226\351\241\265", nullptr));
        PageDownBtn->setText(QApplication::translate("SYSLogDlg", "\345\211\215\344\270\200\351\241\265", nullptr));
        PageUpBtn->setText(QApplication::translate("SYSLogDlg", "\345\220\216\344\270\200\351\241\265", nullptr));
        PageToEndBtn->setText(QApplication::translate("SYSLogDlg", "\346\234\253\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SYSLogDlg: public Ui_SYSLogDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSLOGDLG_H
