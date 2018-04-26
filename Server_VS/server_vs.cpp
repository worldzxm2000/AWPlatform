#include "server_vs.h"
#include<QJsonDocument>
#include"PluginInstance.h"
#include"PluginManager.h"
#include<qfiledialog.h>
#include"ConfigWnd.h"
#include<QtNetwork>
#include <iphlpapi.h>
using namespace std;
//消息中间件类
SimpleProducer g_SimpleProducer;
//HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

//构造函数
Server_VS::Server_VS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1024, 768);
	strOperateType = "";

	ui.ServerList->setColumnCount(2);
	ui.ServerList->setHorizontalHeaderLabels(QStringList() << "业务类型"<<"业务名称");
	QHeaderView *header = ui.ServerList->verticalHeader();
	header->setHidden(true);// 隐藏行号 
	ui.ServerList->setColumnHidden(1, true);//隐藏第二列
	ui.ServerList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.ServerList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.ServerList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.ServerList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.ServerList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	ui.ServerList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.ServerList->setContextMenuPolicy(Qt::CustomContextMenu);
	CreateServerListActions();

	ui.clientList->setColumnCount(8);
	ui.clientList->setHorizontalHeaderLabels(QStringList() << "业务类型" << "设备号" << "时间" << "数据数量" << "设备状态" << "连接" << "IP" << "端口号");

	header = ui.clientList->verticalHeader();
	header->setHidden(true);// 隐藏行号 
	ui.clientList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.clientList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.clientList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.clientList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.clientList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	ui.clientList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.clientList->setColumnWidth(2, 150);

	LRESULT pResult = -1;
	//消息中间件的初始化

	pResult = InitializeMQ();

	//web服务器Socket的初始化
	pResult = InitializeCommandSocket();

}

//析构函数
Server_VS::~Server_VS()
{
	delete socket4web;

	for (int i = 0; i < ClientInfo.size(); i++)
	{
		ClientInfo[i].pICOP->Stop();
	}
	//g_SimpleProducer.close();
	//setAttribute(Qt::WA_DeleteOnClose);
	//delete pop_Menu_Service;
	////运行
	//delete action_run;
	////停止
	//delete action_stop;
	////属性
	//delete action_Attributes;
	////客户列表右键菜单
	//delete pop_Menu_Client;
	////时间
	//delete action_Time;
	////高度
	//delete action_ALT;
	////经度
	//delete action_LONG;
	////纬度
	//delete action_LAT;
}

//初始化消息中间件
LRESULT Server_VS::InitializeMQ()
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

//初始化Web监听线程
LRESULT Server_VS::InitializeCommandSocket()
{
	//开启WebSocket线程
	socket4web = new SocketServerForWeb();
	//connect(socket4web, SIGNAL(NoticfyServerError(int)), this, SLOT());
	connect(socket4web, SIGNAL(NoticfyServerFacilityID(int, int, int, int, QString, QString)), this, SLOT(RequestForReadCOMM(int, int, int, int, QString, QString)), Qt::AutoConnection);
	socket4web->m_portServer = 1030;
	socket4web->setAutoDelete(false);
	pool.start(socket4web);
	return 1;
}

