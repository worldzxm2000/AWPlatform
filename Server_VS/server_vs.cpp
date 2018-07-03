#include "server_vs.h"
#include<QJsonDocument>
#include<qfiledialog.h>
#include"ConfigWnd.h"
#include<QtNetwork>
#include<QSettings>
#include <iphlpapi.h>
#include"CommandDlg.h"
#include"qdebug.h"
#include"qtcpsocket.h"
#include"DMTDDlg.h"
#include"SYSLogDlg.h"
#include"DataLogDlg.h"
using namespace std;
//消息中间件类
SimpleProducer g_SimpleProducer;
//构造函数
Server_VS::Server_VS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1280, 768);
	strOperateType = "未知操作";

	//设置线程最大数目
	pool.setMaxThreadCount(10);
	//menu功能
	connect(ui.action_SYSLog, SIGNAL(triggered()), this, SLOT(OpenSYSLog()));
	connect(ui.action_DataLog, SIGNAL(triggered()), this, SLOT(OpenDataLog()));
	//读取配置文件
	Convert2StationID();
	//业务类型列表
	connect(ui.ServerList, SIGNAL(NoticfyServerRun(int)), this, SLOT(Lib_Run(int)));
	connect(ui.ServerList, SIGNAL(NoticfyServerStop(int)), this, SLOT(Lib_Stop(int)));
	ui.ServerList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateServerListActions();

	//设备连接列表
	ui.clientList->setColumnCount(9);
	ui.clientList->setHorizontalHeaderLabels(QStringList() << "业务类型" << "区站号" << "登录时间" << "数据数量" << "设备状态" << "连接" << "IP" << "端口号"<<"socket号");
	QHeaderView *header = ui.clientList->verticalHeader();
	header->setHidden(true);// 隐藏行号 
	ui.clientList->setColumnHidden(8, true);//隐藏第九列 Socket号
	ui.clientList->setColumnHidden(4, true);//隐藏第五列 设备状态
	ui.clientList->setColumnHidden(3,true);
	ui.clientList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.clientList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.clientList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.clientList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.clientList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	ui.clientList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.clientList->setColumnWidth(2, 200);
	ui.clientList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateClientListActions();


	LogWrite::SYSLogMsgOutPut("主程序已启动...");
	//心跳监听时间 6min
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(Func_HeartBeat()));
	timer->start(1000 * 10);
	//自动校正时间 24hour
	day_timer = new QTimer(this);
	connect(day_timer, SIGNAL(timeout()), this, SLOT(SetTimeCorrection()));
	day_timer->start(1000 * 60*60*24 );
	//自动补抄数据 1hour
	hour_timer = new QTimer(this);
	connect(hour_timer, SIGNAL(timeout), this, SLOT(CheckDataCorrection()));
	//hour_timer->start(1000 * 60 * 60);
	iSelectIndexOfService = -1;
	LRESULT pResult = -1;
	//消息中间件的初始化
	pResult = InitializeMQ();

	//web服务器Socket的初始化
//	pResult = InitializeCommandSocket();
	switch (pResult)
	{
	case -1:
		QMessageBox::warning(NULL, "警告", "消息中间件服务初始化失败！");
		return;
	case -2:
		QMessageBox::warning(NULL, "警告", "Web服务器初始化失败!");
		return;
	default:
		LogWrite::SYSLogMsgOutPut("消息中间件已启动...");
		break;
	}

}

//析构函数
Server_VS::~Server_VS()
{
	timer->stop();
	//delete socket4web;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].pICOP != NULL)
		{
			if (ClientInfo[i].IsRun)
			{
				ClientInfo[i].pICOP->Stop();
				ClientInfo[i].pICOP = NULL;
			}
		}
	}
}

