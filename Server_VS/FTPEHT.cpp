#include "FTPEHT.h"
#include "ConfigWnd.h"
#include"LogWrite.h"
#include<QSettings>
#include<QDir>
#include<QtXml>
FTPEHT::FTPEHT(QWidget *parent)
{
	//初始化IOCP
	InitIOCP();
	b_IsReconnect = false;//MQ重连状态
	IsExistImageXML = false;
	//读取SIM卡号配置文件，转成区站号
	Convert2StationID();
	m_IsRun = false;
	b_IsRunMQ = false;
	WebCommand = false;
	SetTimeTimer = new QTimer(parent);
	connect(SetTimeTimer, SIGNAL(timeout()), this, SLOT(SetTime()));
	SetTimeTimer->start(1000 * 60 * 60 * 24);

	OffLineTimer = new QTimer(parent);
	connect(OffLineTimer, SIGNAL(timeout()), this, SLOT(Disconnect()));
	OffLineTimer->start(1000 * 60 * 10);

	ReconnectTimer = new QTimer(parent);
	ReconnectTimer->connect(ReconnectTimer, SIGNAL(timeout()), this, SLOT(Reconnect()));

	ReHandleZB = new QTimer(parent);
	ReHandleZB->connect(ReHandleZB,SIGNAL(timeout()),this,SLOT(MoveImageToDesAddr()));
}

FTPEHT::~FTPEHT()
{
}

//加载动态链接库
LRESULT FTPEHT::LoadLib(QString Lib_Path)
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
		if (!(func_GetServiceTypeID && func_GetServiceTypeName && func_GetVersionNo && func_GetPort&&func_Char2Json))
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
		ConfigWnd CfgWnd(this->parentWidget());
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
bool FTPEHT::UnloadLib()
{
	return	m_Lib.unload();
}
//获取版本号
QString FTPEHT::GetVesionNo()
{
	return m_Vesion;
}
//获取业务ID
int FTPEHT::GetServiceID()
{
	return m_ServiceID;
}
//获取业务名称
QString FTPEHT::GetServiceName()
{
	return m_ServiceName;
}
//获取IP号
QString FTPEHT::GetIP()
{
	return m_IP;
}
//获取端口号
int FTPEHT::GetPort()
{
	return m_Port;
}
//获取Socket号
unsigned int FTPEHT::GetSocket(QString StationID)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].StationID == StationID)
			return Clients[i].SocketID;
	}
	return 0;
}

//获取业务描述
QString FTPEHT::GetAttribute()
{
	return m_Attribute;
}
//获取数据解析
Char2Json FTPEHT::GetDataFunc()
{
	return m_DataFunc;
}
//启动监听数据服务
void FTPEHT::Run(QThreadPool &ThreadPool)
{
	if (pIOCP == NULL)
		InitIOCP();
	pIOCP->func_Char2Json = (Char2Json)m_Lib.resolve("Char2Json");
	m_DataFunc = (Char2Json)m_Lib.resolve("Char2Json");
	pIOCP->SetListenedPort(m_Port, m_IP, m_ServiceID);
	ThreadPool.start(pIOCP);
	m_IsRun = true;
}

