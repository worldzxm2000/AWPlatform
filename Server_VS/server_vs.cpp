#include "server_vs.h"
#include<QJsonDocument>
#include<qfiledialog.h>
#include"ConfigWnd.h"
//#include"QtNetwork"
//#include<QtNetwork>
#include <iphlpapi.h>
#include"CommandDlg.h"
#include"qdebug.h"
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
	//业务类型列表
	connect(ui.ServerList, SIGNAL(NoticfyServerRun(int)), this, SLOT(Lib_Run(int)));
	connect(ui.ServerList, SIGNAL(NoticfyServerStop(int)), this, SLOT(Lib_Stop(int)));
	ui.ServerList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateServerListActions();

	//设备连接列表
	ui.clientList->setColumnCount(9);
	ui.clientList->setHorizontalHeaderLabels(QStringList() << "业务类型" << "区站号" << "时间" << "数据数量" << "设备状态" << "连接" << "IP" << "端口号"<<"socket号");
	QHeaderView *header = ui.clientList->verticalHeader();
	header->setHidden(true);// 隐藏行号 
	ui.clientList->setColumnHidden(8, true);//隐藏第九列
	ui.clientList->setColumnHidden(4, true);//隐藏第四列
	ui.clientList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.clientList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.clientList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.clientList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.clientList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	ui.clientList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.clientList->setColumnWidth(2, 200);
	ui.clientList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateClientListActions();

	//心跳监听时间
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(Func_HeartBeat()));
	timer->start(1000 * 60*6);
	iSelectIndexOfService = -1;
	LRESULT pResult = -1;
	//消息中间件的初始化
	pResult = InitializeMQ();

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
		break;
	}

}

//析构函数
Server_VS::~Server_VS()
{
	timer->stop();
	delete socket4web;
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].pICOP != NULL)
		{
			if (ClientInfo[i].pICOP->GetStatus())
				ClientInfo[i].pICOP->Stop();
		}
	}
}

//心跳监听
void Server_VS::Func_HeartBeat()
{
	QDateTime currentTime= QDateTime::currentDateTime();
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		for (int j = 0; j <ClientInfo[i].clients.size(); j++)
		{
			int time_t = currentTime.toTime_t() - ClientInfo[i].clients[j].LatestTimeOfHeartBeat.toTime_t();
			//大于2分钟
			if (time_t > 60*5-1)
			{
				SetFacilityOffLine(ClientInfo[i].clients[j].SocketID);
				//将此设备Socket断开
				int result=closesocket(ClientInfo[i].clients[j].SocketID);
				ClientInfo[i].clients.erase(ClientInfo[i].clients.begin() + j);
				int x = 10;
			}
		}
	}
}

