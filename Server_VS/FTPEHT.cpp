#include "FTPEHT.h"
#include "ConfigWnd.h"
#include"LogWrite.h"
#include<QSettings>
#include<QDir>
#include<QtXml>
FTPEHT::FTPEHT(QWidget *parent)
{
	//��ʼ��IOCP
	InitIOCP();
	b_IsReconnect = false;//MQ����״̬
	IsExistImageXML = false;
	//��ȡSIM���������ļ���ת����վ��
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

//���ض�̬���ӿ�
LRESULT FTPEHT::LoadLib(QString Lib_Path)
{
	m_Lib.setFileName(Lib_Path);
	//(strName);
	//��ȡ�ɹ�
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//��ȡҵ��ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//��ȡҵ������
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("GetPort");//��ȡ�˿ں�
		GetVersionNo_Lib func_GetVersionNo = (GetVersionNo_Lib)m_Lib.resolve("GetVersionNo");//��ȡ�汾��
		Char2Json func_Char2Json = (Char2Json)(m_Lib.resolve("Char2Json"));//��ȡ��������
		if (!(func_GetServiceTypeID && func_GetServiceTypeName && func_GetVersionNo && func_GetPort&&func_Char2Json))
		{
			UnloadLib();
			return -1;
		}


		//��ȡҵ������
		m_ServiceID = func_GetServiceTypeID();
		//��ȡ�˿ں�
		m_Port = func_GetPort();
		//��ȡҵ������
		m_ServiceName = func_GetServiceTypeName();
		//��ȡ�汾��
		m_Vesion = func_GetVersionNo();
		//����IP�Ͷ˿����ô���
		ConfigWnd CfgWnd(this->parentWidget());
		CfgWnd.DialogMode = true;//���� falseΪ��ȡ
		CfgWnd.SetServicePort(m_Port);
		int r = CfgWnd.exec();
		if (r != QDialog::Accepted)
		{
			UnloadLib();
			return 0;
		}


		//��ȡIP
		m_IP = CfgWnd.m_IP;
		//�ж϶˿ںϷ���
		if (!IsLegallyPort(CfgWnd.m_Port))
		{
			UnloadLib();
			return -2;
		}
		//��ȡIP
		m_Port = CfgWnd.m_Port;
		//��ȡ����
		m_Attribute = CfgWnd.m_Attribute;
		return true;
	}
	else
	{
		UnloadLib();
		return false;
	}
}
//ж�ض�̬���ӿ�
bool FTPEHT::UnloadLib()
{
	return	m_Lib.unload();
}
//��ȡ�汾��
QString FTPEHT::GetVesionNo()
{
	return m_Vesion;
}
//��ȡҵ��ID
int FTPEHT::GetServiceID()
{
	return m_ServiceID;
}
//��ȡҵ������
QString FTPEHT::GetServiceName()
{
	return m_ServiceName;
}
//��ȡIP��
QString FTPEHT::GetIP()
{
	return m_IP;
}
//��ȡ�˿ں�
int FTPEHT::GetPort()
{
	return m_Port;
}
//��ȡSocket��
unsigned int FTPEHT::GetSocket(QString StationID)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].StationID == StationID)
			return Clients[i].SocketID;
	}
	return 0;
}

//��ȡҵ������
QString FTPEHT::GetAttribute()
{
	return m_Attribute;
}
//��ȡ���ݽ���
Char2Json FTPEHT::GetDataFunc()
{
	return m_DataFunc;
}
//�����������ݷ���
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

