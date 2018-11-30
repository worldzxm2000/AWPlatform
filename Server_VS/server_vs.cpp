#include "server_vs.h"
#include<QJsonDocument>
#include<QFileDialog>
#include"ConfigWnd.h"
#include<QtNetwork>
#include<QSettings>
#include <iphlpapi.h>
#include"CommandDlg.h"
#include"DMTDDlg.h"
#include"SYSLogDlg.h"
#include"DataLogDlg.h"
#include<QDockWidget>
#include<QApplication>
#include<QDesktopWidget>
#include<QtXml>
#include"MQConfigDlg.h"
//消息中间件
SimpleProducer g_SimpleProducer, g_SimpleProducer_ZDH,g_SimpleProducer_sh;

//构造函数
Server_VS::Server_VS(QWidget *parent)
	: QMainWindow(parent)
	, m_dockWidget(nullptr)

{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
	ConfigWindow();
	setFixedSize(1280, 660);
	strOperateType = "未知操作";
	ui.OnLineCountLabel->setText("当前在线设备个数：0");
	ui.NameLabel->setText("气象观测平台中心站 版本1.0");
	//pool.setMaxThreadCount(1024);
	addDockWidget(Qt::RightDockWidgetArea,ui.WarningDockWidget);
	slModel = new QStringListModel();
	slModel->setStringList(WarningInfoList);
	strView = new QListView();
	strView->setModel(slModel);
	ui.WarningDockWidget->setWidget(strView);
	addToolBarBreak();

	createDockWidgetBar(Qt::LeftDockWidgetArea);
	createDockWidgetBar(Qt::RightDockWidgetArea);
	createDockWidgetBar(Qt::TopDockWidgetArea);
	createDockWidgetBar(Qt::BottomDockWidgetArea);
	//menu功能
	connect(ui.action_SYSLog, SIGNAL(triggered()), this, SLOT(OpenSYSLog()));
	connect(ui.action_DataLog, SIGNAL(triggered()), this, SLOT(OpenDataLog()));
	//读取配置文件
	Convert2StationID();
	//业务类型列表
	connect(ui.ServerList, SIGNAL(NoticfyServerRun(int)), this, SLOT(Lib_Run(int)),Qt::DirectConnection);
	connect(ui.ServerList, SIGNAL(NoticfyServerStop(int)), this, SLOT(Lib_Stop(int)),Qt::DirectConnection);
	connect(ui.ServerList, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(ServerList_currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)));
	ui.ServerList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateServerListActions();

	//设备连接列表
	ui.ClientList->setColumnCount(6);
	ui.ClientList->setHorizontalHeaderLabels(QStringList() << "业务类型" << "区站号" <<"设备号"<< "登录时间"<< "设备状态" << "最新刷新时间");
    ui.ClientList->verticalHeader()->setHidden(true);// 隐藏行号 
	ui.ClientList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.ClientList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.ClientList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.ClientList->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.ClientList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(77,77,77);color:white}"); //设置表头背景色

	ui.ClientList->setColumnWidth(0, 200);
	ui.ClientList->setColumnWidth(1, 100);
	ui.ClientList->setColumnWidth(2, 100);
	ui.ClientList->setColumnWidth(3, 250);
	ui.ClientList->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.ClientList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.ClientList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	ui.AddBtn->setToolTipName("添加新业务");
	ui.RemoveBtn->setToolTipName("移除业务");
	//ui.UpLoadBtn->setToolTipName("补抄数据");
	ui.ControlBtn->setToolTipName("控制设备");
	ui.TerminalBtn->setToolTipName("查看终端返回值");
	ui.MQBtn->setToolTipName("消息中间件设置");
	ui.LogBtn->setToolTipName("查看日志");
	ui.CloseBtn->setToolTipName("关闭");
	ui.MinBtn->setToolTipName("最小化");
	ui.WarningBtn->setToolTipName("报警通知");
	connect(ui.RemoveBtn, SIGNAL(clicked()), this, SLOT(on_DeleteBtn_clicked()));
	connect(ui.LogBtn, SIGNAL(clicked()), this, SLOT(OpenSYSLog()));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.TerminalBtn, SIGNAL(clicked()), this, SLOT(OpenDataLog()));
	//connect(ui.UpLoadBtn,SIGNAL(clicked()),this,SLOT(Func_DMTD()));
	connect(ui.WarningBtn, SIGNAL(clicked()), this, SLOT(ShowWarningDockWidget()));
	connect(ui.ControlBtn, SIGNAL(clicked()), this, SLOT(OpenControlDlg()));
	connect(ui.MQBtn, SIGNAL(clicked()), this, SLOT(MQConfig()));
	LogWrite::SYSLogMsgOutPut("主程序已启动...");
	LogWrite::DataLogMsgOutPut("终端接收已启动...");
	//ListCtrl控件当前选择行
	iSelectedRowOfServiceListCtrl = -1;
	iSelectedRowOfClientListCtrl = -1;

	LRESULT pResult = -1;
	//web服务器Socket的初始化
	pResult = InitializeCommandSocket();
	switch (pResult)
	{
	case -1:
		QMessageBox::warning(this, "警告", "消息中间件服务初始化失败！");
		return;
	case -2:
		QMessageBox::warning(this, "警告", "Web服务器初始化失败!");
		return;
	default:
		LogWrite::SYSLogMsgOutPut("消息中间件已启动...");
		break;
	}
}

