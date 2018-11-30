#include "EHTPool.h"

EHTPool::EHTPool(QObject *parent)
	: QObject(parent)
{
	ThreadPool.setMaxThreadCount(1024);
}
EHTPool::EHTPool()
{
	ThreadPool.setMaxThreadCount(1024);
}
EHTPool::~EHTPool()
{
	StopAll();
}

void EHTPool::Start(EHT* pEHT)
{
	pEHT->Run(ThreadPool);
	AllEHTList.append(pEHT);
}

void EHTPool::Stop(int Index)
{
	for (int i = AllEHTList.count() - 1; i > -1; i--)
	{
		if (AllEHTList[i]->GetServiceID() == Index)
		{
			AllEHTList[i]->Stop();
			delete AllEHTList[i];
			AllEHTList[i] = nullptr;
			AllEHTList.removeAt(i);
		}
	}
}

void EHTPool::Stop(QString ServiceName)
{
	for (int i = AllEHTList.count() - 1; i > -1; i--)
	{
		if (AllEHTList[i]->GetServiceName() == ServiceName)
		{
			AllEHTList[i]->Stop();
			delete AllEHTList[i];
			AllEHTList[i] = nullptr;
			AllEHTList.removeAt(i);
		}
	}
}

void EHTPool::StopAll()
{
	for (int i = AllEHTList.count() - 1; i > -1; i--)
	{
		AllEHTList[i]->Stop();
		delete AllEHTList[i];
		AllEHTList[i] = nullptr;
		AllEHTList.removeAt(i);

	}
}

void EHTPool::Pause(int Index)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceID() == Index)
		{
			(*iter)->Stop();
			break;
		}
		iter++;
	}
}

bool EHTPool::Pause(QString KeyName)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceName() == KeyName)
		{
			return (*iter)->Stop();
		}
		iter++;
	}
}

void EHTPool::PauseAll()
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		(*iter)->Stop();
		iter++;

	}
}

void EHTPool::Run(int Index)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceID() == Index)
		{
			(*iter)->Run(ThreadPool);
			break;
		}
		iter++;
	}
}

bool EHTPool::Run(QString KeyName)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceName() == KeyName)
		{
			return (*iter)->Run(ThreadPool);
		}
		iter++;
	}
}

void EHTPool::RunAll()
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		(*iter)->Run(ThreadPool);
		iter++;

	}
}

//获取EHT
EHT* EHTPool::GetEHT(QString ServiceName)
{

	for (QList<EHT*>::iterator iter = AllEHTList.begin(); iter != AllEHTList.end(); ++iter)
	{
		if ((*iter)->GetServiceName() == ServiceName)
		{
			return (*iter);
		}
	}
	return NULL;
}

EHT* EHTPool::GetEHT(int ServiceID)
{
	for (QList<EHT*>::iterator iter = AllEHTList.begin(); iter != AllEHTList.end(); ++iter)
	{
		if ((*iter)->GetServiceID() == ServiceID)
		{
			return (*iter);
		}
	}
	return NULL;
}
