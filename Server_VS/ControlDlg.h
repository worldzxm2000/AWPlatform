#pragma once

#include <QWidget>
#include "ui_ControlDlg.h"
#include"EHTPool.h"
class ControlDlg : public QWidget
{
	Q_OBJECT

public:
	ControlDlg(QWidget *parent = Q_NULLPTR);
	~ControlDlg();
	void show();
private:
	Ui::ControlDlg ui;
	//窗体移动
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;                //判断鼠标左键是否按下
	QPoint m_DragPosition;
public:
	EHTPool *pEHT;
	QString ServiceName;
	QString StationID;
	int ServiceID; 
public slots:
	//最小化窗体
	void slot_minWindow();
	//高度
	void SendComm();
};