//心跳监听
void Server_VS::Func_HeartBeat()
{
	QDateTime currentTime= QDateTime::currentDateTime();
	QString current_date = currentTime.toString("yyyy.MM.dd hh:mm:ss");
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		for (int j = 0; j <ClientInfo[i].clients.size(); j++)
		{
			int time_t = currentTime.toTime_t() - ClientInfo[i].clients[j].LatestTimeOfHeartBeat.toTime_t();
			//大于5分钟
			if (time_t >300 && ClientInfo[i].clients[j].Online == true)
			{
				int RowIndex = -1;
				RowIndex = FindRowIndex(ClientInfo[i].ServerPortID,ClientInfo[i].clients[j].StationID);
				if (RowIndex < 0)
					return;
				//设置UI设备列表状态
				ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem("离线"));
				ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(current_date));
				ClientInfo[i].clients[j].Online = false;
				closesocket(ClientInfo[i].clients[j].SocketID);
				LogWrite::SYSLogMsgOutPut("未检测到心跳包,区站号 "+ClientInfo[i].clients[j].StationID+"已离线");
			}
		}
	}
}

//初始化消息中间件
LRESULT Server_VS::InitializeMQ()
{
	try
	{
		std::string brokerURI;
		std::string destURI;
		std::string UserName;
		std::string Password;
		bool useTopics;
		bool clientAck;

		activemq::library::ActiveMQCPP::initializeLibrary();
		UserName = "admin";
		Password = "admin";
		brokerURI = "tcp://117.158.216.250:61616";

		unsigned int numMessages = 2000;
		destURI = "DataFromFacility";
		clientAck = false;
		useTopics = false;
		g_SimpleProducer.start(UserName, Password, brokerURI, numMessages, destURI, useTopics, clientAck);
		return 1;
	}
	catch (const std::exception&)
	{
		return -1;
	}
}

//初始化Web监听线程
//LRESULT Server_VS::InitializeCommandSocket()
//{
//	try
//	{
//		//开启WebSocket线程
//		socket4web = new SocketServerForWeb();
//		connect(socket4web, SIGNAL(NoticfyServerError(int)), this, SLOT(GetErrorMSG(int)), Qt::AutoConnection);
//		//处理web端发送过来命令类型
//		connect(socket4web, SIGNAL(NoticfyServerFacilityID(int, int, int, int, QString, QString)), this, SLOT(RequestForReadCOMM(int, int, int, int, QString, QString)), Qt::AutoConnection);
//		socket4web->m_portServer = 1030;
//		socket4web->setAutoDelete(false);
//		pool.start(socket4web);
//		return 1;
//	}
//	catch (const std::exception&)
//	{
//		return -2;
//	}
//}

