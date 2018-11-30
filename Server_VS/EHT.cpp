#include "EHT.h"
#include "ConfigWnd.h"
#include"LogWrite.h"
#include<QSettings>
#include<QDir>
#include<QtXml>
EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//初始化IOCP
	InitIOCP();
	b_IsReconnect = false;//MQ重连状态
	IsExistImage = false;
	IsExistTXT = false;
	//读取SIM卡号配置文件，转成区站号
	Convert2StationID();
	m_IsRun = false;
	b_IsRunMQ = false;
	SetTimeTimer = new QTimer(parent);
	connect(SetTimeTimer, SIGNAL(timeout()), this, SLOT(SetTime()));
	SetTimeTimer->start(1000 * 60 * 60*24 );

	OffLineTimer = new QTimer(parent);
	connect(OffLineTimer, SIGNAL(timeout()), this, SLOT(Disconnect()));
	OffLineTimer->start(1000 * 60 * 20);
	//消息中间件重连时间
	ReconnectTimer = new QTimer(parent);
	ReconnectTimer->
	connect(ReconnectTimer, SIGNAL(timeout()), this, SLOT(Reconnect()));
	//Image图片重新处理时间
	ReHandleZB_IMAGE = new QTimer(parent);
	ReHandleZB_IMAGE->connect(ReHandleZB_IMAGE, SIGNAL(timeout()), this, SLOT(MoveImageToDesAddr()));
	//XML文件处理时间
	ReHandleZB_XML = new QTimer(parent);
	ReHandleZB_XML->connect(ReHandleZB_XML, SIGNAL(timeout()), this, SLOT(MoveXMLToDesAddr()));
	ReHandleZB_XML->start(1000 * 60 * 10);
	//TXT文件重新处理时间
	ReHandleZB_TXT = new QTimer(parent);
	ReHandleZB_TXT->connect(ReHandleZB_TXT, SIGNAL(timeout()), this, SLOT(MoveTXTToDesAddr()));
}
EHT::EHT()
{

}
EHT::~EHT()
{
}
//加载动态链接库
LRESULT EHT::LoadLib(QString Lib_Path)
{
	m_Lib.setFileName(Lib_Path);
	//(strName);
	//读取成功
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//获取业务名称
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("GetPort");//获取端口号
		GetVersionNo_Lib func_GetVersionNo = (GetVersionNo_Lib)m_Lib.resolve("GetVersionNo");//获取版本号
		Char2Json func_Char2Json = (Char2Json)(m_Lib.resolve("Char2Json"));//获取解析数据
		func_SetTime_Lib = (SetTime_Lib)(m_Lib.resolve("SetTime"));
		func_GetControlWidget = (GetControlWidget_Lib)(m_Lib.resolve("GetControlWidget"));
		func_SetValueToControlWidget = (SetValueToControlWidget_Lib)(m_Lib.resolve("SetValueToControlWidget"));
		func_SetCommand = (SetCommand_Lib)(m_Lib.resolve("SetCommand"));
		if (!(func_GetServiceTypeID && func_GetServiceTypeName && func_GetVersionNo && 
			func_GetPort&&func_Char2Json&&func_SetTime_Lib&&func_GetControlWidget&&func_SetCommand&&func_SetValueToControlWidget))
		{
			UnloadLib();
			return -1;
		}
			

		//获取业务类型
		m_ServiceID = func_GetServiceTypeID();
		//获取端口号
		m_Port = func_GetPort();
		//获取业务名称
		m_ServiceName = func_GetServiceTypeName();
		//获取版本号
		m_Vesion = func_GetVersionNo();
		//开启IP和端口设置窗体
		ConfigWnd CfgWnd;
		CfgWnd.DialogMode = true;//设置 false为读取
		CfgWnd.SetServicePort(m_Port);
		int r = CfgWnd.exec();
		if (r != QDialog::Accepted)
		{
			UnloadLib();
			return 0;
		}

		
		//获取IP
		m_IP = CfgWnd.m_IP;
		//判断端口合法性
		if (!IsLegallyPort(CfgWnd.m_Port))
		{
			UnloadLib();
			return -2;
		}
		//获取IP
		m_Port = CfgWnd.m_Port;
		//获取描述
		m_Attribute = CfgWnd.m_Attribute;
		return true;
	}
	else
	{
		UnloadLib();
		return false;
	}
}
//卸载动态链接库
bool EHT::UnloadLib()
{
	return	m_Lib.unload();
}
//获取版本号
QString EHT::GetVesionNo()
{
	return m_Vesion;
}
//获取业务ID
int EHT::GetServiceID()
{
	return m_ServiceID;
}
//获取业务名称
QString EHT::GetServiceName()
{
	return m_ServiceName;
}
//获取IP号
QString EHT::GetIP()
{
	return m_IP;
}
//获取端口号
int EHT::GetPort()
{
	return m_Port;
}
//获取Socket号
unsigned int EHT::GetSocket(QString StationID)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].StationID==StationID)
			return Clients[i].SocketID;
	}
	return 0;
}

