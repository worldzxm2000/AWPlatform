#include "SocketServerForWeb.h"
#include<qjsondocument.h>
#include<qjsonobject.h>

SocketServerForWeb::SocketServerForWeb()
{
	IsClose = false;
}
SocketServerForWeb::SocketServerForWeb(QObject *parent)
	: QObject(parent)
{
	
}

SocketServerForWeb::~SocketServerForWeb()
{
	IsClose = true;
	closesocket(m_SrvSocket);
}

//开启线程处理
void SocketServerForWeb::run()
{
	WSADATA wsaData;//初始化
	int Port = 1030;//服务器监听地址
		//初始化Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKADDR_IN  RecvAddr;//服务器地址
	int len = sizeof(SOCKADDR);
	//创建Socket对象
	m_SrvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//设置服务器地址
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(m_portServer);
	RecvAddr.sin_addr.s_addr = INADDR_ANY;
		//inet_addr("172.18.2.160");
	int a = bind(m_SrvSocket, (SOCKADDR*)&RecvAddr, len);
	while (1)
	{
		char buff[LENGTH] = {0};
		int RecvLen=recvfrom(m_SrvSocket,buff,LENGTH,0,(SOCKADDR*)&from,&len);
		if (RecvLen == SOCKET_ERROR)
		{
			int error=WSAGetLastError();
			
			if (IsClose)
			{
				break;
			}
			else
			{
				//发送错误信息
				GetErrorSignal(error);
				continue;
			}
		}
			
		ResolveData(buff, RecvLen);
	}
}

//发送数据至Web服务器
void SocketServerForWeb::SendToWebServiceSlot(QJsonObject RecvValue)
{
	QJsonDocument document;
	document.setObject(RecvValue);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	LPCSTR dataChar;
	dataChar = byteArray.data();
	int len = sizeof(SOCKADDR);
	sendto(m_SrvSocket, dataChar, strlen(dataChar),0,(SOCKADDR*)&from, len);
}
//解析数据
void SocketServerForWeb::ResolveData(LPCSTR buff,int len)
{
	QString str = QString(QLatin1String(buff,len));
	str = str.simplified();
	QStringList strlist = str.split(",");
	QString header = strlist.at(0);
	QString tailer = strlist.at(strlist.length() - 1);
	//帧头或者帧尾不正确
	if (!(header== "BG" && tailer== "ED"))
	{
		GetErrorSignal(-4);
		return;
	}
	bool ok;
	//业务编号
	int ServiceTypeID = strlist.at(2).toInt(&ok,10);
	//区站号
	QString StationID = strlist.at(4);
	//设备号
	QString FacilityID = strlist.at(6);
	//命令号
	int CommandID = strlist.at(8).toInt(&ok, 10);
	//参数1
	QString Param1 = strlist.at(10);
	//参数2
	QString Param2 = strlist.at(12);
	//处理发送命令
	 emit NoticfyServerFacilityID(ServiceTypeID, StationID, FacilityID,CommandID,Param1,Param2);
}
