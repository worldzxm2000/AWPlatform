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
#include"qdockwidget.h"
#include<qtoolbutton.h>
#include <QMouseEvent>

using namespace std;
//消息中间件
SimpleProducer g_SimpleProducer, g_SimpleProducer_ZDH;
//构造函数
Server_VS::Server_VS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ConfigWindow();
	this->setFixedSize(1280, 660);
	strOperateType = "未知操作";
	pool.setMaxThreadCount(1024);
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
	ui.ClientList->setColumnCount(5);
	ui.ClientList->setHorizontalHeaderLabels(QStringList() << "业务类型" << "区站号" << "登录时间"<< "设备状态" << "最新刷新时间");
    ui.ClientList->verticalHeader()->setHidden(true);// 隐藏行号 
	ui.ClientList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.ClientList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.ClientList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.ClientList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.ClientList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(77,77,77);color:white}"); //设置表头背景色

	ui.ClientList->setColumnWidth(0, 200);
	ui.ClientList->setColumnWidth(1, 200);
	ui.ClientList->setColumnWidth(2, 200);
	ui.ClientList->setColumnWidth(3, 200);
	ui.ClientList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.ClientList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.ClientList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateClientListActions();

	connect(ui.RemoveBtn, SIGNAL(clicked()), this, SLOT(on_DeleteBtn_clicked()));
	connect(ui.MiniBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	LogWrite::SYSLogMsgOutPut("主程序已启动...");
	//ListCtrl控件当前选择行
	iSelectedRowOfServiceListCtrl = -1;
	iSelectedRowOfClientListCtrl = -1;

	LRESULT pResult = -1;
	//web服务器Socket的初始化
	pResult = InitializeCommandSocket();
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
	delete socket4web;
	socket4web = nullptr;
}

void Server_VS::ConfigWindow()
{
	setWindowFlags(Qt::FramelessWindowHint);
	try
	{
		string brokerURI;
		string destURI;
		string destURI_1;
		string UserName;
		string Password;
		bool useTopics;
		bool clientAck;

		activemq::library::ActiveMQCPP::initializeLibrary();
		UserName = "admin";
		Password = "admin";
		brokerURI = "tcp://117.158.216.250:61616";

		unsigned int numMessages = 2000;
		destURI = "DataFromFacility";
		destURI_1 = "ZDH";
		clientAck = false;
		useTopics = false;
		g_SimpleProducer.start(UserName, Password, brokerURI, numMessages, destURI, useTopics, clientAck);
		g_SimpleProducer_ZDH.start(UserName, Password, brokerURI, numMessages, destURI_1, useTopics, clientAck);
		return;
	}
	catch (const std::exception&)
	{
		return;
	}
	
}


void Server_VS::slot_minWindow()
{
	this->showMinimized();
}

void Server_VS::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void Server_VS::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void Server_VS::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

//初始化Web监听线程
LRESULT Server_VS::InitializeCommandSocket()
{
	try
	{
		//开启WebSocket线程
		socket4web = new SocketServerForWeb();
		connect(socket4web, SIGNAL(GetErrorSignal(int)), this, SLOT(GetErrorMSG(int)), Qt::AutoConnection);
		//处理web端发送过来命令类型
		connect(socket4web, SIGNAL(NoticfyServerFacilityID(int, QString, QString, int, QString, QString)), this, SLOT(RequestForReadCOMM(int, QString, QString, int, QString, QString)), Qt::AutoConnection);
		socket4web->m_portServer = 1030;
		socket4web->setAutoDelete(false);
		pool.start(socket4web);
		return 1;
	}
	catch (const std::exception&)
	{
		return -2;
	}
}

//读取设备参数指令
void Server_VS::RequestForReadCOMM(int ServiceTypeID, QString StationID, QString FacilityID, int Command, QString Params1, QString Params2)
{
	//通过业务号和区站号找到对应的Socket号
	if (EHTPool.GetEHT(ServiceTypeID) == NULL)
		return;
	//发送指令
	EHTPool.GetEHT(ServiceTypeID)->SendCommand(OPCommand(Command), StationID, Params1, Params2, true);
	
}