//获取业务描述
QString EHT::GetAttribute()
{
	return m_Attribute;
}
//获取数据解析
Char2Json EHT::GetDataFunc()
{
	return m_DataFunc;
}
//启动监听数据服务
bool EHT::Run(QThreadPool &ThreadPool)
{
	if (pIOCP == NULL)
	{
		if (!IsLegallyPort(m_Port))
		{
			UnloadLib();
			return false;
		}
		InitIOCP();
	}
	
	pIOCP->func_Char2Json = (Char2Json)m_Lib.resolve("Char2Json");
	m_DataFunc= (Char2Json)m_Lib.resolve("Char2Json");
	pIOCP->SetListenedPort(m_Port, m_IP,m_ServiceID);
	ThreadPool.start(pIOCP);
	m_IsRun = true;
	return true;
}

//结束监听数据服务
bool EHT::Stop()
{
	if (pIOCP == nullptr)
	{
		UnloadLib();
		return true;
	}
	//关闭IOCP
	pIOCP->Stop();
	UnloadLib();
	m_IsRun = false;
	pIOCP = nullptr;
	return true;
}
//初始化IOCP
void EHT::InitIOCP()
{
	//IOCP子线程
	pIOCP = new IOCP();
	//设备离线通知
	connect(pIOCP, SIGNAL(OffLineSignal(unsigned int)), this, SLOT(OffLineSlot(unsigned int)), Qt::QueuedConnection);
	//设备数据错误通知
	connect(pIOCP, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorSlot(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(pIOCP, SIGNAL(NewDataSignal(QString, QString,int, unsigned int,QString)), this, SLOT(NewDataSlot(QString ,QString ,int, unsigned int,QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(NewDataSignal(QString, QString, int, int,unsigned int,QString)), this, SLOT(NewDataSlot(QString, QString, int, int, unsigned int,QString)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, int, QString, QString)), this, SLOT(OperationResultSlot(QString, int, QString, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, int, QString, QString)), this, SLOT(OperationResultSlot(QString,QString, int, QString, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, QString, QString, QString, int, QString, QString)), this, SLOT(OperationResultSlot(QString, QString, QString, QString, QString, int, QString, QString)),Qt::QueuedConnection);
 
}
//返回运行状态
bool EHT::IsRun()
{
	return m_IsRun;
}
//判断端口合法性
bool EHT::IsLegallyPort(int port)
{
	//初始化WSA    加载socket动态链接库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // 接收Windows Socket的结构信息
	if (WSAStartup(sockVersion, &wsaData) != 0)
		return false;
	
	SOCKET BindSocket;
	BindSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN  srvAddr;
	//获取本地IP
	LPCSTR  ch;
	QByteArray ba = m_IP.toLatin1();
	ch = ba.data();
	srvAddr.sin_addr.S_un.S_addr = inet_addr(ch);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(port);
	//绑定SOCKET到本机
	int bindResult = ::bind(BindSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == bindResult)
		return false;
	closesocket(BindSocket);
	return true;
}

//离线处理
void EHT::OffLineSlot(unsigned int CltSocket)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//找到离线
		if (Clients[i].SocketID == CltSocket)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("区站号 ") + Clients[i].StationID + QString::fromLocal8Bit("，设备号 ") + Clients[i].DeviceID + QString::fromLocal8Bit("已经断开连接"));
			Clients[i].SocketID = 0;//Socket置零
			Clients[i].Online = false;//设置离线状态

			QJsonObject HBJson;
			HBJson.insert("DeviceID", Clients[i].DeviceID);
			HBJson.insert("StationID", Clients[i].StationID);
			HBJson.insert("ServiceTypeID", QString::number(m_ServiceID));
			HBJson.insert("HBTime", current_date);
			HBJson.insert("OnLineStatus", false);
			QJsonDocument document;
			document.setObject(HBJson);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);
			LPCSTR dataChar;
			dataChar = byteArray.data();
			//发送至消息中间件
			if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
				GetErrorSlot(10304);
			
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, current_date_time, Clients[i].LoginTime,Clients[i].DeviceID);
			break;
		}
	}
}

