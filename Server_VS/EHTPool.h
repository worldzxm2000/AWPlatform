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
	//创建监听服务
	void Start(EHT *pEHT);
	//结束监听服务
	//index EHT对应索引号
	//KeyName EHT包含字段名称
	void Stop(int ServiceID);
	void Stop(QString ServiceName);
	//结束所有监听
	void StopAll();
	//暂停监听服务
	void Pause(int ServiceID);
	void Pause(QString KeyName);
	void PauseAll();
	//开启监听服务
	void Run(int ServiceID);
	void Run(QString ServiceName);
	void RunAll();
	//获取EHT
	EHT* GetEHT(QString ServiceName);
private:
	QList<EHT *> AllEHTList;
	QThreadPool ThreadPool;
};