//�����������ݷ���
void FTPEHT::Stop()
{
	if (pIOCP == nullptr)
	{
		UnloadLib();
		return;
	}
	//�ر�IOCP
	pIOCP->Stop();
	UnloadLib();
	m_IsRun = false;
	pIOCP = nullptr;
}
//��ʼ��IOCP
void FTPEHT::InitIOCP()
{
	//IOCP���߳�
	pIOCP = new IOCP();
	//�豸����֪ͨ
	connect(pIOCP, SIGNAL(OffLineSignal(unsigned int)), this, SLOT(OffLineSlot(unsigned int)), Qt::QueuedConnection);
	//�豸���ݴ���֪ͨ
	connect(pIOCP, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorSlot(int)), Qt::QueuedConnection);
	//�豸������֪ͨ
	connect(pIOCP, SIGNAL(NewDataSignal(QString, QString, int,FileType,unsigned int)), this, SLOT(NewDataSlot(QString, QString, int, FileType, unsigned int)), Qt::QueuedConnection);
	//�豸����״̬֪ͨ
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, int, QString)), this, SLOT(OperationResultSlot(QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString, QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, QString, QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString, QString, QString, QString, QString, int, QString)), Qt::QueuedConnection);
	//�豸�ն������ֵ
	connect(pIOCP, SIGNAL(RecvRealTimeDataSignal(QString)), this, SLOT(RealTimeDataSlot(QString)), Qt::AutoConnection);
}
//��������״̬
bool FTPEHT::IsRun()
{
	return m_IsRun;
}
//�ж϶˿ںϷ���
bool FTPEHT::IsLegallyPort(int port)
{
	//��ʼ��WSA    ����socket��̬���ӿ�
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // ����Windows Socket�Ľṹ��Ϣ
	if (WSAStartup(sockVersion, &wsaData) != 0)
		return false;

	SOCKET BindSocket;
	BindSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN  srvAddr;
	//��ȡ����IP
	LPCSTR  ch;
	QByteArray ba = m_IP.toLatin1();
	ch = ba.data();
	srvAddr.sin_addr.S_un.S_addr = inet_addr(ch);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(port);
	//��SOCKET������
	int bindResult = ::bind(BindSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == bindResult)
		return false;
	closesocket(BindSocket);
	return true;
}
//���ߴ���
void FTPEHT::OffLineSlot(unsigned int CltSocket)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//�ҵ�����
		if (Clients[i].SocketID == CltSocket)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("��վ�� ") + Clients[i].StationID + QString::fromLocal8Bit("�Ѿ��Ͽ�����"));
			Clients[i].SocketID = 0;//Socket����
			Clients[i].Online = false;//��������״̬
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, current_date_time, Clients[i].LoginTime);
			break;
		}
	}
}
//�����ݴ���
void FTPEHT::NewDataSlot(QString StationID, QString IP, int Port,FileType File,unsigned int CltSocket)
{
	//̨վ��Ϊ��
	if (StationID == NULL)
		return;
	//ũίվ��ת��
	if (m_ServiceID == NW)
	{
		if (SIM2Staion.contains(StationID))
		{
			//�ҵ��ض��ġ���-ֵ����
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
		//����
		if (Clients[i].StationID.toUpper().compare(StationID.toUpper()) == 0)
		{
			Clients[i].LatestTimeOfHeartBeat = current_date_time;//����ʱ��
			Clients[i].SocketID = CltSocket;//����Socket��
			Clients[i].IP = IP;//����IP
			Clients[i].Port = Port;//���¶˿�
			Clients[i].Online = true;//��������
			emit OnLineSignal(m_ServiceName, StationID, Clients[i].LatestTimeOfHeartBeat, Clients[i].LoginTime);//ˢ��UI
	     //	LogWrite::DataLogMsgOutPut("�������ѵ��̨վ��Ϊ��" + Clients[i].StationID);
			return;
		}
	}
	//�����ڲ���
	CLIENTINFO clientinfo{ IP, Port,CltSocket,StationID,current_date_time,true,current_date_time };
	Clients.push_back(clientinfo);
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("���豸�����ӣ�̨վ��Ϊ��") + clientinfo.StationID);
	emit  OnLineSignal(m_ServiceName, StationID, clientinfo.LatestTimeOfHeartBeat, clientinfo.LoginTime);;//ˢ��UI
}

