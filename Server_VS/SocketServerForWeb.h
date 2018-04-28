#pragma once

#include <QObject>
#include<QRunnable>
#include<WinSock2.h>
#define LENGTH 4*1024
class SocketServerForWeb : public QObject,public QRunnable
{
	Q_OBJECT

public:
	SocketServerForWeb();
	SocketServerForWeb(QObject *parent);
	~SocketServerForWeb();
	//��������Socket�����˿�
	int m_portServer;
private:
	//��������Socket
	SOCKET srvSocket;
	//Web�˵�ַ
	SOCKADDR_IN from;
protected:
	void run();
	void ResolveData(LPCSTR buff,int len);
	bool IsClose;
public:
	//�ն���������
	int m_CommandID;
	//�ն�����ҵ������
	int m_ServiceTypeID ;
	//�ն�������վ��
	int m_StationID ;
	//�ն������豸��
	int m_FacilityID ;
public:
	//��Web���ʹ���������
	void Send2WebServerJson(QJsonObject RecvValue);
signals:
	//֪ͨUI������Ϣ
	void NoticfyServerError(int Error);
	//֪ͨUI��ȡ�豸����ָ��
	void NoticfyServerFacilityID(int,int,int,int,QString,QString);
};
