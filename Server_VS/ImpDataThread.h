#pragma once

#include <QThread>
#include<QJsonObject>
class ImpDataThread : public QThread
{
	Q_OBJECT

public:
	ImpDataThread();
	~ImpDataThread();
	QList<QJsonObject> JsonList;//��������
private:
	void run();

	void  ImpData();//�ϴ�����
signals:
	void ProcessingSignal(int Proccessing);//������
};