//有数据传输
void EHT::NewDataSlot(QString StationID, QString IP, int Port, unsigned int CltSocket,QString DeviceID)
{
	//台站号为空
	if (StationID == NULL&&DeviceID==NULL)
		return;
	//农委站号转变
	if (m_ServiceID == NW)
	{
		if (SIM2Staion.contains(StationID))
		{
			//找到特定的“键-值”对
			QMap<QString, QString>::iterator it = SIM2Staion.find(StationID);
			StationID = it.value();
		}
	}
	QDateTime current_date_time = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.count(); i++)
	{
		//存在
		if (Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper()) == 0 && Clients[i].StationID.toUpper().compare(StationID.toUpper()) == 0)
		{
			//在线提示
			if (Clients[i].Online==false)
			{
				QJsonObject HBJson;
				HBJson.insert("DeviceID", Clients[i].DeviceID);
				HBJson.insert("StationID", Clients[i].StationID);
				HBJson.insert("ServiceTypeID", QString::number(m_ServiceID));
				HBJson.insert("HBTime", current_date_time.toString("yyyy-MM-dd hh:mm:ss"));
				HBJson.insert("OnLineStatus", true);
				QJsonDocument document;
				document.setObject(HBJson);
				QByteArray byteArray = document.toJson(QJsonDocument::Compact);
				LPCSTR dataChar;
				dataChar = byteArray.data();
				//发送至消息中间件
				if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
					GetErrorSlot(10304);
			}
			Clients[i].LatestTimeOfHeartBeat = current_date_time;//更新时间
			Clients[i].SocketID = CltSocket;//更新Socket号
			Clients[i].IP = IP;//更新IP
			Clients[i].Port = Port;//更新端口
			Clients[i].Online = true;//设置在线
			emit OnLineSignal(m_ServiceName, Clients[i].StationID,Clients[i].LatestTimeOfHeartBeat,Clients[i].LoginTime,Clients[i].DeviceID);//刷新UI
			return;
		}
	}
	//不存在插入
	CLIENTINFO clientinfo{ IP, Port,CltSocket,StationID,DeviceID,current_date_time,true,current_date_time };
	Clients.push_back(clientinfo);
	//在线提示
	QJsonObject HBJson;
	HBJson.insert("DeviceID",DeviceID);
	HBJson.insert("StationID",StationID);
	HBJson.insert("ServiceTypeID", QString::number(m_ServiceID));
	HBJson.insert("HBTime", current_date_time.toString("yyyy-MM-dd hh:mm:ss"));
	HBJson.insert("OnLineStatus", true);
	QJsonDocument document;
	document.setObject(HBJson);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	LPCSTR dataChar;
	dataChar = byteArray.data();
	//发送至消息中间件
	if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
		GetErrorSlot(10304);
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("新设备已连接，台站号为：") + clientinfo.StationID+QString::fromLocal8Bit("，设备号为：")+ clientinfo.DeviceID);
	emit  OnLineSignal(m_ServiceName, StationID,clientinfo.LatestTimeOfHeartBeat,clientinfo.LoginTime, clientinfo.DeviceID);;//刷新UI
}