//添加Lib服务
void Server_VS::on_AddBtn_clicked()
{
	//初始化服务
	//加载动态解析DLL
	LRESULT pResult = AddDll();
	switch (pResult)
	{
	case -1:
		QMessageBox::information(this, tr("错误"), tr("动态链接库加载错误！"));
		break;
	case -2:
		QMessageBox::information(this, tr("错误"), tr("端口已被占用！"));
		break;
	default:
		break;
	}
}

//移除Lib
void Server_VS::on_DeleteBtn_clicked()
{
	if (iSelectedRowOfServiceListCtrl < 0)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 0)->text();
	//移除EHT
	EHTPool.Stop(ServiceName);
	//移除设备列表
	for (int i = ui.ClientList->rowCount()-1; i >-1; i--)
	{
		if (ui.ClientList->item(i,0)->text()== ServiceName)
		{
			ui.ClientList->removeRow(i);
		}
	}
	//从UI列表中移除
	ui.ServerList->removeRow(iSelectedRowOfServiceListCtrl);
}


//添加解析DLL
LRESULT Server_VS::AddDll()
{
	int errCode = 0;
	QString strName;
	//打开选择文件的对话框
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(tr("选择加载动态链接库"));
	fileDialog.setDirectory(".");
	fileDialog.setNameFilter(tr("DLL Files(*.dll)"));
	if (fileDialog.exec() != QDialog::Accepted)
		return 0;
	strName = fileDialog.selectedFiles()[0];
	//创建
	EHT *pEHT=new EHT(this);
	connect(pEHT, SIGNAL(OnLineSignal(QString, QString, QDateTime, QDateTime)), this, SLOT(RefreshListCtrl(QString, QString, QDateTime, QDateTime)));
	connect(pEHT, SIGNAL(OffLineSignal(QString, QString, QDateTime, QDateTime)), this, SLOT(OffLineListCtrl(QString, QString, QDateTime, QDateTime)));
	connect(pEHT, SIGNAL(SendToWebServiceSignal(QJsonObject)), socket4web,SLOT(SendToWebServiceSlot(QJsonObject)));
	int size = sizeof(EHT);
	LRESULT pResult = pEHT->LoadLib(strName);
	if (pResult<1)
		return pResult;
	ui.ServerList->AddRow(pEHT->GetServiceName(), strName);
	EHTPool.Start(pEHT);
	return 1;
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
    LogWrite::LogWrite();
}

//终端命令返回读取值
void Server_VS::GetCommandRecvValue(QJsonObject RecvJson)
{
	QJsonObject::Iterator it;
	QString keyString = "";
	QString valueString = "";
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
	LogWrite::SYSLogMsgOutPut(strMSG);
}

//刷新设备ListCtrl控件
void Server_VS::RefreshListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime)
{
	int RowIndex = FindRowIndex(SrvName, StationID);
	if (RowIndex < 0)//需要添加新的一行
	{
		//更新UI
		RowIndex = ui.ClientList->rowCount();
		ui.ClientList->insertRow(RowIndex);
	}
	ui.ClientList->setItem(RowIndex, 0, new QTableWidgetItem(SrvName));
	ui.ClientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
	ui.ClientList->setItem(RowIndex, 2, new QTableWidgetItem(LoginTime.toString("yyyy-MM-dd hh:mm:ss")));
	ui.ClientList->setItem(RowIndex, 3, new QTableWidgetItem("在线"));
	ui.ClientList->setItem(RowIndex, 4, new QTableWidgetItem(LastTime.toString("yyyy-MM-dd hh:mm:ss")));
}