//读取设备参数指令
void Server_VS::RequestForReadCOMM(int ServiceTypeID, int StationID, int FacilityID, int Command, QString Param1, QString Param2)
{
	//通过业务号和区站号找到对应的Socket号
	int SocketID = FindSocketID(ServiceTypeID, StationID, FacilityID);
	if (SocketID == -1)
		GetCommandStatus(-1);
	//发送终端命令
	switch (Command)
	{
		//读取采集器的基本信息
	case	BASEINFO:
	{
		QString Comm = "BASEINFO\r\n";
		if (Param1 != "NULL")
		{
			Comm = "BASEINFO " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取自动观测站的区站号
	case ID:
	{

		QString Comm = "ID\r\n";
		if (Param1 != "NULL")
		{
			Comm = "ID " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取观测场拔海高度
	case ALT:
	{
		QString Comm = "ALT\r\n";
		if (Param1 != "NULL")
		{
			Comm = "ALT " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//CF卡模块配置
	case CFSET:
	{
		QString Comm = "CFSET\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取数据采集时间范围
	case CAPTIME:
	{
		QString Comm = "CAPTIME\r\n";
		if (Param1 != "NULL")
		{
			Comm = "CAPTIME " + Param1 + " " + Param2 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取自动观测站的经度
	case LONGITUDE:
	{
		QString Comm = "LONG\r\n";
		if (Param1 != "NULL")
		{
			Comm = "LONG " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取数据采集时间间隔
	case CAPINTERVAL:
	{
		QString Comm = "CAPINTERVAL\r\n";
		if (Param1 != "NULL")
		{
			Comm = "CAPINTERVAL " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//重新启动采集器
	case RESET:
	{
		QString Comm = "RESET\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//远程升级开关
	case UPDATE:
	{
		QString Comm = "UPDATE\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//手动采集当前时刻的要素数据
	case SNAPSHOT:
	{
		QString Comm = "SNAPSHOT\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取采集器日期时间操作
	case DATETIME:
	{
		QString Comm = "DATETIME\r\n";
		if (Param1 != "NULL")
		{
			Comm = "DATETIME " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	//设置或读取自动观测站的纬度
	case LAT:
	{
		QString Comm = "LAT\r\n";
		if (Param1 != "NULL")
		{
			Comm = "LAT " + Param1 + "\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	default:
		break;
	}
}

//添加Lib服务
void Server_VS::on_RunBtn_clicked()
{
	//初始化服务
	InitServer();
}

//移除Lib
void Server_VS::on_DeleteBtn_clicked()
{
	QTableWidgetItem* selecteditem = ui.ServerList->currentItem(); //获取选择单元
	int SelectedRow = ui.ServerList->currentRow();//获取选中行
	if (selecteditem == 0)
		return;
	//从业务数组中移除
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == selecteditem->text())
		{
			if (ClientInfo[i].pICOP != NULL)
			{
				if (ClientInfo[i].IsRun==true)
				{
					QMessageBox::warning(NULL, "警告", "请先停止运行，再移除业务！");
					return;
				}
				ClientInfo[i].pICOP->Stop();
				ClientInfo[i].IsRun = false;
				ClientInfo[i].pICOP = NULL;
			}
			ClientInfo.erase(ClientInfo.begin() + i);
		}
	}
	//移除设备列表
	for (int i = 0; i < ui.clientList->rowCount(); i++)
	{
		if (ui.clientList->item(i,0)->text()== selecteditem->text())
		{
			ui.clientList->removeRow(i);
		}
	}
	//从UI列表中移除
	ui.ServerList->removeRow(SelectedRow);
}

//加载动态链接库
void Server_VS::InitServer()
{
	//加载动态解析DLL
	LRESULT pResult = AddDll();
	switch (pResult)
	{
	case -3:
		QMessageBox::information(NULL, tr("错误"), tr("加载的动态链接库不正确！"));
		break;
	case -1:
		QMessageBox::information(NULL, tr("错误"), tr("已经添加该业务类型！"));
		break;
	case -2:
		QMessageBox::information(NULL, tr("错误"), tr("IP设置不可用！"));
		break;
	default:
		break;
	}
}

//添加解析DLL
LRESULT Server_VS::AddDll()
{
	int errCode = 0;
	QString strName;
	//打开选择文件的对话框
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(tr("选择加载动态链接库"));
	fileDialog->setDirectory(".");
	fileDialog->setNameFilter(tr("DLL Files(*.dll)"));
	if (fileDialog->exec() != QDialog::Accepted)
		return 0;
	strName = fileDialog->selectedFiles()[0];
	//读取dll
	QLibrary lib(strName);
	//读取成功
	if (lib.load())
	{
		GetServiceTypeID func_GetServiceTypeID = (GetServiceTypeID)lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName func_GetServiceTypeName = (GetServiceTypeName)lib.resolve("GetServiceTypeName");//获取业务名称
		//是否成功连接上 add() 函数  
		if (!(func_GetServiceTypeID&&func_GetServiceTypeName))
			return -3;

		//获取业务类型
		int ServiceID = func_GetServiceTypeID();
		for (int i = 0; i < ClientInfo.size(); i++)
		{
			if (ClientInfo[i].ServiceID == ServiceID)
				return -1;
		}
		//开启IP和端口设置窗体
		ConfigWnd CfgWnd(this);
		CfgWnd.DialogMode = true;
		int r = CfgWnd.exec();
	    if (r != QDialog::Accepted)
		{
			return 1;
		}
		if (!IsLegallyPort(CfgWnd.m_Port))
			return -2;
		//添加到业务类型内存中
		Facility fcty;
		fcty.pICOP = NULL;
		fcty.ServiceID = ServiceID;
		fcty.ServerPortID = CfgWnd.m_Port;
		fcty.ServerName = func_GetServiceTypeName();
		fcty.Path = strName;
		fcty.IP = CfgWnd.m_IP;
		fcty.Attribute = CfgWnd.m_Attribute;
		ui.ServerList->AddRow(fcty.ServerName, strName);
		//设备连接信息
		ClientInfo.push_back(fcty);
		lib.unload();
	}
	return 1;
}

//判断port号的合法性
bool Server_VS::IsLegallyPort(int port)
{
	//for (int i = 0; i < ClientInfo.size(); i++)
	//{
	//	if (ClientInfo[i].ServerPortID == port)
	//		return false;
	//}
	return true;
}

//终端命令返回操作状态
void Server_VS::GetCommandStatus(int result)
{
	//操作状态
	QString strOperateStatus("未知值");
	switch (result)
	{
		//无效操作
	case -1:
		strOperateStatus = "无效操作!";
		break;
		//操作失败
	case 0:
		strOperateStatus = "操作失败!";
		break;
		//操作成功
	case 1:
		strOperateStatus = "操作成功!";
		break;
	default:
		strOperateStatus =QString::number(result);
		break;
	}
	LogWrite::DataLogMsgOutPut(QString("终端命令:")+strOperateType +QString(",解析终端值:") + strOperateStatus);
	ui.StatusLabel->setText(strOperateType +":"+ strOperateStatus);
    //LogWrite::LogWrite();
}

//终端命令返回读取值
void Server_VS::GetCommandRecvValue(QJsonObject RecvJson)
{
	QJsonObject::Iterator it;
	QString keyString = "未知值";
	QString valueString = "未知值";
	for (it = RecvJson.begin(); it != RecvJson.end(); it++)
	{
		keyString = it.key();
		if (keyString == "RecvValue1" || keyString == "RecvValue2" || keyString == "RecvValue3" || keyString == "RecvValue4")
		{
			QString value = it.value().toString();
			if (value == "N")
				continue;
			valueString += " ";
			valueString += value;
		}
	}
	ui.StatusLabel->setText(strOperateType+":"+valueString);
	QJsonDocument document;
	document.setObject(RecvJson);
	QString strRecv(document.toJson(QJsonDocument::Compact));
	LogWrite::DataLogMsgOutPut(QString("解析终端值:")+strRecv);
	//socket4web->Send2WebServerJson(RecvJson);
}

//获得错误信息
void Server_VS::GetErrorMSG(int error)
{
	QString strMSG;
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	switch (error)
	{
	case 1:
		strMSG = "正常";
		break;
	case -1:
		strMSG = "通信初始化失败！";
		break;
	case -2:
		strMSG = "";
		break;
	case -3:
	{
		strMSG = "消息中间件通信异常！";
	//	g_SimpleProducer.start("admin", "admin", "tcp://117.158.216.250:61616", 2000, "DataFromFacility", false, false);
	}
		break;
	case -4:
		strMSG = "服务器间通信异常！";
		break;
	case -5:
		strMSG = "设备已登出！";
		break;
	case -10311:
		strMSG = "端口号监听失败！";
		QMessageBox::warning(NULL, "警告", strMSG);
		break;
	default:
		strMSG = QString::number(error);
		break;
	}
	ui.StatusLabel->setText(strMSG);
	LogWrite::SYSLogMsgOutPut(strMSG);
}

//设备发送数据  "业务类型"<< "设备号" << "时间" << "上传数量"<<"设备状态"<<"连接"<<"IP"<<"Socket"
void Server_VS::UpdateUI(QString StationID, QString ObserveTime, int Count, bool Connected, QString IP, int Port,int Socket,int SrvPort)
{
	//判断是否第一次连接
	bool bIsExited = false;
	bIsExited = AddClient(IP, Port, SrvPort, Socket, StationID);
	//已存在
	QString stServiceTypeID = FindserviceTypeIDByPort(SrvPort);
	if (bIsExited)
	{
		//找到设备对应的UI行
		int RowIndex = -1;
		RowIndex=FindRowIndex(SrvPort, StationID);
		//未找到
		if (RowIndex < 0)
			return;
		ui.clientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(Count, 10)));
		ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.clientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.clientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.clientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(Socket)));
	}
	//第一次连接
	else
	{
		//更新UI
		int RowIndex = ui.clientList->rowCount();
		ui.clientList->insertRow(RowIndex);
		ui.clientList->setItem(RowIndex, 0, new QTableWidgetItem(stServiceTypeID));
		ui.clientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
		ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(ObserveTime));
		ui.clientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(Count, 10)));
		ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.clientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.clientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.clientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(Socket)));
	}
	LogWrite::DataLogMsgOutPut(stServiceTypeID+"有新的数据,台站号为:"+StationID+QString(",Socket号为:")+QString::number(Socket));
}

//添加到设备数组
bool Server_VS::AddClient(QString ip, int port, int serverpot, SOCKET socketID,QString StationID)
{
	bool bIsExist = false;
	int index = -1;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == serverpot)
		{
			index = i;
			for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				if (ClientInfo[i].clients[j].StationID == StationID)
				{
					QDateTime current_date_time = QDateTime::currentDateTime();
					ClientInfo[i].clients[j].LatestTimeOfHeartBeat = current_date_time;
					ClientInfo[i].clients[j].SocketID = socketID;
					ClientInfo[i].clients[j].Online = true;
					bIsExist = true;
				}
			}
			if (bIsExist)
				return bIsExist;
			QDateTime current_date_time = QDateTime::currentDateTime();
			CLIENTINFO clientinfo{ ip, port,socketID,StationID,current_date_time,true };
			ClientInfo[index].clients.push_back(clientinfo);
		}
	}
	return bIsExist;
}

//通过设备ip和端口查询到设备索引号
int Server_VS::FindRowIndex(int SrvPort, QString StationID)
{
	QString ServiceTypeID = FindserviceTypeIDByPort(SrvPort);
	Qt::MatchFlags flags;
	QList<QTableWidgetItem *> totalItems = ui.clientList->findItems(ServiceTypeID, flags);
	for (int i = 0; i < totalItems.count(); i++)
	{
		int row = totalItems[i]->row();
		QString strStationID = ui.clientList->item(row, 1)->text();
		if (StationID == strStationID)
		{
			return row;
		}
	}
	return -1;
}

//通过业务号和区站号找到Socket号
int Server_VS::FindSocketID(int ServiceTypeID, int StationID, int FacilityID)
{
	//判断区站号是否连接，未连接返回-1
	int CountOfServiceType = ClientInfo.size();
	if (CountOfServiceType < 0)
		return -1;
	for (int i = 0; i < CountOfServiceType; i++)
	{
		if (ClientInfo[i].ServiceID == ServiceTypeID)
		{
			int CountOfStations = ClientInfo[i].clients.size();
			for (int j = 0; j < CountOfStations; j++)
			{
				if (ClientInfo[i].clients[j].StationID == StationID)
					return ClientInfo[i].clients[j].SocketID;
			}
		}
	}
	return -1;
}

//通过连接端口找到业务类型
QString Server_VS::FindserviceTypeIDByPort(int SrvPort)
{
	QString serviceTypeID;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == SrvPort)
		{
			return ClientInfo[i].ServerName;
		}
	}
	return NULL;
}

//业务列表右键事件
void Server_VS::on_ServerList_customContextMenuRequested(const QPoint &pos)
{
	QTableWidgetItem* selecteditem = ui.ServerList->itemAt(pos); //get right click pos item
	if (selecteditem == 0)
		return;
	//找到业务数组中对应索引号
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == selecteditem->text())
		{
			iSelectIndexOfService = i;
		}
	}
	//菜单出现的位置为当前鼠标的位置
	pop_Menu_Service.exec(QCursor::pos());

}

//业务列表右键菜单
void Server_VS::CreateServerListActions()
{
	//创建一个action
	action_Attributes.setText(QString("属性"));
	action_dmtd.setText(QString("补抄数据"));
	connect(&action_Attributes, SIGNAL(triggered()), this, SLOT(Lib_Attri()));
	connect(&action_dmtd,SIGNAL(triggered()),this,SLOT(Func_DMTD()));
	//connect(ui.ActionDMTD, SIGNAL(triggered()), this, SLOT(Func_DMTD()));
	pop_Menu_Service.addAction(&action_dmtd);
	pop_Menu_Service.addAction(&action_Attributes);

}

////区站号列表右键事件
void Server_VS::on_clientList_customContextMenuRequested(const QPoint &pos)
{
	QTableWidgetItem* selecteditem = ui.clientList->itemAt(pos); //get right click pos item

	if (selecteditem == 0)
	{
		ServiceTypeItem = NULL;
		return;
	}
	int row = selecteditem->row();
	ServiceTypeItem = ui.clientList->item(row, 0);

	//菜单出现的位置为当前鼠标的位置
	pop_Menu_Client.exec(QCursor::pos());
}

//客户列表右键菜单
void Server_VS::CreateClientListActions()
{
	action_Comm.setText(QString("终端命令"));
	pop_Menu_Client.addAction(&action_Comm);
	connect(&action_Comm, SIGNAL(triggered()), this, SLOT(SendCOMM()));
}

//启动Lib服务
void Server_VS::Lib_Run(int ServerIndex)
{
	QTableWidgetItem* selecteditem = ui.ServerList->item(ServerIndex, 0); //获取选择行														
	if (selecteditem == 0)
		return;
	//找到业务数组中对应服务名称
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == selecteditem->text())
		{
			iSelectIndexOfService = i;
		}
	}
	//找到Lib路径，解析Lib
	QLibrary lib(ClientInfo[iSelectIndexOfService].Path);
	if (lib.load())
	{
		Char2Json func_Char2Json = (Char2Json)(lib.resolve("Char2Json"));
		if (func_Char2Json == NULL)
		{
			QMessageBox::warning(NULL, "错误", "Lib拆包函数加载错误!");
			return;
		}
		//启动一个IOCP来监听设备
		AddIOCP(func_Char2Json, ClientInfo[iSelectIndexOfService].ServerPortID, ClientInfo[iSelectIndexOfService].IP);
	}
}