//读取设备参数指令
void Server_VS::RequestForReadCOMM(int ServiceTypeID, int StationID, int FacilityID, int Command,QString Param1 ,QString Param2)
{
	//通过业务号和区站号找到对应的Socket号
	int SocketID = FindSocketID(ServiceTypeID, StationID, FacilityID);
	if (SocketID == -1)
		GetCommandStatus(-1);
	//发送终端命令
	switch (Command)
	{
	case	BASEINFO:
	{
		QString Comm = "BASEINFO\r\n";
		if (Param1 != "NULL")
		{
			Comm = "BASEINFO "+Param1+"\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
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
	case CFSET:
	{
		QString Comm = "CFSET\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	case CAPTIME:
	{
		QString Comm = "CAPTIME\r\n";
		if (Param1 != "NULL")
		{
			Comm = "CAPTIME " + Param1 + " "+Param2+"\r\n";
		}
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
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
	case RESET:
	{
		QString Comm = "RESET\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	case UPDATE:
	{
		QString Comm = "UPDATE\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
	case SNAPSHOT:
	{
		QString Comm = "SNAPSHOT\r\n";
		QByteArray ba = Comm.toLatin1();
		LPCSTR ch = ba.data();
		int len = Comm.length();
		::send(SocketID, ch, len, 0);
		break;
	}
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
	default:
		break;
	}


}

//添加Lib服务
void Server_VS::on_RunBtn_clicked()
{

	//初始化服务
	//1 添加动态加载DLL
	//2 开辟一个线程，监听
	//3 设置信号槽
	InitServer();
	// iocp->StartSever(1031,NULL);
	//   QTreeWidgetItem *itemIOCP=new QTreeWidgetItem(ui->Servertree,iocp->facilityID);
}

//发送终端命令---设置时间
void Server_VS::on_SetTimeBtn_clicked()
{
	QJsonObject Json;
	Json.insert("RecvValue", 0);
	socket4web->Send2WebServerJson(Json);
}

//加载动态链接库
void Server_VS::InitServer()
{
	//加载动态解析DLL
	LRESULT pResult = AddDll();
	switch (pResult)
	{
	case 0:
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

//开启新的IOCP
void Server_VS::AddIOCP(Char2Json func,int port)
{
	IOCP *iocp = new IOCP();
	connect(iocp, SIGNAL(NoticfyUINewClient(QString, int, int, int)), this, SLOT(AddNewClient(QString, int, int, int)), Qt::QueuedConnection);
	connect(iocp, SIGNAL(NoticfyServerError(int)), this, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	connect(iocp, SIGNAL(NoticfyServerUpdateUI(QString, QString, QString, int, bool, bool, QString, int)), this, SLOT(UpdateUI(QString, QString, QString, int, bool, bool, QString, int)), Qt::QueuedConnection);
	connect(iocp, SIGNAL(NoticfyServerOperateStatus(int)), this, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	connect(iocp,SIGNAL(NoticfyServerRecvValue(QJsonObject)),this,SLOT(GetCommandRecvValue(QJsonObject)),Qt::QueuedConnection);
	connect(iocp,SIGNAL(NoticfyServerNewConnectionStationID(QString)),this,SLOT(AddNewConnectStationID(QString)),Qt::QueuedConnection);
	iocp->func_Char2Json = func;
	iocp->SetListenedPort(port);
	pool.start(iocp);
	
	//添加到业务数组
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID==port)
		{
			ClientInfo[i].pICOP = iocp;
		}
	}
}

//添加解析DLL
LRESULT Server_VS::AddDll()
{
	PluginManager &PluginManager = PluginManager::GetInstance();
	int errCode = 0;
	QString strName;
	//打开选择文件的对话框
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(tr("选择加载动态链接库"));
	fileDialog->setDirectory(".");
	fileDialog->setNameFilter(tr("DLL Files(*.dll)"));
	if (fileDialog->exec() == QDialog::Accepted) {
		strName = fileDialog->selectedFiles()[0];
	}
	else {
		return 0;
	}
	//读取dll
	QLibrary lib(strName);
	//读取成功
	if (lib.load())
	{
		GetServiceTypeID func_GetServiceTypeID = (GetServiceTypeID)lib.resolve("GetServiceTypeID");
		//是否成功连接上 add() 函数  
		if (func_GetServiceTypeID)
		{
			//获取业务类型
			int ServiceID = func_GetServiceTypeID();
			switch (ServiceID)
			{
				//土壤水分
			case TRSF:
			{
				for (int i = 0; i < ClientInfo.size(); i++)
				{
					if (ClientInfo[i].ServiceID == ServiceID)
						return -1;
				}
				//开启IP和端口设置窗体
				ConfigWnd CfgWnd(this);
				CfgWnd.exec();
				if (!IsLegallyPort(CfgWnd.m_Port))
					return -2;
				int RowCount = ui.ServerList->rowCount();
				ui.ServerList->insertRow(RowCount);
				ui.ServerList->setItem(RowCount, 0, new QTableWidgetItem("土壤水分业务"));
				ui.ServerList->setItem(RowCount, 1, new QTableWidgetItem(strName));
				Facility fcty;
				fcty.ServiceID = HKQX;
				fcty.ServerPortID = CfgWnd.m_Port;
				fcty.ServerName = "土壤水分业务";
				fcty.Path = strName;
				//设备连接信息
				ClientInfo.push_back(fcty);
				lib.unload();
				break;
			}
				//航空气象	
			case HKQX:
			{
				for (int i = 0; i < ClientInfo.size(); i++)
				{
					if (ClientInfo[i].ServiceID == ServiceID)
						return -1;
				}
				//开启IP和端口设置窗体
				ConfigWnd CfgWnd(this);
				CfgWnd.exec();
				if (!IsLegallyPort(CfgWnd.m_Port))
					return -2;
				int RowCount = ui.ServerList->rowCount();
				ui.ServerList->insertRow(RowCount);
				ui.ServerList->setItem(RowCount, 0, new QTableWidgetItem("航空气象业务"));
				ui.ServerList->setItem(RowCount, 1, new QTableWidgetItem(strName));
				Facility fcty;
				fcty.ServiceID = HKQX;
				fcty.ServerPortID = CfgWnd.m_Port;
				fcty.ServerName = "航空气象业务";
				fcty.Path = strName;
				//设备连接信息
				ClientInfo.push_back(fcty);
				lib.unload();
				break;
			}
			default:
				break;
			}
		}
	}
	return 1;
}

//判断port号的合法性
bool Server_VS::IsLegallyPort(int port)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == port)
			return false;
	}
	return true;
}

//终端命令返回信息
void Server_VS::GetCommandStatus(int result)
{
	//操作状态
	QString strOperateStatus;
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
		strOperateStatus = "";
		break;
	}
	ui.StatusLabel->setText(strOperateType + strOperateStatus);
}

//终端命令返回读取值
void Server_VS::GetCommandRecvValue(QJsonObject RecvJson)
{
	socket4web->Send2WebServerJson(RecvJson);
}

//获得错误信息
void Server_VS::GetErrorMSG(int error)
{
	QString strMSG;
	switch (error)
	{
	case 1:
		strMSG = "正常";
		break;
	case 0:
		strMSG = "通信异常！";
		break;
	default:
		strMSG = QString::number(error);
		break;
	}
	ui.StatusLabel->setText(strMSG);
}

//"业务类型" << "设备号" << "时间" << "上传数量"<<"设备状态"<<"连接"<<"IP"
//设备发送数据
void Server_VS::UpdateUI(QString serviceTypeID, QString stationID, QString observeTime, int count, bool stationStatus, bool connected, QString ip, int port)
{
	//	WaitForSingleObject(hMutex, INFINITE);
	int RowIndex = FindRowIndex(ip, port);
	//未找到
	if (RowIndex < 0)
		return;
	AddClientInfoStation(ip,port,stationID);
	bool ok;
	QString stServiceTypeID = FindserviceTypeIDByServiceID(serviceTypeID.toInt(&ok, 10));
	ui.clientList->setItem(RowIndex, 0, new QTableWidgetItem(stServiceTypeID));
	ui.clientList->setItem(RowIndex, 1, new QTableWidgetItem(stationID));
	ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(observeTime));
	ui.clientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(count, 10)));
	QString strStationStatus = stationStatus == true ? "已连接" : "已断开";
	ui.clientList->setItem(RowIndex, 4, new QTableWidgetItem(strStationStatus));
	QString strConnected = connected == true ? "已连接" : "已断开";
	ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem(strConnected));
	ui.clientList->setItem(RowIndex, 6, new QTableWidgetItem(ip));
	ui.clientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(port, 10)));
	//qApp->processEvents();
	//ReleaseMutex(hMutex);
}