//析构函数
Server_VS::~Server_VS()
{	
	//socket4web->Stop();
	//socket4web = nullptr;
}

//消息中间件配置窗体
void Server_VS::ConfigWindow()
{
	
	try
	{
	

		activemq::library::ActiveMQCPP::initializeLibrary();
		g_SimpleProducer.UserName = "admin";
		g_SimpleProducer.Password = "admin";
		g_SimpleProducer.brokerURI = "tcp://117.158.216.250:61616";


		g_SimpleProducer_ZDH.UserName = "admin";
		g_SimpleProducer_ZDH.Password = "admin";
		g_SimpleProducer_ZDH.brokerURI = "tcp://117.158.216.250:61616";


		g_SimpleProducer_sh.UserName = "admin";
		g_SimpleProducer_sh.Password = "admin";
		g_SimpleProducer_sh.brokerURI = "tcp://117.158.216.250:61616";
	

		g_SimpleProducer.destURI = "DataFromFacility";
		g_SimpleProducer_ZDH.destURI= "ZDH";
		g_SimpleProducer_sh.destURI= "SH_BYD";
	

		g_SimpleProducer.start();
		g_SimpleProducer_ZDH.start();
		g_SimpleProducer_sh.start();

		/*g_SimpleProducer.start(UserName, Password, brokerURI, numMessages, destURI, useTopics, clientAck);
		g_SimpleProducer_ZDH.start(UserName, Password, brokerURI, numMessages, destURI_1, useTopics, clientAck);
		g_SimpleProducer_sh.start(UserName, Password, brokerURI, numMessages, destURI_sh, useTopics, clientAck);*/
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
		connect(socket4web, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorMSG(int)), Qt::AutoConnection);
	//	处理web端发送过来命令类型
		connect(socket4web, SIGNAL(NoticfyServerFacilityID(int, QString, QString, int, QString, QString)), this, SLOT(RequestForReadCOMM(int, QString, QString, int, QString, QString)), Qt::AutoConnection);
		socket4web->m_portServer = 1030;
		socket4web->start();
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
	EHTPool.GetEHT(ServiceTypeID)->SendCommand(Command, StationID, Params1, Params2);
	
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
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
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
		EHT *pEHT = new EHT(this);
		//数据或心跳通知
		connect(pEHT, SIGNAL(OnLineSignal(QString, QString, QDateTime, QDateTime,QString)), this, SLOT(RefreshListCtrl(QString, QString, QDateTime, QDateTime,QString)));
		//离线通知
		connect(pEHT, SIGNAL(OffLineSignal(QString, QString, QDateTime, QDateTime,QString)), this, SLOT(OffLineListCtrl(QString, QString, QDateTime, QDateTime,QString)));
		//Web端发送指令通知
		//connect(pEHT, SIGNAL(SendToWebServiceSignal(QJsonObject)), socket4web, SLOT(SendToWebServiceSlot(QJsonObject)));
		//终端返回命令通知
		connect(pEHT, SIGNAL(SendWarningInfoToUI(QString)), this, SLOT(GetWarningInfon(QString)));
		LRESULT pResult = pEHT->LoadLib(strName);
		if (pResult<1)
			return pResult;
		ui.ServerList->AddRow(pEHT->GetServiceName(), strName);
		EHTPool.Start(pEHT);
		return 1;
}

