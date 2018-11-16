#include "ImpDataThread.h"
#include<QJsonDocument>
#include"param.h"
#include<QMessageBox>
ImpDataThread::ImpDataThread()
{
}

ImpDataThread::~ImpDataThread()
{
}
void ImpDataThread::run()
{
	emit ErrorMSGSignal(1);
	ImpData();
}

//���봦��
void  ImpDataThread::ImpData()
{
	int pResult = -1;
	int iCount = JsonList.size();
	for (int i = 0; i < iCount; i++)
	{
		QJsonDocument document;
		document.setObject(JsonList[i]);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		QString ServiceID = JsonList[i].find("ServiceTypeID").value().toString();
		if (ServiceID.toInt() == 8 || ServiceID.toInt() == 11 || ServiceID.toInt() == 12 || ServiceID.toInt() == 13 ||
			ServiceID.toInt() == 14 || ServiceID.toInt() == 15 || ServiceID.toInt() == 16 ||
			ServiceID.toInt() == 17 || ServiceID.toInt() == 18)
		{    //ʪ������
			 //��������Ϣ�м��
			if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
				emit ErrorMSGSignal(10304);
		}
		else
		{
			//��������Ϣ�м��
			if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
				emit ErrorMSGSignal(10304);
			//if (g_SimpleProducer_ZDH.send(dataChar, strlen(dataChar)) < 0)
				//emit ErrorMSGSignal(10304);
		}
		ProcessingSignal(i + 1);
	}
	JsonList.clear();
}
