#pragma once

#include <QDialog>
#include "ui_DMTDDlg.h"
#include"param.h"
class DMTDDlg : public QDialog
{
	Q_OBJECT

public:
	DMTDDlg(QWidget *parent = Q_NULLPTR);
	~DMTDDlg();

private slots:
    void on_BrowsingBtn_clicked();

    void on_ImpBtn_clicked();
private:
	Ui::DMTDDlg ui;
	//数据路径
	QString path;
	//存放解析数据的json数组
	QList<QJsonObject> JsonList;
private:
	//读取txt
	void LoadTXT(QString path);
	//导入数据
	LRESULT ImpData();
	int count;
	//处理函数
	static unsigned __stdcall Process(LPVOID pParam);
	//初始化消息中间件
	void InitActiveMQ();
	//消息中间件
	SimpleProducer m_SimpleProducer, m_SimpleProducer_ZDH;
protected:
	void closeEvent(QCloseEvent *event);
	HANDLE threadhandle;
	bool isRun;
public:
	//解析数据
	Char2Json func_Char2Json;
public slots:
//处理

signals:
	void finished();
};