//获得错误信息
void Server_VS::GetErrorMSG(int error)
{
	QString strMSG;
	switch (error)
	{
	case 10036:
		strMSG = QString("Web监听端口异常");
		break;
	case -1:
		strMSG = QString("Web发送命令错误!");
		break;
	case -4:
		strMSG = QString("服务器间通信异常！");
		break;
	case -5:
		strMSG = QString("发送Web服务器失败！");
		break;
	case 10311:
		strMSG = QString("端口号监听失败！");
		break;
	default:
		strMSG = QString::number(error);
		break;
	}
}

//刷新设备ListCtrl控件
void Server_VS::RefreshListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime,QString DeviceID)
{
	int RowIndex = FindRowIndex(SrvName, StationID,DeviceID);
	if (RowIndex < 0)//需要添加新的一行
	{
		//更新UI
		RowIndex = ui.ClientList->rowCount();
		ui.ClientList->insertRow(RowIndex);
	}
	ui.ClientList->setItem(RowIndex, 0, new QTableWidgetItem(SrvName));
	ui.ClientList->setItem(RowIndex, 1, new QTableWidgetItem(StationID));
	ui.ClientList->setItem(RowIndex, 2, new QTableWidgetItem(DeviceID));
	ui.ClientList->setItem(RowIndex, 3, new QTableWidgetItem(LoginTime.toString("yyyy-MM-dd hh:mm:ss")));
	ui.ClientList->setItem(RowIndex, 4, new QTableWidgetItem("在线"));
	ui.ClientList->setItem(RowIndex, 5, new QTableWidgetItem(LastTime.toString("yyyy-MM-dd hh:mm:ss")));
}

//离线设备ListCtrl控件
void Server_VS::OffLineListCtrl(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime,QString DeviceID)
{
	int RowIndex = FindRowIndex(SrvName, StationID,DeviceID);
	if (RowIndex < 0)//未找到
		return;
	ui.ClientList->setItem(RowIndex, 4, new QTableWidgetItem("离线"));

}

//通过设备ip和端口查询到设备索引号
int Server_VS::FindRowIndex(QString SrvName, QString StationID,QString DeviceID)
{
	QList<QTableWidgetItem *> totalItems = ui.ClientList->findItems(SrvName, Qt::MatchFixedString);
	for (int i = 0; i < totalItems.count(); i++)
	{
		int row = totalItems[i]->row();
		if (StationID=="NULL")
		{
			QString strDeviceID = ui.ClientList->item(row, 2)->text();
			if (DeviceID.toUpper().compare(strDeviceID.toUpper()) == 0)
				return row;
		}
		if (DeviceID == "NULL")
		{
			QString strStationID = ui.ClientList->item(row, 1)->text();
			if (StationID.toUpper().compare(strStationID.toUpper()) == 0)
				return row;
		}
		if (StationID!="NULL"&&DeviceID!="NULL")
		{
			QString strStationID = ui.ClientList->item(row, 1)->text();
			if (StationID.toUpper().compare(strStationID.toUpper()) == 0)
			{
				QString strDeviceID = ui.ClientList->item(row, 2)->text();
				if (DeviceID.toUpper().compare(strDeviceID.toUpper()) == 0)
					return row;
			}
		}
	}
	return -1;
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
	connect(&action_Attributes, SIGNAL(triggered()), this, SLOT(Lib_Attri()));
	pop_Menu_Service.addAction(&action_Attributes);
	pop_Menu_Service.setStyleSheet("background:rgb(77,77,77);color:white");
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

//启动Lib服务
bool Server_VS::Lib_Run(int ServerIndex)
{
	QTableWidgetItem* SelectedItem = ui.ServerList->item(ServerIndex, 0); //获取选择行														
	if (SelectedItem == 0)
		return false;
	int Row = SelectedItem->row();
	bool b= EHTPool.Run(ui.ServerList->item(Row, 0)->text());
	if (!b)
		QMessageBox::warning(this, "警告", "端口号被其他程序占用！");
	return b;
}

//停止Lib服务
bool Server_VS::Lib_Stop(int ServerIndex)
{
	QTableWidgetItem* SelectedItem = ui.ServerList->item(ServerIndex, 0); //获取选择行														
	if (SelectedItem == 0)
		return false;
	int Row = SelectedItem->row();
	return EHTPool.Pause(ui.ServerList->item(Row, 0)->text());
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
	connect(&dmtddlg, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorMSG(int)));
	dmtddlg.exec();

}

