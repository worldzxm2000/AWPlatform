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
	//�����ƶ�
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;                //�ж��������Ƿ���
	QPoint m_DragPosition;
public:
	EHTPool *pEHT;
	QString ServiceName;
	QString StationID;
	int ServiceID; 
public slots:
	//��С������
	void slot_minWindow();
	//�߶�
	void SendComm();
};
