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
		pResult = g_SimpleProducer.send(dataChar, strlen(dataChar));
		pResult = g_SimpleProducer_ZDH.send(dataChar, strlen(dataChar));
		if (pResult < 0)
		{
			QMessageBox::warning(NULL, "错误", "消息中间件发生错误");
			return ;
		}
		ProcessingSignal(i + 1);
		Sleep(10);
	}
	JsonList.clear();
}
