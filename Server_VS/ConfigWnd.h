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
	//获取本地IP
	void GetLocalIP();
public:
	//设置端口号
	int m_Port;
	//设置ip号
	QString m_IP;
	//描述
	QString m_Attribute;
	//窗体打开模式
	bool DialogMode;
	//设置端口号
	void SetServicePort(int Port);
	int exec();
private slots:
    void on_SetBtn_clicked();
};
