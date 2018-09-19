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

//导入处理
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
		if (ServiceID.toInt() == 8 || ServiceID.toInt() == 11 || ServiceID.toInt() == 12)
		{    //湿地数据
			 //发送至消息中间件
			if (g_SimpleProducer_sh.send(dataChar, strlen(dataChar)) < 0)
				emit ErrorMSGSignal(10304);
		}
		else
		{
			//发送至消息中间件
			if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
				emit ErrorMSGSignal(10304);
			if (g_SimpleProducer_ZDH.send(dataChar, strlen(dataChar)) < 0)
				emit ErrorMSGSignal(10304);
		}
		ProcessingSignal(i + 1);
	}
	JsonList.clear();
}
