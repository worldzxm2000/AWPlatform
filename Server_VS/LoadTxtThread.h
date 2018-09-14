#pragma once

#include <QThread>
#include"param.h"
#include<QJsonObject>
class LoadTxtThread : public QThread
{
	Q_OBJECT

public:
	LoadTxtThread();
	~LoadTxtThread();
	QString path;//TXT读取路径
	bool isRun;//线程控制
	Char2Json func_Char2Json; //解析数据
private:
	void run();
	void LoadTXT(QString path);//读取TXT内容
	int count;//数据个数
signals:
	void CountOfStrSignal(int count);//发送当前txt中数据个数
	void SendJson(QJsonObject json);//发送数据
};
