#pragma once


#include <QObject>
#include<QList>
#include<QThread>
#include<QTimer>
#include<qjsonobject.h>
#include"param.h"
#include<QUdpSocket>
#define LENGTH 4*1024
class SocketServerForWeb :public QThread
{
	Q_OBJECT

public:
	SocketServerForWeb();
	~SocketServerForWeb();
	//��������Socket�����˿�
	int m_portServer;
private:
	//��������Socket
	SOCKET m_SrvSocket;
	//UDP���ӳ�
	QList<UDPClient> ClientsQ;
	//��ʱ���
	virtual void timerEvent(QTimerEvent *event);
	//�����߳�
	int m_TimeOutTimerID;
	//��ȡudp����Ϣ
	SOCKADDR_IN GetClient(QString ServiceID, QString StationID, QString DeviceID);
protected:
	void run();
	void ResolveData(LPCSTR buff,int len, SOCKADDR_IN from);
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
	//�ر����߳�
	void Stop();
signals:
	//֪ͨUI������Ϣ
	void ErrorMSGSignal(int Error);
	//֪ͨUI��ȡ�豸����ָ��
	void NoticfyServerFacilityID(int, QString, QString,int,QString,QString);
};
