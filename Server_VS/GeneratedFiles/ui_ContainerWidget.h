/********************************************************************************
** Form generated from reading UI file 'ContainerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTAINERWIDGET_H
#define UI_CONTAINERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_ContainerWidget
{
public:
	
	QLabel *ImageLabel;
	QLabel *NameLabel;
	QGroupBox *groupBox_6;
	QScrollArea *ScrollArea_MinBtn;
	QWidget *ScrollAreaWidgetContents_MinBtn;
	MyButton *MinBtn;
	QScrollArea *ScrollArea_CloseBtn;
	QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;
    void setupUi(QDialog *ContainerWidget)
    {
        if (ContainerWidget->objectName().isEmpty())
            ContainerWidget->setObjectName(QStringLiteral("ContainerWidget"));
        ContainerWidget->resize(585, 457);
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(10);
		ContainerWidget->setFont(font);
		ContainerWidget->setStyleSheet(QStringLiteral("background:rgb(77, 77, 77);color:white"));
		QIcon icon;
		icon.addFile(QStringLiteral("../Image/png/control.png"), QSize(), QIcon::Normal, QIcon::Off);
		ContainerWidget->setWindowIcon(icon);  //设置窗口图标
		ImageLabel = new QLabel(ContainerWidget);
		ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
		ImageLabel->setGeometry(QRect(5, 2, 31, 31));
		ImageLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/logicon.png")));
		NameLabel = new QLabel(ContainerWidget);
		NameLabel->setObjectName(QStringLiteral("NameLabel"));
		NameLabel->setGeometry(QRect(40, 8, 50, 20));
		NameLabel->setStyleSheet(QString("QLabel{color:white}"));
		NameLabel->setText(QString::fromLocal8Bit("设备控制"));


		groupBox_6 = new QGroupBox(ContainerWidget);
		groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
		groupBox_6->setGeometry(QRect(ContainerWidget->width()-50, 2, 46, 26));
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

        retranslateUi(ContainerWidget);

        QMetaObject::connectSlotsByName(ContainerWidget);
    } // setupUi

    void retranslateUi(QDialog *ContainerWidget)
    {
        ContainerWidget->setWindowTitle(QApplication::translate("ContainerWidget", "ContainerWidget", nullptr));
		
    } // retranslateUi

};

namespace Ui {
    class ContainerWidget: public Ui_ContainerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTAINERWIDGET_H
