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
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceID() == Index)
		{
			(*iter)->Stop();
			delete (*iter);
			(*iter) = NULL;
			AllEHTList.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
}

void EHTPool::Stop(QString ServiceName)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceName() == ServiceName)
		{
			(*iter)->Stop();
			delete (*iter);
			(*iter) = NULL;
			AllEHTList.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
}

void EHTPool::StopAll()
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		(*iter)->Stop();
		delete (*iter);
		(*iter) = NULL;
		AllEHTList.erase(iter++);
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

void EHTPool::Pause(QString KeyName)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceName() == KeyName)
		{
			(*iter)->Stop();
			break;
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

void EHTPool::Run(QString KeyName)
{
	QList<EHT*>::iterator iter = AllEHTList.begin();
	while (iter != AllEHTList.end())
	{
		if ((*iter)->GetServiceName() == KeyName)
		{
			(*iter)->Run(ThreadPool);
			break;
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

//ªÒ»°EHT
EHT* EHTPool::GetEHT(QString ServiceName)
{
	
	for (QList<EHT*>::iterator iter = AllEHTList.begin(); iter != AllEHTList.end();++iter)
	{
		if ((*iter)->GetServiceName()==ServiceName)
		{
			return (*iter);
		}
	}
	return NULL;
}
