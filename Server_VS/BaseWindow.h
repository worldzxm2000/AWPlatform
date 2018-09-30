#pragma once

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
class BaseWindow : public QWidget
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent);
	~BaseWindow();
private:
	QGroupBox *groupBox;
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
public:
	void show();
};
