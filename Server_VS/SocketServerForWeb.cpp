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
	closesocket(srvSocket);
}

//�����̴߳���
void SocketServerForWeb::run()
{
	WSADATA wsaData;//��ʼ��
	int Port = 1030;//������������ַ
		//��ʼ��Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKADDR_IN  RecvAddr;//��������ַ
	int len = sizeof(SOCKADDR);
	//����Socket����
	srvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//���÷�������ַ
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(m_portServer);
	RecvAddr.sin_addr.s_addr = inet_addr("172.18.2.160");
	int a = bind(srvSocket, (SOCKADDR*)&RecvAddr, len);
	timeval timeout = {5,0 };//3s
	//setsockopt(srvSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	while (1)
	{
		char buff[LENGTH] = {0};
		int RecvLen=recvfrom(srvSocket,buff,LENGTH,0,(SOCKADDR*)&from,&len);
		if (RecvLen == SOCKET_ERROR)
		{
			int error=WSAGetLastError();
			switch (error)
			{
			case WSAECONNRESET:
				break;
			default:
				break;
			}
			if (IsClose)
			{
				break;
			}
			else
			{
				continue;
			}
		}
			
		ResolveData(buff, RecvLen);
	}
}

//����������Web������
void SocketServerForWeb::Send2WebServerJson(QJsonObject RecvValue)
{
	
	QJsonDocument document;
	document.setObject(RecvValue);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	LPCSTR dataChar;
	dataChar = byteArray.data();
	int len = sizeof(SOCKADDR);
	sendto(srvSocket, dataChar, strlen(dataChar),0,(SOCKADDR*)&from, len);
}
//��������
void SocketServerForWeb::ResolveData(LPCSTR buff,int len)
{
	QString str = QString(QLatin1String(buff));
	QStringList strlist = str.split(",");
	QString header = strlist.at(0);
	QString tailer = strlist.at(strlist.length() - 1);
	//֡ͷ����֡β����ȷ
	if (!(header== "BG" && tailer== "ED"))
	{
		NoticfyServerError(-1);
		return;
	}
	bool ok;
	//ҵ����
	int ServiceTypeID = strlist.at(2).toInt(&ok,10);
	//��վ��
	int StationID = strlist.at(4).toInt(&ok, 10);
	//�豸��
	int FacilityID = strlist.at(6).toInt(&ok, 10);

	//�����
	int CommandID = strlist.at(8).toInt(&ok, 10);
	//����1
	QString Param1 = strlist.at(10);
	//����2
	QString Param2 = strlist.at(12);
	NoticfyServerFacilityID(ServiceTypeID, StationID, FacilityID,CommandID,Param1,Param2);
	LPCSTR dataChar="<005,009001,234,46.02.20,N>";
	sendto(srvSocket,dataChar , strlen(dataChar), 0, (SOCKADDR*)&from, len);
	m_CommandID = CommandID;
	m_ServiceTypeID = ServiceTypeID;
	m_StationID = StationID;
	m_FacilityID = FacilityID;
}