//开启新的IOCP
void Server_VS::AddIOCP(Char2Json func, int port,QString ip)
{
	IOCP *iocp = new IOCP();
	//设备离线通知
	connect(iocp,SIGNAL(NoticfyOffLine(int,int)),this,SLOT(OffLine(int,int)),Qt::QueuedConnection);
	//设备数据错误通知
	connect(iocp, SIGNAL(NoticfyServerError(int)), this, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(iocp, SIGNAL(NoticfyServerUpdateUI( QString, QString, int, bool, QString, int,int,int)), this, SLOT(UpdateUI( QString, QString, int, bool, QString, int,int,int)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(iocp, SIGNAL(NoticfyServerOperateStatus(int)), this, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//主动发送终端命令接收数据通知
	connect(iocp, SIGNAL(NoticfyServerRecvValue(QJsonObject)), this, SLOT(GetCommandRecvValue(QJsonObject)), Qt::QueuedConnection);
	//心跳处理
	connect(iocp, SIGNAL(NoticfyServerHB(QString, int, int, int, QString, QString)), this, SLOT(HeartBeat(QString,int,int,int,QString,QString)), Qt::QueuedConnection);
	//数据拆包函数
	iocp->func_Char2Json = func;
	//启动监听号开始监听设备
	iocp->SetListenedPort(port,ip);
	//启动
	pool.start(iocp);

	//添加到业务数组
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == port)
		{
			ClientInfo[i].pICOP = iocp;
			ClientInfo[i].IsRun = true;
		}
	}
}

//心跳处理
void Server_VS::HeartBeat(QString IP,int Port,int SrvPort, int CltSocket,QString StationID,QString ServiceTypeID)
{
	bool bIsExited = false;
	QString serviceTypeID = FindserviceTypeIDByPort(SrvPort);
	//农委
	if (serviceTypeID == "农委气象业务")
	{
		if (SIM2Staion.contains(StationID))
		{
			//找到特定的“键-值”对
			QMap<QString, QString>::iterator it = SIM2Staion.find(StationID);
			StationID = it.value();
		}
	}
	bIsExited = AddClient(IP, Port, SrvPort, CltSocket, StationID);
	if (bIsExited)
	{
		//找到设备对应的UI行
		int RowIndex = -1;
		RowIndex= FindRowIndex(SrvPort, StationID);
		//未找到
		if (RowIndex < 0)
			return;
		
		ui.clientList->setItem(RowIndex, 0, new QTableWidgetItem(serviceTypeID));
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.clientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
		ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(current_date));
		//ui.clientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
		ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.clientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.clientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.clientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(CltSocket)));
	}
	//新的连接
	else
	{
		//更新UI
		int RowCount = ui.clientList->rowCount();
		ui.clientList->insertRow(RowCount);
		QString serviceTypeID = FindserviceTypeIDByPort(SrvPort);
		ui.clientList->setItem(RowCount, 0, new QTableWidgetItem(serviceTypeID));
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.clientList->setItem(RowCount, 1, new QTableWidgetItem(StationID));
		ui.clientList->setItem(RowCount, 2, new QTableWidgetItem(current_date));
		ui.clientList->setItem(RowCount, 3, new QTableWidgetItem("0"));
		//ui.clientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
		ui.clientList->setItem(RowCount, 5, new QTableWidgetItem("在线"));
		ui.clientList->setItem(RowCount, 6, new QTableWidgetItem(IP));
		ui.clientList->setItem(RowCount, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.clientList->setItem(RowCount, 8, new QTableWidgetItem(QString::number(CltSocket)));
	}
}