//打开系统运行日志
void Server_VS::OpenSYSLog()
{
	SYSLogDlg syslogdlg("SYSLog");
	syslogdlg.exec();
}

//查看数据运行日志
void Server_VS::OpenDataLog()
{
	SYSLogDlg datalogdlg("DataLog");
	datalogdlg.exec();
}
int nCount = 0;
//命令控制窗体
void Server_VS::OpenControlDlg()
{	//nCount++;
//	QJsonObject json;
//	json.insert("Count", nCount);
//	socket4web->SendToWebServiceSlot(json);
//
	if (iSelectedRowOfClientListCtrl<0 || iSelectedRowOfClientListCtrl>ui.ClientList->rowCount() - 1)
		return;

		QString ServiceName = ui.ClientList->item(iSelectedRowOfClientListCtrl, 0)->text();
		QString StationID = ui.ClientList->item(iSelectedRowOfClientListCtrl, 1)->text();
		QString DeviceID = ui.ClientList->item(iSelectedRowOfClientListCtrl,2)->text();
		int SeverID = EHTPool.GetEHT(ServiceName)->GetServiceID();
		EHTPool.GetEHT(ServiceName)->OpenCtrlWnd(StationID,DeviceID);
}

//打开报警停靠窗口
void Server_VS:: ShowWarningDockWidget()
{	
	//读取WaningLog文件中报警信息
	LoadWarningInfo();
	ui.WarningDockWidget->show();
	ui.groupBox_SrvGB->setGeometry(QRect(940, 2, 75, 26));
}

//加载报警信息
void Server_VS::LoadWarningInfo()
{
	QString path = QCoreApplication::applicationDirPath() + "\\Log\\WarningLog.txt";
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	QString line = in.readLine();
	WarningInfoList.append(line);
	//读取数据
	while (!line.isNull())
	{
		line = in.readLine();
		WarningInfoList.append(line);
	}
	file.close();
	slModel->setStringList(WarningInfoList);
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

//获取终端命令名称
void Server_VS::GetCommName(QString CommName)
{
	strOperateType = CommName;
}

//业务列表点击
void Server_VS::on_ServerList_itemClicked(QTableWidgetItem *item)
{
	iSelectedRowOfServiceListCtrl = item->row();
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 0)->text();
	int Count=EHTPool.GetEHT(ServiceName)->GetOnlineCount();
	ui.OnLineCountLabel->setText("当前在线设备个数: "+ QString::number(Count));
}

//设备列表点击
void Server_VS::on_ClientList_itemClicked(QTableWidgetItem *item)
{
	iSelectedRowOfClientListCtrl = item->row();
}

//业务列表改变
void Server_VS::ServerList_currentItemChanged(QTableWidgetItem * current, QTableWidgetItem * previous)
{
	if (current == NULL)
		return;
	iSelectedRowOfServiceListCtrl = current->row();
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 0)->text();
	int Count = EHTPool.GetEHT(ServiceName)->GetOnlineCount();
	ui.OnLineCountLabel->setText("当前在线设备个数: " + QString::number(Count));
}

//设备列表改变
void Server_VS::ClientList_cuurentItemChanged(QTableWidgetItem * current, QTableWidgetItem * previous)
{
	if (current == NULL)
		return;
	iSelectedRowOfClientListCtrl = current->row();
}
void Server_VS::MQConfig()
{
	MQConfigDlg *mq = new MQConfigDlg();
	mq->show();
}
//Docking配置方法
static
Qt::ToolBarArea dockAreaToToolBarArea(Qt::DockWidgetArea area)
{
	switch (area)
	{
	case Qt::LeftDockWidgetArea: return Qt::LeftToolBarArea;
	case Qt::RightDockWidgetArea: return Qt::RightToolBarArea;
	case Qt::TopDockWidgetArea: return Qt::TopToolBarArea;
	case Qt::BottomDockWidgetArea: return Qt::BottomToolBarArea;
	default:
		return Qt::ToolBarArea(0);
	}
}

