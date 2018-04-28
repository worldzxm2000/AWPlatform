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
	//服务器端Socket监听端口
	int m_portServer;
private:
	//服务器端Socket
	SOCKET srvSocket;
	//Web端地址
	SOCKADDR_IN from;
protected:
	void run();
	void ResolveData(LPCSTR buff,int len);
	bool IsClose;
public:
	//终端命令类型
	int m_CommandID;
	//终端命令业务类型
	int m_ServiceTypeID ;
	//终端命令区站号
	int m_StationID ;
	//终端命令设备号
	int m_FacilityID ;
public:
	//向Web发送处理后的数据
	void Send2WebServerJson(QJsonObject RecvValue);
signals:
	//通知UI错误信息
	void NoticfyServerError(int Error);
	//通知UI读取设备参数指令
	void NoticfyServerFacilityID(int,int,int,int,QString,QString);
};