//读取SIM卡号配置文件，转成区站号
void Server_VS::Convert2StationID()
{
	//读取Command.ini路径
	QString path = QCoreApplication::applicationDirPath() + "//SIM2STATION.ini";
	//打开INI文件
	QSettings configIniRead(path, QSettings::IniFormat);
	//终端命令个数
	int Count = configIniRead.value("NW/Count").toInt();
	//遍历终端命令
	for (int i = 0; i < Count; i++)
	{
		QString key = "/NW/STATION" + QString::number(i);
		QString StationID = configIniRead.value(key).toString();
		key = "/NW/SIM" + QString::number(i);
		QString SIMID = configIniRead.value(key).toString();
		SIM2Staion.insert(SIMID, StationID);
	}
}

//停止Lib服务
void Server_VS::Lib_Stop(int ServerIndex)
{
	if (iSelectIndexOfService < 0)
		return;
	if (ClientInfo[iSelectIndexOfService].pICOP != NULL)
	{
		ClientInfo[iSelectIndexOfService].pICOP->Stop();
		ClientInfo[iSelectIndexOfService].IsRun = false;
		ClientInfo[iSelectIndexOfService].pICOP = NULL;
	}
}

//补抄数据
void Server_VS::Func_DMTD()
{
	//未选中业务服务
	if (iSelectIndexOfService < 0)
		return;

	//初始化
	DMTDDlg dmtddlg;
	if (ClientInfo[iSelectIndexOfService].pICOP == NULL)
	{
		QMessageBox::warning(NULL,"错误","解析函数未加载，请先启动业务服务！");
		return;
	}
	dmtddlg.func_Char2Json = ClientInfo[iSelectIndexOfService].pICOP->func_Char2Json;
	dmtddlg.exec();

}

