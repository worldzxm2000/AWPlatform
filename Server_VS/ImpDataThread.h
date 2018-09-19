#pragma once

#include <QThread>
#include<QJsonObject>
class ImpDataThread : public QThread
{
	Q_OBJECT

public:
	ImpDataThread();
	~ImpDataThread();
	QList<QJsonObject> JsonList;//数据数组
private:
	void run();

	void  ImpData();//上传数据
signals:
	void ProcessingSignal(int Proccessing);//进度条
	void ErrorMSGSignal(int ErrorMSG);//异常处理
};