//设置设备在线离线状态
void Server_VS:: SetFacilityOffLine(int SocketID)
{
	for (int i = 0; i < ui.clientList->rowCount(); i++)
	{
		if (ui.clientList->item(i, 8)->text() == QString::number(SocketID))
		{
			//设置UI设备列表状态
			ui.clientList->setItem(i, 5, new QTableWidgetItem("离线"));
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			ui.clientList->setItem(i, 2, new QTableWidgetItem(current_date));
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
LRESULT Server_VS::InitializeCommandSocket()
{
	try
	{
		//开启WebSocket线程
		socket4web = new SocketServerForWeb();
		connect(socket4web, SIGNAL(NoticfyServerError(int)), this, SLOT(GetErrorMSG(int)), Qt::AutoConnection);
		//处理web端发送过来命令类型
		connect(socket4web, SIGNAL(NoticfyServerFacilityID(int, int, int, int, QString, QString)), this, SLOT(RequestForReadCOMM(int, int, int, int, QString, QString)), Qt::AutoConnection);
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

				if (ClientInfo[i].pICOP->GetStatus())
				{
					QMessageBox::warning(NULL, "警告", "请先停止运行，再删除业务！");
					return;
				}
				ClientInfo[i].pICOP->Stop();
			}
			ClientInfo.erase(ClientInfo.begin() + i);
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
	if (fileDialog->exec() == QDialog::Accepted)
	{
		strName = fileDialog->selectedFiles()[0];
	}
	else
	{
		return -3;
	}
	//读取dll
	QLibrary lib(strName);
	//读取成功
	if (lib.load())
	{
		GetServiceTypeID func_GetServiceTypeID = (GetServiceTypeID)lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName func_GetServiceTypeName = (GetServiceTypeName)lib.resolve("GetServiceTypeName");//获取业务名称
		//是否成功连接上 add() 函数  
		if (func_GetServiceTypeID&&func_GetServiceTypeName)
		{
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
			CfgWnd.exec();
			if (!IsLegallyPort(CfgWnd.m_Port))
				return -2;
			//添加到业务类型内存中
			Facility fcty;
			fcty.pICOP = NULL;
			fcty.ServiceID = ServiceID;
			fcty.ServerPortID = CfgWnd.m_Port;
			fcty.ServerName = func_GetServiceTypeName();
			fcty.Path = strName;
			fcty.Attribute = CfgWnd.m_Attribute;
			ui.ServerList->AddRow(fcty.ServerName, strName);
			//设备连接信息
			ClientInfo.push_back(fcty);
			lib.unload();
		}
		else
		{
			return 0;
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

//终端命令返回操作状态
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
	QJsonObject::Iterator it;
	QString keyString = "";
	QString valueString = "";
	for (it = RecvJson.begin(); it != RecvJson.end(); it++)
	{
		keyString = it.key();
		if (keyString == "RecvValue1" || keyString == "RecvValue2" || keyString == "RecvValue3" || keyString == "RecvValue4")
		{
			valueString += it.value().toString();
		}
	}
	ui.StatusLabel->setText(strOperateType+":"+valueString);
	socket4web->Send2WebServerJson(RecvJson);
}

//终端返回读取值
void Server_VS::GetCommandRecvValue(QJsonObject RecvJson, bool IsComm)
{

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
	case -1:
		strMSG = "通信异常！";
		break;
	case -2:
		strMSG = "来自非本业务的数据";
		break;
	default:
		strMSG = QString::number(error);
		break;
	}
	ui.StatusLabel->setText(strMSG);
}

//设备发送数据  "业务类型"<< "设备号" << "时间" << "上传数量"<<"设备状态"<<"连接"<<"IP"<<"Socket"
void Server_VS::UpdateUI(QString serviceTypeID, QString stationID, QString observeTime, int count, bool connected, QString ip, int port,int socket)
{
	//找到设备对应的UI行
	int RowIndex = FindRowIndex(ip, port);
	//未找到
	if (RowIndex < 0)
		return;
	//将台站号添加到内存
	AddClientInfoStation(ip, port, stationID);
	bool ok;
	QString stServiceTypeID = FindserviceTypeIDByServiceID(serviceTypeID.toInt(&ok, 10));
	ui.clientList->setItem(RowIndex, 0, new QTableWidgetItem(stServiceTypeID));
	ui.clientList->setItem(RowIndex, 1, new QTableWidgetItem(stationID));
	ui.clientList->setItem(RowIndex, 2, new QTableWidgetItem(observeTime));
	ui.clientList->setItem(RowIndex, 3, new QTableWidgetItem(QString::number(count, 10)));
	QString strConnected = connected == true ? "已连接" : "已断开";
	ui.clientList->setItem(RowIndex, 5, new QTableWidgetItem(strConnected));
	ui.clientList->setItem(RowIndex, 6, new QTableWidgetItem(ip));
	ui.clientList->setItem(RowIndex, 7, new QTableWidgetItem(QString::number(port, 10)));
	ui.clientList->setItem(RowIndex,8,new QTableWidgetItem(QString::number(socket)));
}

//添加区站号
void Server_VS::AddClientInfoStation(QString ip, int port, QString StationID)
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

//有新的客户端连接 "业务类型" << "设备号" << "时间" << "上传数量"<<"设备状态"<<"连接"<<"IP"<<"Socket"
void Server_VS::AddNewClient(QString clientIp, int clientPort, int serverPort, int socketID)
{
	//添加到业务数组内存
	AddClient(clientIp, clientPort, serverPort, socketID);
	//更新UI
	int RowCount = ui.clientList->rowCount();
	ui.clientList->insertRow(RowCount);
	QString serviceTypeID = FindserviceTypeIDByPort(serverPort);
	ui.clientList->setItem(RowCount, 0, new QTableWidgetItem(serviceTypeID));
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	ui.clientList->setItem(RowCount, 1, new QTableWidgetItem("未知"));
	ui.clientList->setItem(RowCount, 2, new QTableWidgetItem(current_date));
	ui.clientList->setItem(RowCount, 3, new QTableWidgetItem("0"));
	//ui.clientList->setItem(RowCount, 4, new QTableWidgetItem("未知"));
	ui.clientList->setItem(RowCount, 5, new QTableWidgetItem("已连接"));
	ui.clientList->setItem(RowCount, 6, new QTableWidgetItem(clientIp));
	ui.clientList->setItem(RowCount, 7, new QTableWidgetItem(QString::number(clientPort, 10)));
	ui.clientList->setItem(RowCount, 8, new QTableWidgetItem(QString::number(socketID)));
	//ReleaseMutex(hMutex);
}

//添加到设备数组
void Server_VS::AddClient(QString ip, int port, int serverpot, SOCKET socketID)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == serverpot)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			CLIENTINFO clientinfo{ ip, port,socketID,0,current_date_time };
			ClientInfo[i].clients.push_back(clientinfo);
		}
	}
}