//结束监听数据服务
void FTPEHT::Stop()
{
	if (pIOCP == nullptr)
	{
		UnloadLib();
		return;
	}
	//关闭IOCP
	pIOCP->Stop();
	UnloadLib();
	m_IsRun = false;
	pIOCP = nullptr;
}
//初始化IOCP
void FTPEHT::InitIOCP()
{
	//IOCP子线程
	pIOCP = new IOCP();
	//设备离线通知
	connect(pIOCP, SIGNAL(OffLineSignal(unsigned int)), this, SLOT(OffLineSlot(unsigned int)), Qt::QueuedConnection);
	//设备数据错误通知
	connect(pIOCP, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorSlot(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(pIOCP, SIGNAL(NewDataSignal(QString, QString, int,FileType,unsigned int)), this, SLOT(NewDataSlot(QString, QString, int, FileType, unsigned int)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, int, QString)), this, SLOT(OperationResultSlot(QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString, QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, QString, QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString, QString, QString, QString, QString, int, QString)), Qt::QueuedConnection);
	//设备终端命令返回值
	connect(pIOCP, SIGNAL(RecvRealTimeDataSignal(QString)), this, SLOT(RealTimeDataSlot(QString)), Qt::AutoConnection);
}
//返回运行状态
bool FTPEHT::IsRun()
{
	return m_IsRun;
}
//判断端口合法性
bool FTPEHT::IsLegallyPort(int port)
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
void FTPEHT::OffLineSlot(unsigned int CltSocket)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//找到离线
		if (Clients[i].SocketID == CltSocket)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("区站号 ") + Clients[i].StationID + QString::fromLocal8Bit("已经断开连接"));
			Clients[i].SocketID = 0;//Socket置零
			Clients[i].Online = false;//设置离线状态
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, current_date_time, Clients[i].LoginTime);
			break;
		}
	}
}
//有数据传输
void FTPEHT::NewDataSlot(QString StationID, QString IP, int Port,FileType File,unsigned int CltSocket)
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
		IsExistImageXML = false;
		ReconnectTimer->start(1000 * 10);
	}
		break;
	case TXT:
		MoveTXTToDesAddr();
		break;
	default:
		break;
	}
	QDateTime current_date_time = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.count(); i++)
	{
		//存在
		if (Clients[i].StationID.toUpper().compare(StationID.toUpper()) == 0)
		{
			Clients[i].LatestTimeOfHeartBeat = current_date_time;//更新时间
			Clients[i].SocketID = CltSocket;//更新Socket号
			Clients[i].IP = IP;//更新IP
			Clients[i].Port = Port;//更新端口
			Clients[i].Online = true;//设置在线
			emit OnLineSignal(m_ServiceName, StationID, Clients[i].LatestTimeOfHeartBeat, Clients[i].LoginTime);//刷新UI
	     //	LogWrite::DataLogMsgOutPut("新数据已到达！台站号为：" + Clients[i].StationID);
			return;
		}
	}
	//不存在插入
	CLIENTINFO clientinfo{ IP, Port,CltSocket,StationID,current_date_time,true,current_date_time };
	Clients.push_back(clientinfo);
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("新设备已连接，台站号为：") + clientinfo.StationID);
	emit  OnLineSignal(m_ServiceName, StationID, clientinfo.LatestTimeOfHeartBeat, clientinfo.LoginTime);;//刷新UI
}

//图片处理
void FTPEHT::MoveImageToDesAddr()
{
	if (IsExistImageXML)
		ReHandleZB->stop();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd");
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
		//获取图片名称
		QStringList namestrlit = name.split(".");
		if (namestrlit.count() < 1)
			continue;
		//判断是否存在识别结果XML
		QFileInfo file("E:\\EcologyImage\\" + namestrlit.at(0) + ".xml");
		if (file.exists() == false)
			return;
		IsExistImageXML = true;
		//两个文件都存在,生成原始图和缩略图
		QString DesFile_Image = "D://Tomcat 8.0//webapps//byd//upload//yszb//" + current_date;//原始图
		QString DesFile_MinImage = "D://Tomcat 8.0//webapps//byd//upload//slzb//" + current_date;//缩略图
		QDir dir(DesFile_Image);
		if (!dir.exists())
			dir.mkpath(DesFile_Image);//创建多级目录
		QDir dir_mi(DesFile_MinImage);
		if (!dir_mi.exists())
			dir_mi.mkpath(DesFile_MinImage);//创建多级目录
		DesFile_Image += "\\" + name;
		DesFile_MinImage += "\\" + name;
		QImage minImage;
		minImage.load(path);
		minImage = minImage.scaled(300, 200, Qt::KeepAspectRatio);
		minImage.save(DesFile_MinImage, "JPG");
		//XML文件处理
		QJsonObject Json;
		MoveXMLToDesAddr(Json);
		//复制成功后 删除源文件
		if(QFile::copy(path, DesFile_Image))
			QFile::remove(path);
	}
}

//文本处理
void FTPEHT::MoveTXTToDesAddr()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd");
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
		if(QFile::copy(path, DesFile_TXT))
			QFile::remove(path);
	}
}

//XML处理
void FTPEHT::MoveXMLToDesAddr(QJsonObject &Json)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd");
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
		QString DesFile_XML = "D://SH_ZB_TXT//" + current_date;//目的路径
		QDir dir(DesFile_XML);
		if (!dir.exists())
			dir.mkpath(DesFile_XML);//创建多级目录
		DesFile_XML += "\\" + name;
		//解析文件
		QFile file(path); //相对路径、绝对路径、资源路径都行
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
		Json.insert("DeviceID", "3");
		//设备是否含有区站号
		Json.insert("ContainSID", false);
		Json.insert("StationID", "3");
		//观测时间
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
		Json.insert("ObserveTime", current_date);
		//业务号
		Json.insert("StationID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_SimpleProducer_sh.send(dataChar, strlen(dataChar)) < 0)
			 GetErrorSlot(10304);
		//复制成功后 删除源文件
		if (QFile::copy(path, DesFile_XML))
			QFile::remove(path);
	}
}

