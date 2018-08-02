#ifndef SERVER_VS_H
#define SERVER_VS_H
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif 
#include <QtWidgets/QMainWindow>
#include "ui_server_vs.h"
#include<QMessageBox>
#include<QThreadPool>
#include"LogWrite.h"
#include<qjsonobject.h>
#include"EHTPool.h"
#include<qlibrary.h>
#include"SocketServerForWeb.h"
#include "qtimer.h"
#include"qnetworkreply.h"
//业务类型连接信息
typedef struct
{
	//描述
	QString Attribute;
	//业务号
	int ServiceID;
	//Lib路径
	QString Path;
	//业务线程
	IOCP *pICOP;
	//监听业务服务器Socket号
	int ServerSocketID;
	//业务编号端口号
	int ServerPortID;
	//业务名称
	QString ServerName;
	//是否在运行
	bool IsRun;
	//IP
	QString IP;
	//业务下连接socket的IP号和端口号
	vector<CLIENTINFO> clients;
} Facility, *LPFacility;

class Server_VS : public QMainWindow
{
	Q_OBJECT

public:
	Server_VS(QWidget *parent = 0);
	~Server_VS();
private:
	//初始化服务程序
	void InitServer();
	//添加解析DLL
	LRESULT AddDll();
	//开启新的IOCP
	void AddIOCP(Char2Json func, int port, QString IP);
	//通过设备号和端口查询到设备索引号
	int FindRowIndex(QString SrvName, QString StationID);
	//通过服务器端口号查找业务编号
	QString FindserviceTypeIDByPort(int servicePort);
	//通过服务器类型查找业务编号
	//QString FindserviceTypeIDByServiceID(int serviceID);
	//添加台站号
	bool AddClient(QString IP, int Port, int SrvPort, SOCKET SocketID, QString StationID);
	//业务列表右键菜单
	void CreateServerListActions();
	//区站号列表右键菜单
	void CreateClientListActions();
	//初始化消息中间件
	LRESULT InitializeMQ();
	//初始化终端命令Socket
	//LRESULT InitializeCommandSocket();
	//通过业务和区站号找到对应的Socket号
	int FindSocketID(int ServiceTypeID, int StationID, int FacilityID);
	//判断port号的合法性
	bool IsLegallyPort(int port);

	//添加SIM卡号
	void Convert2StationID();
private:
	Ui::Server_VSClass ui;
	//业务类型数组
	EHTPool EHTPool;
	//UPD线程
	SocketServerForWeb *socket4web;
	//IOCP线程池
	//QThreadPool ThreadPool;
	//操作类型
	QString strOperateType;
	//业务列表右键菜单
	QMenu pop_Menu_Service;
	//运行
	QAction action_run;
	//停止
	QAction action_stop;
	//补抄数据
	QAction action_dmtd;
	//属性
	QAction action_Attributes;
	//客户列表右键菜单
	QMenu pop_Menu_Client;
	//时间
	QAction action_Time;
	//高度
	QAction action_ALT;
	//经度
	QAction action_LONG;
	//纬度
	QAction action_LAT;
	//发送终端命令
	QAction action_Comm;
	//获取即时要素数据
	QAction action_GetData;
	//获取参数
	QAction action_GetConfig;
	//业务ListCtrl选中行
	int iSelectedRowOfServiceListCtrl;
	//台站号ListCtrl选中行
	int iSelectedRowOfClientListCtrl;
	//业务类型数组
	vector<Facility> ClientInfo;
	//SIM卡号对应区站号
	QMap<QString, QString> SIM2Staion;
	//心跳监听时间
	QTimer *timer;
	//自动对时
	QTimer *day_timer;
	//自动补抄
	QTimer *hour_timer;

	private slots:
	//设备离线ListCtrl控件信息
	void OffLineListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime);
	//刷新设备ListCtrl控件信息
	void RefreshListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime);
	//终端读取设备命令
	void RequestForReadCOMM(int ServiceTypeID, int StationID, int FacilityID, int Command, QString Param1, QString Param2);
	//错误提示
	void GetErrorMSG(int error);
	//更新UI界面
	void UpdateUI(QString stationID, QString observeTime, int count, bool connected, QString ip, int port, int socket, int SrvPort);
	//新客户端连接
	//void AddNewClient(QString clientIp, int clientPort, int serverPort, int socketNo);
	//终端操作返回信息
	void GetCommandStatus(int result);
	//终端操作返回读取值
	void GetCommandRecvValue(QJsonObject RecvJson);
	//添加Lib按钮事件
	void on_RunBtn_clicked();
	//移除业务Lib
	void on_DeleteBtn_clicked();
	//业务列表右键事件
	void on_ServerList_customContextMenuRequested(const QPoint &pos);
	//action_run事件
	void Lib_Run(int ServerIndex);
	//action_stop事件
	void Lib_Stop(int ServerIndex);
	//action_attri事件
	void Lib_Attri();
	//区站号列表右键事件
	void on_ClientList_customContextMenuRequested(const QPoint &pos);
	//获取即时采集数据
	void GetFeature();
	//获取参数设置
	void GetConfig();
	//发送终端命令
	void SendCOMM();
	//心跳处理
	void HeartBeat(QString IP, int Port, int SrvPort, int CltSocket, QString StationID, QString  ServiceTypeID);
	//获取终端命令名称
	void GetCommName(QString CommName);
	//自动对时
	void SetTimeCorrection();
	//自动补抄数据
	void CheckDataCorrection();
	//补抄数据功能
	void Func_DMTD();
	//业务列表点击
	void on_ServerList_itemClicked(QTableWidgetItem *item);
	//离线处理
	void  OffLine(int SrvPort, int CltSocket);
	//打开系统日志
	void OpenSYSLog();
	//打开数据日志
	void OpenDataLog();
};

#endif // SERVER_VS_H