//打开系统运行日志
void Server_VS::OpenSYSLog()
{
	SYSLogDlg syslogdlg;
	syslogdlg.exec();
}

//查看数据运行日志
void Server_VS::OpenDataLog()
{
	DataLogDlg datalogdlg;
	datalogdlg.exec();
}

//查看业务属性
void Server_VS::Lib_Attri()
{
	if (iSelectIndexOfService < 0)
		return;
	ConfigWnd CfgWnd(this);
	//不能修改
	CfgWnd.DialogMode = false;
	//描述
	CfgWnd.m_Attribute = ClientInfo[iSelectIndexOfService].Attribute;;
	//端口号
	CfgWnd.m_Port = ClientInfo[iSelectIndexOfService].ServerPortID;
	CfgWnd.exec();
}

//发送终端命令
void Server_VS::SendCOMM()
{
	//选中区站号，找到对应socket
	int row = ServiceTypeItem->row();
	QTableWidgetItem *SocketWidgetItem = ui.clientList->item(row, 8);
	int SocketID = SocketWidgetItem->text().toInt();
	int severtype = -1;
	//int SocketID = -1;

	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == ServiceTypeItem->text())
		{
			severtype = ClientInfo[i].ServiceID;
			break;
		}
	}
	CommandDlg commdlg(severtype);
	commdlg.Socket = SocketID;
	connect(&commdlg,SIGNAL(NoticfyUICOMMSTR(QString)),this,SLOT(GetCommName(QString)));
	commdlg.exec();
}

