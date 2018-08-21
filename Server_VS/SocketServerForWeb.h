#pragma once

#include <QObject>
#include<QRunnable>
#include<WinSock2.h>
#include<qjsonobject.h>
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
	SOCKET m_SrvSocket;
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
	public slots:
	//��Web���ʹ���������
	void SendToWebServiceSlot(QJsonObject RecvValue);
signals:
	//֪ͨUI������Ϣ
	void GetErrorSignal(int Error);
	//֪ͨUI��ȡ�豸����ָ��
	void NoticfyServerFacilityID(int, QString, QString,int,QString,QString);
};
