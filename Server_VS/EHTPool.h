#pragma once

#include <QObject>
#include "EHT.h"
class EHTPool : public QObject
{
	Q_OBJECT

public:
	EHTPool(QObject *parent);
	EHTPool::EHTPool();
	~EHTPool();
	//������������
	void Start(EHT *pEHT);
	//������������
	//index EHT��Ӧ������
	//KeyName EHT�����ֶ�����
	void Stop(int ServiceID);
	void Stop(QString ServiceName);
	//�������м���
	void StopAll();
	//��ͣ��������
	void Pause(int ServiceID);
	void Pause(QString KeyName);
	void PauseAll();
	//������������
	void Run(int ServiceID);
	void Run(QString ServiceName);
	void RunAll();
	//��ȡEHT
	EHT* GetEHT(QString ServiceName);
private:
	QList<EHT *> AllEHTList;
	QThreadPool ThreadPool;
};
