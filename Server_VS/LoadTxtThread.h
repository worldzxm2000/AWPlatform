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
	QString path;//TXT��ȡ·��
	bool isRun;//�߳̿���
	Char2Json func_Char2Json; //��������
private:
	void run();
	void LoadTXT(QString path);//��ȡTXT����
	int count;//���ݸ���
signals:
	void CountOfStrSignal(int count);//���͵�ǰtxt�����ݸ���
	void SendJson(QJsonObject json);//��������
};