void Server_VS::createDockWidgetBar(Qt::DockWidgetArea area)
{
	if (m_dockWidgetBar.find(area) != std::end(m_dockWidgetBar)) {
		return;
	}

	MyDockWidgetTabBar* dockWidgetBar = new MyDockWidgetTabBar(area);
	m_dockWidgetBar[area] = dockWidgetBar;
	connect(dockWidgetBar, &MyDockWidgetTabBar::signal_dockWidgetButton_clicked, this, &Server_VS::showDockWidget);

	addToolBar(dockAreaToToolBarArea(area), dockWidgetBar);
}

void Server_VS::dockWidgetUnpinned(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	MyDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
	if (dockWidgetBar == nullptr) {
		return;
	}

	QList<QDockWidget*> dockWidgetList = tabifiedDockWidgets(dockWidget);
	dockWidgetList.push_back(dockWidget);

	std::for_each(std::begin(dockWidgetList), std::end(dockWidgetList), [&](QDockWidget* qDockWidget)
	{
		MyDockWidget* dockWidget = static_cast<MyDockWidget*>(qDockWidget);

		dockWidget->setState(DockWidgetState::Hidden);

		if (!dockWidget->isHidden())
		{
			dockWidgetBar->addDockWidget(dockWidget);

			dockWidget->setTabifiedDocks(dockWidgetList);

			QMainWindow::removeDockWidget(dockWidget);
		}
	});

	if (dockWidget->getArea() == Qt::LeftDockWidgetArea)
	{
		getDockWidgetBar(Qt::TopDockWidgetArea)->insertSpacing();
		getDockWidgetBar(Qt::BottomDockWidgetArea)->insertSpacing();
	}
	if (dockWidget->getArea() == Qt::RightDockWidgetArea)
	{
		getDockWidgetBar(Qt::TopDockWidgetArea)->insertSpacing();
		getDockWidgetBar(Qt::BottomDockWidgetArea)->insertSpacing();
		ui.groupBox_SrvGB->setGeometry(QRect(1175, 2, 75, 26));
	}
}

void Server_VS::dockWidgetPinned(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	MyDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
	if (dockWidgetBar == nullptr) {
		return;
	}

	m_dockWidget = nullptr;

	std::vector<MyDockWidget*> dockWidgetList = dockWidget->getTabifiedDocks();
	dockWidgetList.push_back(dockWidget);

	MyDockWidget* prevDockWidget = nullptr;

	std::for_each(std::begin(dockWidgetList), std::end(dockWidgetList), [&](MyDockWidget* dockWidget)
	{
		if (dockWidgetBar->removeDockWidget(dockWidget))
		{
			if (prevDockWidget == nullptr) {
				QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
			}
			else {
				tabifyDockWidget(prevDockWidget, dockWidget);
			}

			prevDockWidget = dockWidget;

			dockWidget->setState(DockWidgetState::Docked);

			dockWidget->show();
		}
	});

	dockWidget->raise();

	if ((dockWidget->getArea() == Qt::LeftDockWidgetArea) &&
		dockWidgetBar->isHidden())
	{
		getDockWidgetBar(Qt::TopDockWidgetArea)->removeSpacing();
		getDockWidgetBar(Qt::BottomDockWidgetArea)->removeSpacing();
	}
	if((dockWidget->getArea() == Qt::RightDockWidgetArea) &&
		dockWidgetBar->isHidden())
	{
		ui.groupBox_SrvGB->setGeometry(QRect(935, 2, 75, 26));
	}
	
}