//有数据传输植被
void EHT::NewDataSlot(QString StationID, QString IP, int Port, int File, unsigned int CltSocket,QString DeviceID)
{

	//台站号为空
	if (StationID == NULL)
		return;
	//农委站号转变
	if (m_ServiceID == NW)
	{
		if (SIM2Staion.contains(StationID))
		{
			//找到特定的“键-值”对
			QMap<QString, QString>::iterator it = SIM2Staion.find(StationID);
			StationID = it.value();
		}
	}
	switch (File)
	{
	case IMAGE:
	{
		IsExistImage = false;
		ReHandleZB_IMAGE->start(1000 * 10);
	}
	break;
	case TXT:
	{
		IsExistTXT= false;
		ReHandleZB_TXT->start(1000* 10);
	}
		break;
	default:
		break;
	}
	QDateTime current_date_time = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.count(); i++)
	{
		//存在
		if (Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper()) == 0 && Clients[i].StationID.toUpper().compare(StationID.toUpper()) == 0)
		{
			Clients[i].LatestTimeOfHeartBeat = current_date_time;//更新时间
			Clients[i].SocketID = CltSocket;//更新Socket号
			Clients[i].IP = IP;//更新IP
			Clients[i].Port = Port;//更新端口
			Clients[i].Online = true;//设置在线
			emit OnLineSignal(m_ServiceName, StationID, Clients[i].LatestTimeOfHeartBeat, Clients[i].LoginTime, Clients[i].DeviceID);//刷新UI
			return;
		}
	}
	//不存在插入
	CLIENTINFO clientinfo{ IP, Port,CltSocket,StationID,DeviceID,current_date_time,true,current_date_time };
	Clients.push_back(clientinfo);
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("新设备已连接，台站号为：") + clientinfo.StationID);
	emit  OnLineSignal(m_ServiceName, StationID, clientinfo.LatestTimeOfHeartBeat, clientinfo.LoginTime,clientinfo.DeviceID);;//刷新UI
}

//图片处理
void EHT::MoveImageToDesAddr()
{
	if (IsExistImage)
		ReHandleZB_IMAGE->stop();
	
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.jpeg") << QString("*.jpg") << QString("*.png") << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是图片
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		int sizeOfImg = fileInfo->at(i).size();
		//获取图片名称
		QStringList namestrlit = name.split(".");
		if (namestrlit.count() < 1)
			continue;
		QStringList strName = name.split("_");
		if (strName.count() != 4)
			continue;
		QStringList strDll = strName.at(3).split(".");
		QString DeviceID = strDll.at(0);
		QString OBcurrent_date = strName.at(2);
		QString StationID = strName.at(0);

		QDateTime current_date_time = QDateTime::fromString("yyyyMMddhhmmss");
		QString yy = current_date_time.toString("yyyy");
		QString mm = current_date_time.toString("MM");
		QString dd = current_date_time.toString("dd");

		//生成原始图和缩略图
		QString DesFile_Image = "D://Tomcat 8.0//webapps//byd//upload//yszb//" + yy+"//"+mm+"//"+dd;//原始图
		QString DesFile_MinImage = "D://Tomcat 8.0//webapps//byd//upload//slzb//" +yy + "//" + mm + "//" + dd;//缩略图
		QDir dir(DesFile_Image);
		if (!dir.exists())
			dir.mkpath(DesFile_Image);//创建多级目录
		QDir dir_mi(DesFile_MinImage);
		if (!dir_mi.exists())
			dir_mi.mkpath(DesFile_MinImage);//创建多级目录
		DesFile_Image += "//" + name;
		DesFile_MinImage += "//" + name;
		QImage minImage;
		minImage.load(path);
		minImage = minImage.scaled(300, 200, Qt::KeepAspectRatio);
		minImage.save(DesFile_MinImage, "JPG");
		//XML文件处理
		QJsonObject Json;
	
		//原图名称
		Json.insert("ImageName",name);
		//原图路径
		Json.insert("ImagePath","//byd//upload//yszb//" + yy + "//" + mm + "//" + dd +"//" + name);
		//缩略图路径
		Json.insert("MinImgPath", "//byd//upload//slzb//" + yy + "//" + mm + "//" + dd + "//" + name);
		//设备ID
		Json.insert("DeviceID", DeviceID);
		//设备是否含有区站号
		Json.insert("ContainSID", false);
		Json.insert("StationID", DeviceID);
		//观测时间
		Json.insert("ObserveTime", OBcurrent_date);
		//业务号
		Json.insert("ServiceTypeID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
			GetErrorSlot(10304);
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_Image);
		QFile::remove(path);
		IsExistImage = true;
	}
}

