#pragma once

#include <QDialog>
#include "ui_ContainerWidget.h"
#include<QMouseEvent>
class ContainerWidget : public QDialog
{
	Q_OBJECT

public:
	ContainerWidget(QWidget *parent = Q_NULLPTR);
	~ContainerWidget();
	QWidget *MainWidget;
private:
	Ui::ContainerWidget ui;
	//窗体移动
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;                //判断鼠标左键是否按下
	QPoint m_DragPosition;
public:
	void show();
private slots:
	void slot_minWindow();
};
