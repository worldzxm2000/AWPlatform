#include "BaseWindow.h"

BaseWindow::BaseWindow(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QStringLiteral("groupBox"));
	groupBox->setGeometry(QRect(this->width()-52, 5, 52, 26));
	ScrollArea_CloseBtn = new QScrollArea(groupBox);
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
	ScrollArea_MinBtn = new QScrollArea(groupBox);
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
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::show()
{
	groupBox->setGeometry(QRect(this->width() - 52, 5, 52, 26));
	QWidget::show();
}