//文本处理
void EHT::MoveTXTToDesAddr()
{
	if (IsExistTXT)
		ReHandleZB_TXT->stop();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是TXT
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QString DesFile_TXT = "D://SH_ZB_TXT//" + current_date;//目的路径
		QDir dir(DesFile_TXT);
		if (!dir.exists())
			dir.mkpath(DesFile_TXT);//创建多级目录
		DesFile_TXT += "\\" + name;
		
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_TXT);
		QFile::remove(path);
		IsExistTXT = true;
	}
}

//XML处理
void EHT::MoveXMLToDesAddr()
{
	QJsonObject Json;
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.xml");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是XML
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QStringList strName = name.split("_");
		if (strName.count() != 4)
			continue;
		QStringList strDll = strName.at(3).split(".");
		QString DeviceID = strDll.at(0);
		QString OBcurrent_date = strName.at(2);
		QString StationID = strName.at(0);

		QString DesFile_XML = "D://SH_ZB_XML//" + current_date;//目的路径
		QDir dir(DesFile_XML);
		if (!dir.exists())
			dir.mkpath(DesFile_XML);//创建多级目录
		DesFile_XML += "\\" + name;
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_XML);
	    QFile::remove(path);
		//解析文件
		QFile file(DesFile_XML); //相对路径、绝对路径、资源路径都行
		if (!file.open(QFile::ReadOnly))
			return;

		QDomDocument doc;
		if (!doc.setContent(&file))
		{
			file.close();
			return;
		}
		file.close();
	
		QDomElement root = doc.documentElement(); //返回根节点
		QDomNode node = root.firstChildElement("currentCoverage");
		Json.insert("Coverage", node.toElement().text());
		node = root.firstChildElement("density");
		Json.insert("Density", node.toElement().text());
		node = root.firstChildElement("height");
		Json.insert("CanopyHeight", node.toElement().text());
		//设备ID
		Json.insert("DeviceID", DeviceID);
		//设备是否含有区站号
		Json.insert("ContainSID", false);
		Json.insert("StationID", DeviceID);
		//观测时间
		Json.insert("ObserveTime", OBcurrent_date);
		//业务号
		Json.insert("ServiceTypeID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
			GetErrorSlot(10304);
	}
}

//终端命令操作
void EHT:: OperationResultSlot(QString Value, int SrvPort, QString StationID, QString DeviceID)
{
	QStringList ValueList;
	ValueList.append(Value);
	for (int i = 0; i < Clients.count(); i++)
	{
		if(Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper())==0&& Clients[i].StationID.toUpper().compare(StationID.toUpper())==0)
		func_SetValueToControlWidget(ValueList);
	}
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value + QString::fromLocal8Bit(",信息来自业务号：")+m_ServiceName+ QString::fromLocal8Bit(",台站号：")+StationID+QString::fromLocal8Bit(",设备号：")+DeviceID;

	QJsonObject json;
	json.insert("StationID", StationID);
	json.insert("ServiceTypeID", QString::number(m_ServiceID));
	json.insert("Count", 1);
	json.insert("RecvValue1", Value);
	json.insert("DeviceID", DeviceID);
	//发送至Web服务器
	emit SendToWebServiceSignal(json);

	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}