void Server_VS::OffLineListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime)
{
	int RowIndex = FindRowIndex(SrvName, StationID);
	if (RowIndex < 0)//未找到
		return;
	ui.ClientList->setItem(RowIndex, 3, new QTableWidgetItem("离线"));

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
		RowIndex=FindRowIndex(stServiceTypeID, StationID);
		//未找到
		if (RowIndex < 0)
			return;
		ui.ClientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(Count, 10)));
		ui.ClientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.ClientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.ClientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.ClientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(Socket)));
	}
	//第一次连接
	else
	{
		//更新UI
		int RowIndex = ui.ClientList->rowCount();
		ui.ClientList->insertRow(RowIndex);
		ui.ClientList->setItem(RowIndex, 0, new QTableWidgetItem(stServiceTypeID));
		ui.ClientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
		ui.ClientList->setItem(RowIndex, 2, new QTableWidgetItem(ObserveTime));
		ui.ClientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(Count, 10)));
		ui.ClientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.ClientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.ClientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.ClientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(Socket)));
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
int Server_VS::FindRowIndex(QString SrvName, QString StationID)
{
	QList<QTableWidgetItem *> totalItems = ui.ClientList->findItems(SrvName, Qt::MatchFixedString);
	for (int i = 0; i < totalItems.count(); i++)
	{
		int row = totalItems[i]->row();
		QString strStationID = ui.ClientList->item(row, 1)->text();
		if (StationID.toUpper().compare(strStationID.toUpper()) == 0)
			return row;
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
	QTableWidgetItem *SelectItem = ui.ServerList->itemAt(pos);
	if (SelectItem == NULL)
		return;
	iSelectedRowOfServiceListCtrl = SelectItem->row(); //get right click pos item
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

//区站号列表右键事件
void Server_VS::on_ClientList_customContextMenuRequested(const QPoint &pos)
{
	QTableWidgetItem *SelectItem = ui.ClientList->itemAt(pos);
	if (SelectItem == NULL)
		return;
	iSelectedRowOfClientListCtrl = SelectItem->row(); //get right click pos item
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
	QTableWidgetItem* SelectedItem = ui.ServerList->item(ServerIndex, 0); //获取选择行														
	if (SelectedItem == 0)
		return;
	int Row = SelectedItem->row();
	EHTPool.Run(ui.ServerList->item(Row, 0)->text());
}
//停止Lib服务
void Server_VS::Lib_Stop(int ServerIndex)
{
	QTableWidgetItem* SelectedItem = ui.ServerList->item(ServerIndex, 0); //获取选择行														
	if (SelectedItem == 0)
		return;
	int Row = SelectedItem->row();
	EHTPool.Pause(ui.ServerList->item(Row, 0)->text());
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
		RowIndex= FindRowIndex(ServiceTypeID, StationID);
		//未找到
		if (RowIndex < 0)
			return;
		
		ui.ClientList->setItem(RowIndex, 0, new QTableWidgetItem(serviceTypeID));
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.ClientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
		ui.ClientList->setItem(RowIndex, 2, new QTableWidgetItem(current_date));
		//ui.ClientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
		ui.ClientList->setItem(RowIndex, 5, new QTableWidgetItem("在线"));
		ui.ClientList->setItem(RowIndex, 6, new QTableWidgetItem(IP));
		ui.ClientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.ClientList->setItem(RowIndex, 8, new QTableWidgetItem(QString::number(CltSocket)));
	}
	//新的连接
	else
	{
		//更新UI
		int RowCount = ui.ClientList->rowCount();
		ui.ClientList->insertRow(RowCount);
		QString serviceTypeID = FindserviceTypeIDByPort(SrvPort);
		ui.ClientList->setItem(RowCount, 0, new QTableWidgetItem(serviceTypeID));
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.ClientList->setItem(RowCount, 1, new QTableWidgetItem(StationID));
		ui.ClientList->setItem(RowCount, 2, new QTableWidgetItem(current_date));
		ui.ClientList->setItem(RowCount, 3, new QTableWidgetItem("0"));
		//ui.ClientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
		ui.ClientList->setItem(RowCount, 5, new QTableWidgetItem("在线"));
		ui.ClientList->setItem(RowCount, 6, new QTableWidgetItem(IP));
		ui.ClientList->setItem(RowCount, 7, new QTableWidgetItem(QString::number(Port, 10)));
		ui.ClientList->setItem(RowCount, 8, new QTableWidgetItem(QString::number(CltSocket)));
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



//补抄数据
void Server_VS::Func_DMTD()
{
	//未选中业务服务
	if (iSelectedRowOfServiceListCtrl < 0)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 0)->text();
	//初始化
	DMTDDlg dmtddlg;
	dmtddlg.func_Char2Json =EHTPool.GetEHT(ServiceName)->GetDataFunc();
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
	if (iSelectedRowOfServiceListCtrl < 0)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 0)->text();
	ConfigWnd CfgWnd(this);
	//不能修改
	CfgWnd.DialogMode = false;
	//描述
	CfgWnd.m_Attribute = EHTPool.GetEHT(ServiceName)->GetAttribute();
	////端口号
	CfgWnd.m_Port = EHTPool.GetEHT(ServiceName)->GetPort();
	CfgWnd.exec();
}

//发送终端命令
void Server_VS::SendCOMM()
{
	QString ServiceName = ui.ClientList->item(iSelectedRowOfClientListCtrl, 0)->text();
	QString StationID = ui.ClientList->item(iSelectedRowOfClientListCtrl, 1)->text();
	int SeverID = EHTPool.GetEHT(ServiceName)->GetServiceID();
	CommandDlg commdlg(SeverID);
	commdlg.Socket = EHTPool.GetEHT(ServiceName)->GetSocket(StationID);
	connect(&commdlg,SIGNAL(NoticfyUICOMMSTR(QString)),this,SLOT(GetCommName(QString)));
	commdlg.exec();
}

//获取即时采集数据
void Server_VS::GetFeature()
{
	//int severtype = -1;
	//int SocketID = -1;
	//for (int i = 0; i < ClientInfo.size(); i++)
	//{
	//	if (ClientInfo[i].ServerName == ServiceTypeItem->text())
	//	{
	//		severtype = ClientInfo[i].ServiceID;
	//		for (int j = 0; j < ClientInfo[i].clients.size(); j++)
	//		{
	//			SocketID = ClientInfo[i].clients[j].SocketID;
	//		}
	//	}
	//}
	/*switch (severtype)
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
	}*/
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
	socket->connectToHost("time-a-g.nist.gov", 13);
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
	QString year, month, day, hour, min, sec;
	year = nowtime.toString("yy");
	month = nowtime.toString("MM");
	day = nowtime.toString("dd");
	hour = nowtime.toString("hh");
	min = nowtime.toString("mm");
	sec = nowtime.toString("ss");

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
				int result=::send(socketID, ch, len, 0);
				LogWrite::SYSLogMsgOutPut("台站号："+ClientInfo[i].clients[j].StationID+"自动矫正时钟:"+QString::number(result));
			}
			continue;
		}
		case TRSF:
		{
			for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				int chk = 0;
				int socketID = ClientInfo[i].clients[j].SocketID;
				int SrcAdrr = ClientInfo[i].clients[j].StationID.toInt();
				BYTE bytes[1024];
				bytes[0] = 0xaa;
				bytes[1] = 0x0a;//帧长度
				bytes[2] = 0x81;//帧命令
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//源地址 低八位
				chk += bytes[3];
				bytes[4] = (SrcAdrr >> 8) & 0xff; //高八位
				chk += bytes[4];
				bytes[5] = 0x14;//20
				chk += bytes[5];
				bytes[6] = year.toInt();
				chk += bytes[6];
				bytes[7] = month.toInt();
				chk += bytes[7];
				bytes[8] = day.toInt();
				chk += bytes[8];
				bytes[9] = hour.toInt();
				chk += bytes[9];
				bytes[10] = min.toInt();
				chk += bytes[10];
				bytes[11] = sec.toInt();
				chk += bytes[11];
				bytes[12] = chk & 0xff;//校验位 低八位
				bytes[13] = (chk>>8) & 0xff;//高八位
				bytes[14] = 0xff;
				int result=::send(socketID, (char *)bytes, 15, 0);
				LogWrite::SYSLogMsgOutPut("土壤水分"+ ClientInfo[i].clients[j].StationID +"自动矫正时钟:" + QString::number(result));
			}
			continue;
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
	iSelectedRowOfServiceListCtrl = item->row();
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
		RowIndex = FindRowIndex("", StationID);
		//未找到
		if (RowIndex < 0)
			return;
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		ui.ClientList->setItem(RowIndex, 2, new QTableWidgetItem(current_date));
		ui.ClientList->setItem(RowIndex, 5, new QTableWidgetItem("离线"));
		LogWrite::SYSLogMsgOutPut("区站号 " + StationID + "已经断开连接");
}