//ͼƬ����
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
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//�������͹�������ֻΪ�ļ���ʽ
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//�ҵ���ͼƬ
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		//��ȡͼƬ����
		QStringList namestrlit = name.split(".");
		if (namestrlit.count() < 1)
			continue;
		//�ж��Ƿ����ʶ����XML
		QFileInfo file("E:\\EcologyImage\\" + namestrlit.at(0) + ".xml");
		if (file.exists() == false)
			return;
		IsExistImageXML = true;
		//�����ļ�������,����ԭʼͼ������ͼ
		QString DesFile_Image = "D://Tomcat 8.0//webapps//byd//upload//yszb//" + current_date;//ԭʼͼ
		QString DesFile_MinImage = "D://Tomcat 8.0//webapps//byd//upload//slzb//" + current_date;//����ͼ
		QDir dir(DesFile_Image);
		if (!dir.exists())
			dir.mkpath(DesFile_Image);//�����༶Ŀ¼
		QDir dir_mi(DesFile_MinImage);
		if (!dir_mi.exists())
			dir_mi.mkpath(DesFile_MinImage);//�����༶Ŀ¼
		DesFile_Image += "\\" + name;
		DesFile_MinImage += "\\" + name;
		QImage minImage;
		minImage.load(path);
		minImage = minImage.scaled(300, 200, Qt::KeepAspectRatio);
		minImage.save(DesFile_MinImage, "JPG");
		//XML�ļ�����
		QJsonObject Json;
		MoveXMLToDesAddr(Json);
		//���Ƴɹ��� ɾ��Դ�ļ�
		if(QFile::copy(path, DesFile_Image))
			QFile::remove(path);
	}
}

//�ı�����
void FTPEHT::MoveTXTToDesAddr()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//�������͹�������ֻΪ�ļ���ʽ
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//�ҵ���TXT
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QString DesFile_TXT = "D://SH_ZB_TXT//" + current_date;//Ŀ��·��
		QDir dir(DesFile_TXT);
		if (!dir.exists())
			dir.mkpath(DesFile_TXT);//�����༶Ŀ¼
		DesFile_TXT += "\\" + name;
		//���Ƴɹ��� ɾ��Դ�ļ�
		if(QFile::copy(path, DesFile_TXT))
			QFile::remove(path);
	}
}

//XML����
void FTPEHT::MoveXMLToDesAddr(QJsonObject &Json)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.xml");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//�������͹�������ֻΪ�ļ���ʽ
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//�ҵ���XML
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QString DesFile_XML = "D://SH_ZB_TXT//" + current_date;//Ŀ��·��
		QDir dir(DesFile_XML);
		if (!dir.exists())
			dir.mkpath(DesFile_XML);//�����༶Ŀ¼
		DesFile_XML += "\\" + name;
		//�����ļ�
		QFile file(path); //���·��������·������Դ·������
		if (!file.open(QFile::ReadOnly))
			return;

		QDomDocument doc;
		if (!doc.setContent(&file))
		{
			file.close();
			return;
		}
		file.close();
	
		QDomElement root = doc.documentElement(); //���ظ��ڵ�
		QDomNode node = root.firstChildElement("currentCoverage");
		Json.insert("Coverage", node.toElement().text());
		node = root.firstChildElement("density");
		Json.insert("Density", node.toElement().text());
		node = root.firstChildElement("height");
		Json.insert("CanopyHeight", node.toElement().text());
		//�豸ID
		Json.insert("DeviceID", "3");
		//�豸�Ƿ�����վ��
		Json.insert("ContainSID", false);
		Json.insert("StationID", "3");
		//�۲�ʱ��
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
		Json.insert("ObserveTime", current_date);
		//ҵ���
		Json.insert("StationID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_SimpleProducer_sh.send(dataChar, strlen(dataChar)) < 0)
			 GetErrorSlot(10304);
		//���Ƴɹ��� ɾ��Դ�ļ�
		if (QFile::copy(path, DesFile_XML))
			QFile::remove(path);
	}
}

//�ն��������
void FTPEHT::OperationResultSlot(QString Value, int SrvPort, QString StationID)
{
	//ǰ�˷���ָ��
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("�ն˷���ֵ��") + Value + QString::fromLocal8Bit(",��Ϣ����ҵ��ţ�") + m_ServiceName + QString::fromLocal8Bit(",̨վ�ţ�") + StationID;
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
		//������Web������
		emit SendToWebServiceSignal(json);
	}
	//UI��ʾ
	//emit SendToUI(OperationLog);
	//д��������־
	LogWrite::DataLogMsgOutPut(OperationLog);
}
void FTPEHT::OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID)
{
	//ǰ�˷���ָ��
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("�ն˷���ֵ��") + Value1 + QString::fromLocal8Bit("������ֵ��") + Value2 + QString::fromLocal8Bit(",��Ϣ����ҵ��ţ�") + m_ServiceName + QString::fromLocal8Bit(",̨վ�ţ�") + StationID;
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
		//������Web������
		emit SendToWebServiceSignal(json);
	}
	//emit SendToUI(OperationLog);
	//д��������־
	LogWrite::DataLogMsgOutPut(OperationLog);
}

