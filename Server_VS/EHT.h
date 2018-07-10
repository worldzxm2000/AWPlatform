#pragma once

#include <QObject>
#include <QWidget>
#include<QLibrary>
#include<QThreadPool>
#include"IOCP.h"
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT(QWidget *parent);
	~EHT();
public:
	//处理线程
	IOCP *pIOCP;
	//加载动态链接库
	bool LoadLib(QString Lib_Path);
	//卸载动态链接库
	bool UnloadLib();
	//获取版本号
	QString GetVesionNo();
	//获取业务ID
	int GetServiceID();
	//获取业务名称
	QString GetServiceName();
	//获取IP号
	QString GetIP();
	//获取端口号
	int GetPort();
	//获取Socket号
	int GetSocket();
	//获取业务描述
	QString GetAttribute();
	//开始运行监听
	void Run(QThreadPool &ThreadPool);
protected:
	//Lib加载类
	QLibrary m_Lib;
	//版本号
	QString m_Vesion;
	//IP号
	QString m_IP;
	//Socket
	int m_Socket;
	//端口号
	int m_Port;
	//业务类型
	int m_ServiceID;
	//业务名称
	QString m_ServiceName;
	//描述
	QString m_Attribute;
	//检查端口是否合法
	bool IsLegallyPort(int Port);
};
