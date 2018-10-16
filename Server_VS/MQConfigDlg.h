#pragma once

#include <QWidget>
#include "ui_MQConfig.h"
#include<QMouseEvent>
#include"param.h"
class MQConfigDlg : public QWidget
{
	Q_OBJECT

public:
	MQConfigDlg(QWidget *parent = Q_NULLPTR);
	~MQConfigDlg();

private:
	Ui::MQConfigDlg ui;
	//�����ƶ�
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;                //�ж��������Ƿ���
	QPoint m_DragPosition;
private slots:
	void slot_minWindow();
	void SetURL();
	void SetAdmin();
	void SetPassword();
};