void Server_VS::showDockWidget(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	if (dockWidget->isHidden())
	{
		hideDockWidget(m_dockWidget);

		if (dockWidget->isFloating())
		{
			QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
			dockWidget->setFloating(false);

			QMainWindow::removeDockWidget(dockWidget);
		}

		adjustDockWidget(dockWidget);
		//读取WaningLog文件中报警信息
		LoadWarningInfo();
		dockWidget->show();
		dockWidget->raise();

		dockWidget->setFocus();

		m_dockWidget = dockWidget;
		ui.groupBox_SrvGB->setGeometry(QRect(915, 2, 75, 26));
	}
	else
	{
		hideDockWidget(dockWidget);
		ui.groupBox_SrvGB->setGeometry(QRect(1170, 2, 75, 26));
	}
}

bool Server_VS::event(QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		hideDockWidget(m_dockWidget);
	}

	// Make sure the rest of events are handled
	return QMainWindow::event(event);
}

void Server_VS::adjustDockWidget(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	QRect rect = getDockWidgetsAreaRect();
	switch (dockWidget->getArea())
	{
	case Qt::LeftDockWidgetArea: {
		dockWidget->setGeometry(rect.left(), rect.top(), dockWidget->width(), rect.height());
	}
								 break;

	case Qt::TopDockWidgetArea: {
		dockWidget->setGeometry(rect.left(), rect.top(), rect.width(), dockWidget->height());
	}
								break;

	case Qt::RightDockWidgetArea: {
		ui.groupBox_SrvGB->setGeometry(QRect(915, 2, 75, 26));
		dockWidget->setGeometry(rect.left() + rect.width() - dockWidget->width(), rect.top(), dockWidget->width(), rect.height());
	}
								  break;

	case Qt::BottomDockWidgetArea: {
		dockWidget->setGeometry(rect.left(), rect.top() + rect.height() - dockWidget->height(), rect.width(), dockWidget->height());
	}
								   break;
	}
}

MyDockWidgetTabBar* Server_VS::getDockWidgetBar(Qt::DockWidgetArea area)
{
	assert(m_dockWidgetBar.find(area) != std::end(m_dockWidgetBar));

	auto it = m_dockWidgetBar.find(area);
	if (it != std::end(m_dockWidgetBar)) {
		return it->second;
	}

	return nullptr;
}

void Server_VS::addDockWidget(Qt::DockWidgetArea area, MyDockWidget* dockWidget)
{
	addDockWidget(area, dockWidget, Qt::Vertical);
}

void Server_VS::addDockWidget(Qt::DockWidgetArea area, MyDockWidget* dockWidget, Qt::Orientation orientation)
{
	if (dockWidget == nullptr) {
		return;
	}

	connect(dockWidget, &MyDockWidget::signal_pinned, this, &Server_VS::dockWidgetPinned);
	connect(dockWidget, &MyDockWidget::signal_unpinned, this, &Server_VS::dockWidgetUnpinned);
	connect(dockWidget, &MyDockWidget::signal_docked, this, &Server_VS::dockWidgetDocked);
	connect(dockWidget, &MyDockWidget::signal_undocked, this, &Server_VS::dockWidgetUndocked);
	connect(dockWidget, &MyDockWidget::signal_close, this, &Server_VS::dockWidgetClose);
	m_dockWidgets.push_back(dockWidget);

	QMainWindow::addDockWidget(area, dockWidget, orientation);

	QString title = dockWidget->windowTitle();
	if (title.isEmpty()) {
		title = QObject::tr("Noname");
	}
}

void Server_VS::removeDockWidget(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	auto it = std::find(m_dockWidgets.begin(), m_dockWidgets.end(), dockWidget);
	if (it == m_dockWidgets.end()) {
		return;
	}

	m_dockWidgets.erase(it);

	if (dockWidget->isMinimized()) {
		dockWidgetPinned(dockWidget);
	}

	QMainWindow::removeDockWidget(dockWidget);

	dockWidget->setParent(nullptr);
}

void Server_VS::dockWidgetDocked(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}
}

void Server_VS::dockWidgetClose(MyDockWidget* dockWidget)
{
    ui.groupBox_SrvGB->setGeometry(QRect(1200, 2, 75, 26));
}