//终端命令操作
void FTPEHT::OperationResultSlot(QString Value, int SrvPort, QString StationID)
{
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value + QString::fromLocal8Bit(",信息来自业务号：") + m_ServiceName + QString::fromLocal8Bit(",台站号：") + StationID;
	if (this->WebCommand)
	{
		QJsonObject json;
		json.insert("StationID", StationID);
		json.insert("ServiceTypeID", m_ServiceID);
		json.insert("Command", QString::number(CurrentCommand));
		json.insert("Count", 1);
		json.insert("RecvValue1", Value);
		this->WebCommand = false;
		this->CurrentCommand = NONE;
		//发送至Web服务器
		emit SendToWebServiceSignal(json);
	}
	//UI显示
	//emit SendToUI(OperationLog);
	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}
void FTPEHT::OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID)
{
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value1 + QString::fromLocal8Bit("，返回值：") + Value2 + QString::fromLocal8Bit(",信息来自业务号：") + m_ServiceName + QString::fromLocal8Bit(",台站号：") + StationID;
	if (this->WebCommand)
	{
		QJsonObject json;
		json.insert("StationID", StationID);
		json.insert("ServiceTypeID", m_ServiceID);
		json.insert("Command", QString::number(CurrentCommand));
		json.insert("Count", 2);
		json.insert("RecvValue1", Value1);
		json.insert("RecvValue2", Value2);
		this->WebCommand = false;
		this->CurrentCommand = NONE;
		//发送至Web服务器
		emit SendToWebServiceSignal(json);
	}
	//emit SendToUI(OperationLog);
	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}

void FTPEHT::OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID)
{
	//前端发送指令
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("终端返回值：") + Value1 + QString::fromLocal8Bit("，返回值：") + Value2 + QString::fromLocal8Bit(",返回值：") + Value3 + QString::fromLocal8Bit("，返回值:") + Value4 + QString::fromLocal8Bit(",信息来自业务号：") + m_ServiceName + QString::fromLocal8Bit(",台站号：") + StationID;
	if (this->WebCommand)
	{
		QJsonObject json;
		json.insert("StationID", StationID);
		json.insert("ServiceTypeID", m_ServiceID);
		json.insert("Command", QString::number(CurrentCommand));
		json.insert("Count", 4);
		json.insert("RecvValue1", Value1);
		json.insert("RecvValue2", Value2);
		json.insert("RecvValue3", Value3);
		json.insert("RecvValue4", Value4);
		this->WebCommand = false;
		this->CurrentCommand = NONE;
		//发送至Web服务器
		emit SendToWebServiceSignal(json);
	}
	//emit SendToUI(OperationLog);
	//写入数据日志
	LogWrite::DataLogMsgOutPut(OperationLog);
}
//获取错误
void FTPEHT::GetErrorSlot(int ErrorMSG)
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
void FTPEHT::Convert2StationID()
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
void FTPEHT::SetTime()
{
	QDateTime nowtime = QDateTime::currentDateTime();
	QString datetime = nowtime.toString("yyyy.MM.dd hh:mm:ss");
	QString year, month, day, hour, min, sec;
	year = nowtime.toString("yy");
	month = nowtime.toString("MM");
	day = nowtime.toString("dd");
	hour = nowtime.toString("hh");
	min = nowtime.toString("mm");
	sec = nowtime.toString("ss");
	switch (m_ServiceID)
	{
	case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:
	{
		for (int i = 0; i < Clients.size(); i++)
		{
			//判断是否在线
			if (Clients[i].Online == false)
				continue;//离线返回
			int chk = 0;
			int socketID = Clients[i].SocketID;
			int SrcAdrr = Clients[i].StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x0a;//帧长度
			bytes[2] = 0x81;//帧命令
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//源地址
			chk += bytes[3];
			bytes[4] = (SrcAdrr >> 8) & 0xff;
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
			bytes[13] = (chk >> 8) & 0xff;//高八位
			bytes[14] = 0xff;
			int result = ::send(socketID, (char *)bytes, 15, 0);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("土壤水分") + Clients[i].StationID + QString::fromLocal8Bit("自动矫正时钟."));
		}
		break;
	}

	default:
	{
		for (int i = 0; i < Clients.size(); i++)
		{
			//判断是否在线
			if (Clients[i].Online == false)
				continue;//离线返回
			int socketID = Clients[i].SocketID;
			QString Comm = "DATETIME " + datetime + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			int result = ::send(socketID, ch, len, 0);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("台站号：") + Clients[i].StationID + QString::fromLocal8Bit("自动矫正时钟."));
		}
		break;
	}

	}
}

