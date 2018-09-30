#pragma once
#include"EHT.h"
#include <QObject>
#include<QJsonObject>
class FTPEHT :public  EHT
{
	Q_OBJECT
public:
	FTPEHT(QWidget *parent);
	~FTPEHT();
public:
	//加载动态链接库
	LRESULT LoadLib(QString Lib_Path);
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
	//获取设备Socket号
	unsigned int GetSocket(QString StationID);
	//获取业务描述
	QString GetAttribute();
	//获得数据解析
	Char2Json GetDataFunc();
	//开始运行监听
	void Run(QThreadPool &ThreadPool);
	//结束运行监听
	void Stop();
	//获取运行状态
	bool IsRun();
	//获取连接客户端数组
	QList<CLIENTINFO> Clients;
	//发送COMMAND指令
	void SendCommand(OPCommand cmm, QString StationID, QString Params1, QString Params2, bool WebCommand);
	//当前COMMAND指令
	OPCommand CurrentCommand;
	//锁住操作变量，判断是否是Web发送的请求
	bool WebCommand;
	//获取在线设备个数
	int GetOnlineCount();
private:
	//图片处理
	void FTPEHT::MoveImageToDesAddr();
	//文本处理
	void FTPEHT::MoveTXTToDesAddr();
	//XML处理
	void FTPEHT::MoveXMLToDesAddr(QJsonObject &Json);

	//初始化IOCP
	void InitIOCP();
	//消息中间件错误重连
	void ReConnectActiveMq();
	//重连定时器
	QTimer *ReconnectTimer;
	//植被重新处理定时器
	QTimer *ReHandleZB;
	//是否存在JPG和XML文件
	bool IsExistImageXML;
	//重连状态
	bool b_IsReconnect;
	//连接状态
	bool b_IsRunMQ;
	//运行状态
	bool m_IsRun;
	//处理线程
	IOCP *pIOCP;
	//Lib加载类
	QLibrary m_Lib;
	//版本号
	QString m_Vesion;
	//服务监听IP号
	QString m_IP;
	//设备连接Socket
	unsigned int m_Socket;
	//服务监听端口号
	int m_Port;
	//业务类型
	int m_ServiceID;
	//业务名称
	QString m_ServiceName;
	//描述
	QString m_Attribute;
	//数据解析
	Char2Json m_DataFunc;
	//SIM卡号对应区站号
	QMap<QString, QString> SIM2Staion;
	//检查端口是否合法
	bool IsLegallyPort(int Port);
	//读取SIM卡号配置文件，转成区站号v
	void Convert2StationID();
	//自动对时时钟
	QTimer *SetTimeTimer;
	//离线判断
	QTimer *OffLineTimer;
private slots:
	//自动检测离线
	void Disconnect();
	//对时处理
	void SetTime();
	//重连MQ处理
	void Reconnect();
	//离线通知
	void OffLineSlot(unsigned int CltSocket);
	//新的数据(观测数据或者心跳数据)
	void NewDataSlot(QString StationID, QString IP, int Port, FileType File, unsigned int CltSocket);
	//错误信息
	void GetErrorSlot(int ErrorMSG);
	//终端操作指令
	void OperationResultSlot(QString Value, int SrvPort, QString StationID);
	void OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID);
	void OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID);
	//设备实时数据
	void RealTimeDataSlot(QString data);

signals:
	//UI登录时间
	void LoginTimeSignal(int SrvPort, QString Station);
	//UI设备在线信息
	void OnLineSignal(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime);
	//UI设备离线信息
	void OffLineSignal(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime);
	//UI显示终端返回值
	void SendWarningInfoToUI(QString Result);
	//发送至Web
	void  SendToWebServiceSignal(QJsonObject Json);
};