void Server_VS::AddClientInfoStation(QString ip,int port,QString StationID)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		for (int j = 0; j < ClientInfo[i].clients.size(); j++)
		{
			if (ClientInfo[i].clients[j].IP == ip&&ClientInfo[i].clients[j].Port == port)
			{
				bool ok;
				ClientInfo[i].clients[j].StationID = StationID.toInt(&ok, 10);
			}
		}
	}
}
//有新的客户端连接 //"业务类型" << "设备号" << "时间" << "上传数量"<<"设备状态"<<"连接"<<"IP"
void Server_VS::AddNewClient(QString clientIp, int clientPort, int serverPort, int socketNo)
{
	//添加到内存
	AddClient(clientIp, clientPort, serverPort, socketNo);
	//更新UI
	int RowCount = ui.clientList->rowCount();
	ui.clientList->insertRow(RowCount);
	QString serviceTypeID = FindserviceTypeIDByPort(serverPort);
	ui.clientList->setItem(RowCount, 0, new QTableWidgetItem(serviceTypeID));
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	ui.clientList->setItem(RowCount, 1, new QTableWidgetItem("未知"));
	ui.clientList->setItem(RowCount, 2, new QTableWidgetItem(current_date));
	ui.clientList->setItem(RowCount, 3, new QTableWidgetItem("0"));
	ui.clientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
	ui.clientList->setItem(RowCount, 5, new QTableWidgetItem("已连接"));
	ui.clientList->setItem(RowCount, 6, new QTableWidgetItem(clientIp));
	ui.clientList->setItem(RowCount, 7, new QTableWidgetItem(QString::number(clientPort, 10)));
	//ReleaseMutex(hMutex);
}

//添加到设备数组
void Server_VS::AddClient(QString ip, int port, int serverpot, SOCKET socketNo)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == serverpot)
		{
			CLIENTINFO clientinfo{ ip, port,socketNo };
			ClientInfo[i].clients.push_back(clientinfo);
		}
	}
}

