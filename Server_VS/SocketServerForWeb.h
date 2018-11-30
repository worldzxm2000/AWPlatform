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
	//服务器端Socket监听端口
	int m_portServer;
private:
	//服务器端Socket
	SOCKET m_SrvSocket;
	//UDP连接池
	QList<UDPClient> ClientsQ;
	//超时检测
	virtual void timerEvent(QTimerEvent *event);
	//计数线程
	int m_TimeOutTimerID;
	//获取udp端信息
	SOCKADDR_IN GetClient(QString ServiceID, QString StationID, QString DeviceID);
protected:
	void run();
	void ResolveData(LPCSTR buff,int len, SOCKADDR_IN from);
public:
	//终端命令类型
	int m_CommandID;
	//终端命令业务类型
	int m_ServiceTypeID ;
	//终端命令区站号
	int m_StationID ;
	//终端命令设备号
	int m_FacilityID ;
	public slots:
	//向Web发送处理后的数据
	void SendToWebServiceSlot(QJsonObject RecvValue);
	//关闭子线程
	void Stop();
signals:
	//通知UI错误信息
	void ErrorMSGSignal(int Error);
	//通知UI读取设备参数指令
	void NoticfyServerFacilityID(int, QString, QString,int,QString,QString);
};