void Server_VS::dockWidgetUndocked(MyDockWidget* dockWidget)
{
	hideDockWidget(m_dockWidget);

	MyDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
	if (dockWidgetBar == nullptr) {
		return;
	}

	dockWidget->clearTabifiedDocks();

	if (dockWidgetBar->removeDockWidget(dockWidget))
	{
		if (!dockWidget->isFloating()) {
			QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
		}

		if ((dockWidget->getArea() == Qt::LeftDockWidgetArea) &&
			dockWidgetBar->isHidden())
		{
			getDockWidgetBar(Qt::TopDockWidgetArea)->removeSpacing();
			getDockWidgetBar(Qt::BottomDockWidgetArea)->removeSpacing();
		}

		dockWidget->show();
	}
}

std::list<MyDockWidget*> Server_VS::getDockWidgetListAtArea(Qt::DockWidgetArea area)
{
	std::list<MyDockWidget*> dockWidgetList;
	std::copy_if(std::begin(m_dockWidgets), std::end(m_dockWidgets), std::back_inserter(dockWidgetList), [area](const MyDockWidget* dockWidget) {
		return (dockWidget->getArea() == area) && (dockWidget->isDocked());
	});

	return dockWidgetList;
}

QRect Server_VS::getDockWidgetsAreaRect()
{
	int left = centralWidget()->x();
	std::list<MyDockWidget*> leftAreaDockWidgets = getDockWidgetListAtArea(Qt::LeftDockWidgetArea);
	std::for_each(std::begin(leftAreaDockWidgets), std::end(leftAreaDockWidgets), [&left](const MyDockWidget* dockWidget)
	{
		if ((dockWidget->x() >= 0) && (dockWidget->width() > 0)) {
			left = std::min(left, dockWidget->x());
		}
	});

	int top = centralWidget()->y();
	std::list<MyDockWidget*> topAreaDockWidgets = getDockWidgetListAtArea(Qt::TopDockWidgetArea);
	std::for_each(std::begin(topAreaDockWidgets), std::end(topAreaDockWidgets), [&top](const MyDockWidget* dockWidget)
	{
		if ((dockWidget->y() >= 0) && (dockWidget->height() > 0)) {
			top = std::min(top, dockWidget->y());
		}
	});

	int right = centralWidget()->x() + centralWidget()->width();
	std::list<MyDockWidget*> rightAreaDockWidgets = getDockWidgetListAtArea(Qt::RightDockWidgetArea);
	std::for_each(std::begin(rightAreaDockWidgets), std::end(rightAreaDockWidgets), [&right](const MyDockWidget* dockWidget)
	{
		if ((dockWidget->x() >= 0) && (dockWidget->width() > 0)) {
			right = std::max(right, dockWidget->x() + dockWidget->width());
		}
	});

	int bottom = centralWidget()->y() + centralWidget()->height();
	std::list<MyDockWidget*> bottomAreaDockWidgets = getDockWidgetListAtArea(Qt::BottomDockWidgetArea);
	std::for_each(std::begin(bottomAreaDockWidgets), std::end(bottomAreaDockWidgets), [&bottom](const MyDockWidget* dockWidget)
	{
		if ((dockWidget->y() >= 0) && (dockWidget->height() > 0)) {
			bottom = std::max(bottom, dockWidget->y() + dockWidget->height());
		}
	});

	return QRect(left, top, right - left, bottom - top);
}

void Server_VS::hideDockWidget(MyDockWidget* dockWidget)
{
	if ((dockWidget == nullptr) || (dockWidget->isHidden())) {
		return;
	}

	m_dockWidget = nullptr;
	WarningInfoList.clear();
	dockWidget->hide();
}

void Server_VS::menuWindows_triggered(QAction* action)
{
	auto it = std::find_if(m_dockWidgets.begin(), m_dockWidgets.end(), [&](MyDockWidget* dockWidget) {
		return (dockWidget->getMenuAction() == action);
	});
	if (it == m_dockWidgets.end()) {
		return;
	}

	MyDockWidget* dockWidget = *it;
	if (dockWidget->isHidden())
	{
		hideDockWidget(m_dockWidget);

		dockWidget->show();
		dockWidget->raise();

		// dockWidget->setState(DockWidgetState::Docked);
	}
	else if (dockWidget->isMinimized())
	{
		showDockWidget(dockWidget);
	}

	dockWidget->setFocus();
}