//获取即时采集数据
void Server_VS::GetFeature()
{
	int severtype = -1;
	int SocketID = -1;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == ServiceTypeItem->text())
		{
			severtype = ClientInfo[i].ServiceID;
			for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				SocketID = ClientInfo[i].clients[j].SocketID;
			}
		}
	}
	switch (severtype)
	{
	case HKQX:
	{
		QString Comm = "SNAPSHOT\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	default:
		break;
	}
}

//获取参数设置
void Server_VS::GetConfig()
{

}

//获取终端命令名称
void Server_VS::GetCommName(QString CommName)
{
	strOperateType = CommName;
}

//自动校正时钟
void Server_VS::SetTimeCorrection()
{
	LogWrite::SYSLogMsgOutPut("自动矫正时钟开始");
	//获取网络时间
	QTcpSocket *socket = new QTcpSocket();
	socket->connectToHost("time.nist.gov", 13);
	QString datetime;
	if (socket->waitForConnected())
	{
		if (socket->waitForReadyRead())
		{
			QString str(socket->readAll());
			str = str.trimmed();
			str = str.section(" ", 1, 2);
			datetime = "20" + str;
		}
	}
	socket->close();
	delete socket;
	socket = NULL;
	QDateTime current_datetime = QDateTime::fromString(datetime,"yyyy-MM-dd hh:mm:ss");
	uint diff_time= current_datetime.toTime_t();
	diff_time += 28800;//北京时间 需要加上8小时
	QDateTime nowtime = QDateTime::fromTime_t(diff_time);
	datetime=nowtime.toString("yyyy.MM.dd hh:mm:ss"); 
	//校正设备时钟
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		switch (ClientInfo[i].ServiceID)
		{
		case NW:case HKQX:case NTXQH:case JTQX:
		{
			for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				int socketID = ClientInfo[i].clients[j].SocketID;
				QString Comm = "DATETIME " + datetime + "\r\n";
				QByteArray ba = Comm.toLatin1();
				LPCSTR ch = ba.data();
				int len = Comm.length();
				::send(socketID, ch, len, 0);
			}
			break;
		}
		case TRSF:
		{
			//for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			//{
			//	int socketID = ClientInfo[i].clients[j].SocketID;
			//	BYTE bytes[1024];
			//	bytes[0] = 0xff;
			//	bytes[1] = 0xff;
			//	bytes[2] = 0xff;
			//	bytes[3] = 0xaa;
			//	bytes[4] = 0x0a;
			//	bytes[5] = 0x81;
			//	bytes[6] = 0x00;
			//	//bytes[7] = 0x;//目的地址
			//	bytes[8] = 0x14;//20
			////	bytes[9] = 0x;//2018
			//	bytes[10] = 0xff;//月
			//	bytes[11] = 0xff;//日
			//	bytes[12] = 0xff;//时
			//	bytes[13] = 0xff;//分
			//	bytes[14] = 0xff;//秒
			//	bytes[15] = 0xff;//校验位
			//	bytes[16] = 0xdd;
			//	bytes[17] = 0xff;
			//	
			//	//::send(socketID, ch, len, 0);
			//}
			break;
		}
		default:
			break;
		}
	}
	LogWrite::SYSLogMsgOutPut("自动矫正时钟结束");
}

//自动补抄
void Server_VS::CheckDataCorrection()
{

}

//业务列表点击
void Server_VS::on_ServerList_itemClicked(QTableWidgetItem *item)
{
	iSelectIndexOfService = item->row();
}

//离线处理
void Server_VS::OffLine(int SrvPort, int CltSocket)
{
	QString StationID;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == SrvPort)
		{
			for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				//找到离线
				if (ClientInfo[i].clients[j].SocketID == CltSocket)
				{
					StationID = ClientInfo[i].clients[j].StationID;
					ClientInfo[i].clients[j].SocketID = 0;
					ClientInfo[i].clients[j].Online = false;
					break;
				}
			}
			break;
		}
	}
		//找到设备对应的UI行
		int RowIndex = -1;
		RowIndex = FindRowIndex(SrvPort, StationID);
		//未找到
		if (RowIndex < 0)
			return;
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(current_date));
		ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem("离线"));
		LogWrite::SYSLogMsgOutPut("区站号 " + StationID + "已经断开连接");
}