void FTPEHT::OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID)
{
	//ǰ�˷���ָ��
	QString OperationLog;
	OperationLog = QString::fromLocal8Bit("�ն˷���ֵ��") + Value1 + QString::fromLocal8Bit("������ֵ��") + Value2 + QString::fromLocal8Bit(",����ֵ��") + Value3 + QString::fromLocal8Bit("������ֵ:") + Value4 + QString::fromLocal8Bit(",��Ϣ����ҵ��ţ�") + m_ServiceName + QString::fromLocal8Bit(",̨վ�ţ�") + StationID;
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
		//������Web������
		emit SendToWebServiceSignal(json);
	}
	//emit SendToUI(OperationLog);
	//д��������־
	LogWrite::DataLogMsgOutPut(OperationLog);
}
//��ȡ����
void FTPEHT::GetErrorSlot(int ErrorMSG)
{
	QString strMSG;
	switch (ErrorMSG)
	{
	case 1:
		strMSG = QString::fromLocal8Bit("����");
		break;
	case 10300: case 10301: case 10302:
		strMSG = QString::fromLocal8Bit("ͨ�ų�ʼ��ʧ�ܣ�");
		break;
	case 10304:
		strMSG = QString::fromLocal8Bit("��Ϣ�м��ͨ���쳣��");
		ReConnectActiveMq();
		break;
	case 10305:
		strMSG = QString::fromLocal8Bit("�����ڴ����");
		break;
	case 10036:
		strMSG = QString::fromLocal8Bit("Web�����˿��쳣");
		break;
	case -4:
		strMSG = QString::fromLocal8Bit("��������ͨ���쳣��");
		break;
	case -5:
		strMSG = QString::fromLocal8Bit("�豸�ѵǳ���");
		break;
	case 10311:
		strMSG = QString::fromLocal8Bit("�˿ںż���ʧ�ܣ�");
		break;
	default:
		strMSG = QString::number(ErrorMSG);
		break;
	}
	SendWarningInfoToUI(strMSG);
	LogWrite::WarningLogMsgOutPut(strMSG);
}
//��ȡSIM���������ļ���ת����վ��
void FTPEHT::Convert2StationID()
{
	//��ȡCommand.ini·��
	QString path = QCoreApplication::applicationDirPath() + "//SIM2STATION.ini";
	//��INI�ļ�
	QSettings configIniRead(path, QSettings::IniFormat);
	//�ն��������
	int Count = configIniRead.value("NW/Count").toInt();
	//�����ն�����
	for (int i = 0; i < Count; i++)
	{
		QString key = "/NW/STATION" + QString::number(i);
		QString StationID = configIniRead.value(key).toString();
		key = "/NW/SIM" + QString::number(i);
		QString SIMID = configIniRead.value(key).toString();
		SIM2Staion.insert(SIMID, StationID);
	}
}

//����ʱ��
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
			//�ж��Ƿ�����
			if (Clients[i].Online == false)
				continue;//���߷���
			int chk = 0;
			int socketID = Clients[i].SocketID;
			int SrcAdrr = Clients[i].StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x0a;//֡����
			bytes[2] = 0x81;//֡����
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//Դ��ַ
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
			bytes[12] = chk & 0xff;//У��λ �Ͱ�λ
			bytes[13] = (chk >> 8) & 0xff;//�߰�λ
			bytes[14] = 0xff;
			int result = ::send(socketID, (char *)bytes, 15, 0);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("����ˮ��") + Clients[i].StationID + QString::fromLocal8Bit("�Զ�����ʱ��."));
		}
		break;
	}

	default:
	{
		for (int i = 0; i < Clients.size(); i++)
		{
			//�ж��Ƿ�����
			if (Clients[i].Online == false)
				continue;//���߷���
			int socketID = Clients[i].SocketID;
			QString Comm = "DATETIME " + datetime + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			int result = ::send(socketID, ch, len, 0);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("̨վ�ţ�") + Clients[i].StationID + QString::fromLocal8Bit("�Զ�����ʱ��."));
		}
		break;
	}

	}
}