//自动检测离线
void FTPEHT::Disconnect()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString current_date = currentTime.toString("yyyy.MM.dd hh:mm:ss");
	for (int i = 0; i < Clients.size(); i++)
	{

		int time_t = currentTime.toTime_t() - Clients[i].LatestTimeOfHeartBeat.toTime_t();
		//大于5分钟
		if (time_t >300 && (Clients[i].Online == true))
		{
			Clients[i].Online = false;
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, Clients[i].LatestTimeOfHeartBeat, Clients[i].LoginTime);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("未检测到心跳包,区站号 ") + Clients[i].StationID + QString::fromLocal8Bit("已离线"));
		}
	}
}

//终端命令操作
void FTPEHT::SendCommand(OPCommand cmm, QString StationID, QString Params1, QString Params2, bool WebCommand)
{
	this->WebCommand = WebCommand;
	pIOCP->SetWebCommand(1);
	//获取当前终端指令
	this->CurrentCommand = cmm;
	//找到对应台站号的Socket值
	unsigned int SocketID = 0;
	SocketID = GetSocket(StationID);
	//土壤水分
	switch (m_ServiceID)
	{
	case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:
	{
		switch (cmm)
		{
		case NONE:
			break;
		case BASEINFO:
			break;
			//设置或读取采集器日期时间操作
		case DATETIME:
		{
			if (Params1 != "NULL")
			{
				QDateTime nowtime = QDateTime::currentDateTime();
				QString datetime = nowtime.toString("yyyy.MM.dd hh:mm:ss");
				QString year, month, day, hour, min, sec;
				year = nowtime.toString("yy");
				month = nowtime.toString("MM");
				day = nowtime.toString("dd");
				hour = nowtime.toString("hh");
				min = nowtime.toString("mm");
				sec = nowtime.toString("ss");

				int chk = 0;
				int SrcAdrr = StationID.toInt();
				BYTE bytes[1024] = { 0 };
				bytes[0] = 0xaa;
				bytes[1] = 0x0a;//帧长度
				bytes[2] = 0x81;//帧命令
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//源地址
				chk += bytes[3];
				bytes[4] = (SrcAdrr >> 8) & 0xff;
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
				bytes[13] = (chk >> 8) & 0xff;//高八位
				bytes[14] = 0xff;
				::send(SocketID, (char *)bytes, 15, 0);
			}
			else
			{
				int chk = 0;
				int SrcAdrr = StationID.toInt();
				BYTE bytes[1024] = { 0 };
				bytes[0] = 0xaa;
				bytes[1] = 0x03;//帧长度
				bytes[2] = 0x82;//帧命令
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//源地址
				chk += bytes[3];
				bytes[4] = (SrcAdrr >> 8) & 0xff;
				chk += bytes[4];
				bytes[5] = chk & 0xff;//校验位 低八位
				bytes[6] = (chk >> 8) & 0xff;//高八位
				bytes[7] = 0xff;
				::send(SocketID, (char *)bytes, 8, 0);
			}
		}
		break;
		//设置或读取采集器IP和端口
		case ID:
		{
			if (Params1 != "NULL"&&Params2 != "NULL")
			{
			}
		}
		break;
		case LAT:
			break;
		case LONGITUDE:
			break;
		case ALT:
			break;
		case CFSET:
			break;
		case CAPTIME:
			break;
		case CAPINTERVAL:
			break;
		case SNAPSHOT:
			break;
		case RESET:
			break;
		case UPDATE:
			break;
			//补抄数据命令
		case DMTD:
		{
			if (Params1 != "NULL"&&Params2 != "NULL")
			{
				QDateTime Btime = QDateTime::fromString(Params1, "yyyy-MM-dd hh:mm:ss");
				QDateTime Etime = QDateTime::fromString(Params2, "yyyy-MM-dd hh:mm:ss");
				QString yearB, monthB, dayB, hourB, minB, yearE, monthE, dayE, hourE, minE;
				yearB = Btime.toString("yy");
				monthB = Btime.toString("MM");
				dayB = Btime.toString("DD");
				hourB = Btime.toString("hh");
				minB = Btime.toString("mm");

				yearE = Etime.toString("yy");
				monthE = Etime.toString("MM");
				dayE = Etime.toString("DD");
				hourE = Etime.toString("hh");
				minE = Etime.toString("mm");
				int chk = 0;
				int SrcAdrr = StationID.toInt();
				BYTE bytes[1024] = { 0 };
				bytes[0] = 0xaa;
				bytes[1] = 0x0d;//帧长度
				bytes[2] = 0x94;//帧命令
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//源地址
				chk += bytes[3];
				bytes[4] = (SrcAdrr >> 8) & 0xff;
				chk += bytes[4];
				bytes[5] = yearB.toInt() - 2000;
				chk += bytes[5];
				bytes[6] = monthB.toInt();
				chk += bytes[6];
				bytes[7] = dayB.toInt();
				chk += bytes[7];
				bytes[8] = hourB.toInt();
				chk += bytes[8];
				bytes[9] = minB.toInt();
				chk += bytes[9];
				bytes[10] = yearE.toInt() - 2000;
				chk += bytes[10];
				bytes[11] = monthE.toInt();
				chk += bytes[11];
				bytes[12] = dayE.toInt();
				chk += bytes[12];
				bytes[13] = hourE.toInt();
				chk += bytes[13];
				bytes[14] = minE.toInt();
				chk += bytes[14];
				bytes[15] = chk & 0xff;//校验位 低八位
				bytes[16] = (chk >> 8) & 0xff;//高八位
				bytes[17] = 0xff;
				::send(SocketID, (char *)bytes, 18, 0);
			}
		}
		default:
			break;
		}
		break;
	}
	default:
	{
		//发送终端命令
		switch (cmm)
		{
			//读取采集器的基本信息
		case BASEINFO:
		{
			QString Comm = "BASEINFO\r\n";
			if (Params1 != "NULL")
			{
				Comm = "BASEINFO " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "ID " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "ALT " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "CAPTIME " + Params1 + " " + Params2 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "LONG " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "CAPINTERVAL " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "DATETIME " + Params1 + "\r\n";
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
			if (Params1 != "NULL")
			{
				Comm = "LAT " + Params1 + "\r\n";
			}
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		//补抄数据命令
		case DMTD:
		{
			if (Params1 != "NULL"&&Params2 != "NULL")
			{
				QString Comm = "DMTD " + Params1 + " " + Params2 + "\r\n";
				QByteArray ba = Comm.toLatin1();
				LPCSTR ch = ba.data();
				int len = Comm.length();
				::send(SocketID, ch, len, 0);
			}
			break;
		}
		default:
			break;
		}
	}
	break;
	}
}
//统计在线个数
int FTPEHT::GetOnlineCount()
{
	int count = 0;
	for (int i = 0; i < Clients.count(); i++)
	{
		if (Clients[i].Online)
			count++;
	}
	return count;
}

//实时接收数据
void FTPEHT::RealTimeDataSlot(QString data)
{

}

void FTPEHT::ReConnectActiveMq()
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

void FTPEHT::Reconnect()
{
	LPCSTR dataChar = "test";
	if (g_SimpleProducer.send(dataChar, strlen(dataChar)) == 1)
	{
		LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("消息中间件已经重连1"));
		ReconnectTimer->stop();
		return;
	}
	g_SimpleProducer.close();
	g_SimpleProducer_ZDH.close();
	g_SimpleProducer_sh.close();
	string brokerURI;
	string destURI;
	string destURI_1;
	string destURI_sh;
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
	destURI_sh = "SH_BYD";
	clientAck = false;
	useTopics = false;
	g_SimpleProducer.start(UserName, Password, brokerURI, numMessages, destURI, useTopics, clientAck);
	g_SimpleProducer_ZDH.start(UserName, Password, brokerURI, numMessages, destURI_1, useTopics, clientAck);
	g_SimpleProducer_sh.start(UserName, Password, brokerURI, numMessages, destURI_sh, useTopics, clientAck);


}