//添加区站号
void Server_VS::AddNewConnectStationID(QString StationID)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		
	}
}
//通过设备ip和端口查询到设备索引号
int Server_VS::FindRowIndex(QString ip, int port)
{
	Qt::MatchFlags flags;
	QList<QTableWidgetItem *> totalItems = ui.clientList->findItems(ip, flags);
	for (int i = 0; i < totalItems.count(); i++)
	{
		int row = ui.clientList->row(totalItems.at(i));
		QString strPort = ui.clientList->item(row, 7)->text();
		bool ok;
		if (strPort.toInt(&ok, 10) == port)
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
					return ClientInfo[i].clients[j].socketNO;
			}
		}
	}
	return -1;
}

//通过连接端口找到业务类型
QString Server_VS::FindserviceTypeIDByPort(int serverPort)
{
	QString serviceTypeID;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == serverPort)
		{
			return ClientInfo[i].ServerName;
		}
	}
	return NULL;
}

//通过连接端口找到业务类型
QString Server_VS::FindserviceTypeIDByServiceID(int serviceID)
{
	QString serviceTypeID;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServiceID == serviceID)
		{
			return ClientInfo[i].ServerName;
		}
	}
	return NULL;
}
//业务列表右键事件
void Server_VS::on_ServerList_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem* selecteditem = ui.ServerList->itemAt(pos) ; //get right click pos item
      /*
      * do sth  relative with current selected item
      *  QString finalStr = selecteditem->text();
      */

	//pop_menu->clear(); //清除原有菜单
	if (selecteditem == 0)
		return;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName== selecteditem->text())
		{
			iSelectIndex = ClientInfo[i].ServerPortID;
		}
	}
	//菜单出现的位置为当前鼠标的位置
	pop_Menu_Service.exec(QCursor::pos());

}

//业务列表右键菜单
void Server_VS::CreateServerListActions()
{
	//创建菜单项
	/*pop_Menu_Service = new QMenu();
	action_run = new QAction(this);
	action_stop = new QAction(this);
	action_Attributes = new QAction(this);*/

	action_run.setText(QString("启动"));
	action_stop.setText(QString("停止"));
	action_stop.setDisabled(true);
	action_Attributes.setText(QString("属性"));

	pop_Menu_Service.addAction(&action_run);
	connect(&action_run, SIGNAL(triggered()), this, SLOT(Lib_Run()));
	pop_Menu_Service.addAction(&action_stop);
	connect(&action_stop, SIGNAL(triggered()), this, SLOT(Lib_Stop()));
	pop_Menu_Service.addSeparator();
	pop_Menu_Service.addAction(&action_Attributes);

}

//区站号列表右键事件
void Server_VS::on_clientList_customContextMenuRequested(const QPoint &pos)
{
	QTableWidgetItem* selecteditem = ui.clientList->itemAt(pos); //get right click pos item
																
	if (selecteditem == 0)
		return;
	int row = selecteditem->row();
	QTableWidgetItem * ServiceTypeItem = ui.clientList->item(row,0);
	int iServicType = -1;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == ServiceTypeItem->text())
		{
			iServicType = ClientInfo[i].ServiceID;
		}
	}
	//菜单出现的位置为当前鼠标的位置
	pop_Menu_Client.exec(QCursor::pos());
}
//客户列表右键菜单
void Server_VS :: CreateClientListActions(int type)
{

	switch (type)
	{
	case TRSF:
	{
		QAction action_GetData;
		QAction action_GetConfig;
		action_GetData.setText(QString("获取即时采集数据"));
		action_GetConfig.setText(QString("获取参数设置"));

		pop_Menu_Client.addAction(&action_GetData);
		connect(&action_GetData, SIGNAL(triggered()), this, SLOT(Lib_Run()));
		pop_Menu_Client.addAction(&action_GetConfig);
		connect(&action_stop, SIGNAL(triggered()), this, SLOT(Lib_Stop()));

	}
	default:
		break;
	}
}

//启动Lib服务
void Server_VS::Lib_Run()
{
	if (iSelectIndex < 0)
		return;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == iSelectIndex)
		{
			QLibrary lib(ClientInfo[i].Path);
			if (lib.load())
			{
				Char2Json func_Char2Json = (Char2Json)(lib.resolve("Char2Json"));
				if (func_Char2Json == NULL)
					return;
				AddIOCP(func_Char2Json, ClientInfo[i].ServerPortID);
			}
		}
	}
	action_run.setDisabled(true);
	action_stop.setDisabled(false);
}

//停止Lib服务
void Server_VS::Lib_Stop()
{
	if (iSelectIndex < 0)
		return;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == iSelectIndex)
		{
			ClientInfo[i].pICOP->Stop();
		}
	}
	action_run.setDisabled(false);
	action_stop.setDisabled(true);
}