void EHT:: OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID, QString DeviceID)
{
	QStringList ValueList;
	ValueList.append(Value1);
	ValueList.append(Value2);
	for (int i = 0; i < Clients.count(); i++)
	{
		if (Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper()) == 0 && Clients[i].StationID.toUpper().compare(StationID.toUpper())==0)
			func_SetValueToControlWidget(ValueList);
	}
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value1+ QString::fromLocal8Bit("，返回值：")+Value2 + QString::fromLocal8Bit(",信息来自业务号：") + m_ServiceName + QString::fromLocal8Bit(",台站号：") + StationID + QString::fromLocal8Bit(",设备号：") + DeviceID;
		QJsonObject json;
		json.insert("StationID", StationID);
		json.insert("ServiceTypeID",QString::number(m_ServiceID));
		json.insert("DeviceID", DeviceID);
		json.insert("Count", 2);
		json.insert("RecvValue1", Value1);
		json.insert("RecvValue2", Value2);
		//发送至Web服务器
		emit SendToWebServiceSignal(json);
	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}
void EHT:: OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID, QString DeviceID)
{
	QStringList ValueList;
	if (!(Value1 == "NULL" || Value1.toUpper() == "N"))
		ValueList.append(Value1);
	if (!(Value2 == "NULL" || Value2.toUpper() == "N"))
		ValueList.append(Value2);

	for (int i = 0; i < Clients.count(); i++)
	{
		if (Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper()) == 0 && Clients[i].StationID.toUpper().compare(StationID.toUpper())==0)
			func_SetValueToControlWidget(ValueList);
	}
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value1 + QString::fromLocal8Bit("，返回值：") + Value2 + QString::fromLocal8Bit(",返回值：")+Value3+ QString::fromLocal8Bit("，返回值:")+Value4+ QString::fromLocal8Bit(",信息来自业务号：") + m_ServiceName + QString::fromLocal8Bit(",台站号：") + StationID + QString::fromLocal8Bit(",设备号：") + DeviceID;

		QJsonObject json;
		json.insert("StationID", StationID);
		json.insert("ServiceTypeID", QString::number(m_ServiceID));
		json.insert("Count", 2);
		json.insert("DeviceID", DeviceID);
		json.insert("RecvValue1", Value1);
		json.insert("RecvValue2", Value2);
		//发送至Web服务器
		emit SendToWebServiceSignal(json);
	
	//emit SendToUI(OperationLog);
	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}

//获取错误
void EHT:: GetErrorSlot(int ErrorMSG)
{
	QString strMSG;
	switch (ErrorMSG)
	{
	case 1:
		strMSG = QString::fromLocal8Bit("正常");
		break;
	case 10300: case 10301: case 10302:
		strMSG = QString::fromLocal8Bit("通信初始化失败！");
		break;
	case 10304:
		strMSG = QString::fromLocal8Bit("消息中间件通信异常！");
		ReConnectActiveMq();
		break;
	case 10305:
		strMSG = QString::fromLocal8Bit("接收内存溢出");
		break;
	case 10036:
		strMSG = QString::fromLocal8Bit("Web监听端口异常");
		break;
	case -4:
		strMSG = QString::fromLocal8Bit("服务器间通信异常！");
		break;
	case -5:
		strMSG = QString::fromLocal8Bit("设备已登出！");
		break;
	case 10311:
		strMSG = QString::fromLocal8Bit("端口号监听失败！");
		break;
	default:
		strMSG = QString::number(ErrorMSG);
		break;
	}
	SendWarningInfoToUI(strMSG);
	LogWrite::WarningLogMsgOutPut(strMSG);
}

//读取SIM卡号配置文件，转成区站号
void EHT::Convert2StationID()
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