//添加区站号
void Server_VS::AddNewConnectStationID(QJsonObject RecvJson)
{
	//获取业务类别，区站号，IP和端口号
	QString ServiceTypeID = RecvJson.find("ServiceTypeID").value().toString();
	QString StationID = RecvJson.find("StationID").value().toString();
	QString IP = RecvJson.find("IP").value().toString();
	int Port = RecvJson.find("Port").value().toInt();
	//查找索引号
	int RowIndex = FindRowIndex(IP, Port);
	//未找到
	if (RowIndex < 0)
		return;
	AddClientInfoStation(IP, Port, StationID);
	ui.clientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
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
					return ClientInfo[i].clients[j].SocketID;
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
	connect(&action_Attributes, SIGNAL(triggered()), this, SLOT(Lib_Attri()));
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
		AddIOCP(func_Char2Json, ClientInfo[iSelectIndexOfService].ServerPortID);
	}
}

//开启新的IOCP
void Server_VS::AddIOCP(Char2Json func, int port)
{
	IOCP *iocp = new IOCP();
	//新设备连接通知
	connect(iocp, SIGNAL(NoticfyUINewClient(QString, int, int, int)), this, SLOT(AddNewClient(QString, int, int, int)), Qt::QueuedConnection);
	//设备数据错误通知
	connect(iocp, SIGNAL(NoticfyServerError(int)), this, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(iocp, SIGNAL(NoticfyServerUpdateUI(QString, QString, QString, int, bool, QString, int,int)), this, SLOT(UpdateUI(QString, QString, QString, int, bool, QString, int,int)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(iocp, SIGNAL(NoticfyServerOperateStatus(int)), this, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//主动发送终端命令接收数据通知
	connect(iocp, SIGNAL(NoticfyServerRecvValue(QJsonObject)), this, SLOT(GetCommandRecvValue(QJsonObject)), Qt::QueuedConnection);
	connect(iocp, SIGNAL(NoticfyServerRecvValue(QJsonObject,bool)), this, SLOT(GetCommandRecvValue(QJsonObject,bool)), Qt::QueuedConnection);
	//新设备连接获取台站号通知
	connect(iocp, SIGNAL(NoticfyServerNewConnectionStationID(QJsonObject)), this, SLOT(AddNewConnectStationID(QJsonObject)), Qt::QueuedConnection);
	//心跳处理
	connect(iocp, SIGNAL(NoticfyServerHB(int)), this, SLOT(HeartBeat(int)), Qt::QueuedConnection);
	//数据拆包函数
	iocp->func_Char2Json = func;
	//启动监听号开始监听设备
	iocp->SetListenedPort(port);
	//启动
	pool.start(iocp);

	//添加到业务数组
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerPortID == port)
		{
			ClientInfo[i].pICOP = iocp;
		}
	}
}

//心跳处理
void Server_VS::HeartBeat( int Socket)
{
	for (int i = 0; i < ClientInfo.size(); i++)
	{
		for (int j = 0; j < ClientInfo[i].clients.size(); j++)
		{
			//通过socket找到设备的最新上传时间
			if (ClientInfo[i].clients[j].SocketID == Socket)
			{
				QDateTime current_date_time = QDateTime::currentDateTime();
			    ClientInfo[i].clients[j].LatestTimeOfHeartBeat=current_date_time;
			}
		}
	}
}

//停止Lib服务
void Server_VS::Lib_Stop(int ServerIndex)
{
	if (iSelectIndexOfService < 0)
		return;
	if (ClientInfo[iSelectIndexOfService].pICOP != NULL)
		ClientInfo[iSelectIndexOfService].pICOP->Stop();

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
	int row = ServiceTypeItem->row();
	//QTableWidgetItem *IPWidgetItem = ui.clientList->item(row, 6);
	//QTableWidgetItem *PortWidgetItem = ui.clientList->item(row, 7);
	QTableWidgetItem *SocketWidgetItem = ui.clientList->item(row, 8);
	int SocketID = SocketWidgetItem->text().toInt();
	//int port = PortWidgetItem->text().toInt();
	//QString ip = IPWidgetItem->text();
	int severtype = -1;
	//int SocketID = -1;

	for (int i = 0; i < ClientInfo.size(); i++)
	{
		if (ClientInfo[i].ServerName == ServiceTypeItem->text())
		{
			severtype = ClientInfo[i].ServiceID;
			break;
			/*for (int j = 0; j < ClientInfo[i].clients.size(); j++)
			{
				if (ClientInfo[i].clients[j].IP ==ip && ClientInfo[i].clients[j].Port ==port )
					SocketID = ClientInfo[i].clients[j].SocketID;
			}*/
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
