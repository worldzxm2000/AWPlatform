#pragma once

#include <QDialog>
#include "ui_ConfigWnd.h"
#include <QCloseEvent> 
class ConfigWnd : public QDialog
{
	Q_OBJECT

public:
	ConfigWnd(QWidget *parent = Q_NULLPTR);
	~ConfigWnd();
private:
	Ui::ConfigWnd ui;
	void GetLocalIP();
public:
	//设置端口号
	int m_Port;
	//设置ip号
	QString m_IP;

private slots:
    void on_SetBtn_clicked();
};