//矫正时钟
void EHT::SetTime()
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//判断是否在线
			if (Clients[i].Online == false)
				continue;//离线返回
			func_SetTime_Lib(Clients[i].StationID,Clients[i].SocketID);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit( "台站号：") + Clients[i].StationID + QString::fromLocal8Bit("，设备号 ") + Clients[i].DeviceID +QString::fromLocal8Bit( "自动矫正时钟."));
	}
}

//自动检测离线
void EHT::Disconnect()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.size(); i++)
	{
		
			int time_t = currentTime.toTime_t() - Clients[i].LatestTimeOfHeartBeat.toTime_t();
			//大于5分钟
			if (time_t >900 && (Clients[i].Online == true))
			{
				Clients[i].Online = false;
				emit OffLineSignal(m_ServiceName,Clients[i].StationID,Clients[i].LatestTimeOfHeartBeat,Clients[i].LoginTime,Clients[i].DeviceID);

					QJsonObject HBJson;
					HBJson.insert("DeviceID", Clients[i].DeviceID);
					HBJson.insert("StationID", Clients[i].StationID);
					HBJson.insert("ServiceTypeID", QString::number(m_ServiceID));
					QDateTime current_date_time = QDateTime::currentDateTime();
					QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
					HBJson.insert("HBTime", current_date);
					HBJson.insert("OnLineStatus", false);
					QJsonDocument document;
					document.setObject(HBJson);
					QByteArray byteArray = document.toJson(QJsonDocument::Compact);
					LPCSTR dataChar;
					dataChar = byteArray.data();
					//发送至消息中间件
					if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
						 GetErrorSlot(10304);
				
				LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("未检测到心跳包,区站号 ") + Clients[i].StationID +QString::fromLocal8Bit("，设备号 ")+ Clients[i].DeviceID+QString::fromLocal8Bit( "已离线"));
			}
	}
}

//终端命令操作
void EHT::SendCommand(int cmm, QString StationID, QString Params1, QString Params2)
{
	pIOCP->SetWebCommand(1);
	//找到对应台站号的Socket值
	unsigned int SocketID = 0;
	SocketID = GetSocket(StationID);
	func_SetCommand(SocketID, cmm, Params1, Params2,StationID);
}
//统计在线个数
int EHT::GetOnlineCount()
{
	int count = 0;
	for (int  i = 0; i < Clients.count(); i++)
	{
		if (Clients[i].Online)
			count++;
	}
	return count;
}

//重连MQ
void EHT::ReConnectActiveMq()
{
	//已经连接
	LPCSTR dataChar = "test";
	if (g_SimpleProducer.send(dataChar, strlen(dataChar)) == 1)
		return;
	//重连是否开启
	if (ReconnectTimer->isActive())
		return;
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("消息中间件开始重连..."));
	ReconnectTimer->start(1000 * 10);
}

void EHT::Reconnect()
{
	LPCSTR dataChar = "test";
	if (g_SimpleProducer.send(dataChar, strlen(dataChar))==1)
	{
		LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("消息中间件已经重连"));
		ReconnectTimer->stop();
		return;
	}
	g_SimpleProducer.close();
//	g_SimpleProducer_ZDH.close();
	//g_SimpleProducer_sh.close();
	

	activemq::library::ActiveMQCPP::initializeLibrary();
	g_SimpleProducer.start();
	//g_SimpleProducer_ZDH.start();
	//g_SimpleProducer_sh.start();
}

//打开调试窗体
void EHT::OpenCtrlWnd(QString StationID,QString DeviceID)
{
	for (int  i = 0; i < Clients.count(); i++)
	{
		if (Clients[i].StationID.compare(StationID) == 0 &&
			Clients[i].DeviceID.compare(DeviceID)==0)
		{
			if (StationID.toUpper().compare("NULL")==0)
			{
				func_GetControlWidget(DeviceID, Clients[i].SocketID, nullptr);
				return;
			}
			func_GetControlWidget(StationID, Clients[i].SocketID,nullptr);
			return;
		}
		
	}
	
}