//�Զ��������
void FTPEHT::Disconnect()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString current_date = currentTime.toString("yyyy.MM.dd hh:mm:ss");
	for (int i = 0; i < Clients.size(); i++)
	{

		int time_t = currentTime.toTime_t() - Clients[i].LatestTimeOfHeartBeat.toTime_t();
		//����5����
		if (time_t >300 && (Clients[i].Online == true))
		{
			Clients[i].Online = false;
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, Clients[i].LatestTimeOfHeartBeat, Clients[i].LoginTime);
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("δ��⵽������,��վ�� ") + Clients[i].StationID + QString::fromLocal8Bit("������"));
		}
	}
}

//�ն��������
void FTPEHT::SendCommand(OPCommand cmm, QString StationID, QString Params1, QString Params2, bool WebCommand)
{
	this->WebCommand = WebCommand;
	pIOCP->SetWebCommand(1);
	//��ȡ��ǰ�ն�ָ��
	this->CurrentCommand = cmm;
	//�ҵ���Ӧ̨վ�ŵ�Socketֵ
	unsigned int SocketID = 0;
	SocketID = GetSocket(StationID);
	//����ˮ��
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
			//���û��ȡ�ɼ�������ʱ�����
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
				bytes[1] = 0x0a;//֡����
				bytes[2] = 0x81;//֡����
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//Դ��ַ
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
				bytes[12] = chk & 0xff;//У��λ �Ͱ�λ
				bytes[13] = (chk >> 8) & 0xff;//�߰�λ
				bytes[14] = 0xff;
				::send(SocketID, (char *)bytes, 15, 0);
			}
			else
			{
				int chk = 0;
				int SrcAdrr = StationID.toInt();
				BYTE bytes[1024] = { 0 };
				bytes[0] = 0xaa;
				bytes[1] = 0x03;//֡����
				bytes[2] = 0x82;//֡����
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//Դ��ַ
				chk += bytes[3];
				bytes[4] = (SrcAdrr >> 8) & 0xff;
				chk += bytes[4];
				bytes[5] = chk & 0xff;//У��λ �Ͱ�λ
				bytes[6] = (chk >> 8) & 0xff;//�߰�λ
				bytes[7] = 0xff;
				::send(SocketID, (char *)bytes, 8, 0);
			}
		}
		break;
		//���û��ȡ�ɼ���IP�Ͷ˿�
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
			//������������
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
				bytes[1] = 0x0d;//֡����
				bytes[2] = 0x94;//֡����
				chk += bytes[2];
				bytes[3] = SrcAdrr & 0xff;//Դ��ַ
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
				bytes[15] = chk & 0xff;//У��λ �Ͱ�λ
				bytes[16] = (chk >> 8) & 0xff;//�߰�λ
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
		//�����ն�����
		switch (cmm)
		{
			//��ȡ�ɼ����Ļ�����Ϣ
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
		//���û��ȡ�Զ��۲�վ����վ��
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
		//���û��ȡ�۲ⳡ�κ��߶�
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
		//CF��ģ������
		case CFSET:
		{
			QString Comm = "CFSET\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		//���û��ȡ���ݲɼ�ʱ�䷶Χ
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
		//���û��ȡ�Զ��۲�վ�ľ���
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
		//���û��ȡ���ݲɼ�ʱ����
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
		//���������ɼ���
		case RESET:
		{
			QString Comm = "RESET\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		//Զ����������
		case UPDATE:
		{
			QString Comm = "UPDATE\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		//�ֶ��ɼ���ǰʱ�̵�Ҫ������
		case SNAPSHOT:
		{
			QString Comm = "SNAPSHOT\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		//���û��ȡ�ɼ�������ʱ�����
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
		//���û��ȡ�Զ��۲�վ��γ��
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
		//������������
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
//ͳ�����߸���
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

//ʵʱ��������
void FTPEHT::RealTimeDataSlot(QString data)
{

}

void FTPEHT::ReConnectActiveMq()
{
	//�Ѿ�����
	LPCSTR dataChar = "test";
	if (g_SimpleProducer.send(dataChar, strlen(dataChar)) == 1)
		return;
	//�����Ƿ���
	if (ReconnectTimer->isActive())
		return;
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("��Ϣ�м����ʼ����..."));
	ReconnectTimer->start(1000 * 10);
}

void FTPEHT::Reconnect()
{
	LPCSTR dataChar = "test";
	if (g_SimpleProducer.send(dataChar, strlen(dataChar)) == 1)
	{
		LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("��Ϣ�м���Ѿ�����1"));
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
