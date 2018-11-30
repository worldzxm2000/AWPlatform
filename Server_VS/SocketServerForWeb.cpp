#include "SocketServerForWeb.h"
#include<qjsondocument.h>
#include<QMessageBox>
#include<qDebug>
#include<QMutex>
#include<Ws2tcpip.h>
#include"LogWrite.h"
#define TIMEOUT 14
QMutex m_timerMutex;

SocketServerForWeb::SocketServerForWeb()
{
	m_TimeOutTimerID = startTimer(1000);
}

SocketServerForWeb::~SocketServerForWeb()
{
	
}

void SocketServerForWeb::Stop()
{
	closesocket(m_SrvSocket);
	killTimer(m_TimeOutTimerID);
}
//开启线程处理
void SocketServerForWeb::run()
{
	
	WSADATA wsaData;//初始化
	//初始化Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKADDR_IN  RecvAddr;//服务器地址
	int len = sizeof(SOCKADDR);
	//创建Socket对象
	m_SrvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//设置服务器地址
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(m_portServer);
	char name[155];
	char *ip;
	PHOSTENT hostinfo;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				//这些就是获得IP的函数
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
	}
	RecvAddr.sin_addr.s_addr =inet_addr(ip);
	::bind(m_SrvSocket, (SOCKADDR*)&RecvAddr, len);
	while (1)
	{
		char buff[LENGTH] = {0};
		//Web端地址
		SOCKADDR_IN from;
		int RecvLen=recvfrom(m_SrvSocket,buff,LENGTH,0,(SOCKADDR*)&from,&len);
		if (RecvLen == SOCKET_ERROR)
		{
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("Web服务监听断开"));
			return;
		}
		ResolveData(buff, RecvLen,from);
	}
	WSACleanup();
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
	QString ServiceID, StationID, DeviceID;
	SOCKADDR_IN from;
	ServiceID = RecvValue.find("ServiceTypeID").value().toString();
	StationID = RecvValue.find("StationID").value().toString();
	DeviceID = RecvValue.find("DeviceID").value().toString();
    from = GetClient(ServiceID,StationID,DeviceID);
	sendto(m_SrvSocket, dataChar, strlen(dataChar),0,(SOCKADDR*)&from, len);

}
//解析数据
void SocketServerForWeb::ResolveData(LPCSTR buff,int len, SOCKADDR_IN from)
{
	UDPClient client;
	QString str = QString(QLatin1String(buff,len));
	str = str.simplified();
	QStringList strlist = str.split(",");
	QString header = strlist.at(0);
	QString tailer = strlist.at(strlist.length() - 1);
	//帧头或者帧尾不正确
	if (!(header== "BG" && tailer== "ED"))
		return;
	
	if (strlist.count()<14)
	{
		emit ErrorMSGSignal(-1);
	}
	//业务编号
	int ServiceTypeID = strlist.at(2).toInt();
	client.ServiceID =ServiceTypeID;
	//区站号
	QString StationID = strlist.at(4);
	client.StationID = StationID;
	//设备号
	QString DeviceID = strlist.at(6);
	client.DeviceID = DeviceID;
	//命令号
	int CommandID = strlist.at(8).toInt();
	//参数1
	QString Param1 = strlist.at(10);
	//参数2
	QString Param2 = strlist.at(12);
	client.from = from;
	client.Count = 0;
	ClientsQ.append(client);
	//处理发送命令
    emit NoticfyServerFacilityID(ServiceTypeID, StationID, DeviceID,CommandID,Param1,Param2);
}

//超时检测
void SocketServerForWeb::timerEvent(QTimerEvent *event)
{
	//每一秒进行计数，当计数器超过15时，Timeout。
	for (int  i = ClientsQ.count()-1; i >-1; i--)
	{
		ClientsQ[i].Count++;
		if (ClientsQ[i].Count >TIMEOUT)
		{
			m_timerMutex.lock();
			ClientsQ.removeAt(i);
			m_timerMutex.unlock();
		}
	}
}

//查找相对应的UDP
SOCKADDR_IN SocketServerForWeb::GetClient(QString ServiceID,QString StationID,QString DeviceID)
{
	SOCKADDR_IN from;
	for (int i = ClientsQ.count() - 1; i >-1; i--)
	{
		if (ClientsQ[i].DeviceID==DeviceID&&ClientsQ[i].StationID==StationID&&ClientsQ[i].ServiceID==ServiceID.toInt())
		{
			m_timerMutex.lock();
			from= ClientsQ[i].from;
			ClientsQ.removeAt(i);
			m_timerMutex.unlock();
			return from;
		}
	}
	return from;
}