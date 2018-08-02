#include "EHT.h"
#include "ConfigWnd.h"
#include"LogWrite.h"
#include<qsettings.h>
EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//��ʼ��IOCP
	InitIOCP();
	//��ȡSIM���������ļ���ת����վ��
	Convert2StationID();
	m_IsRun = false;
	SetTimeTimer = new QTimer(parent);
	connect(SetTimeTimer, SIGNAL(timeout()), this, SLOT(SetTime()));
	SetTimeTimer->start(1000 * 60 * 60*24);

	OffLineTimer = new QTimer(parent);
	connect(OffLineTimer, SIGNAL(timeout()), this, SLOT(Disconnect()));
	OffLineTimer->start(1000 * 60 * 10);
}

EHT::~EHT()
{
}
//���ض�̬���ӿ�
LRESULT EHT::LoadLib(QString Lib_Path)
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
			return -1;

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
			return 0;
		
		//��ȡIP
		m_IP = CfgWnd.m_IP;
		//�ж϶˿ںϷ���
		if (!IsLegallyPort(CfgWnd.m_Port))
			return -2;
		//��ȡ����
		m_Attribute = CfgWnd.m_Attribute;
		return true;
	}
	return false;
}
//ж�ض�̬���ӿ�
bool EHT::UnloadLib()
{
	return	m_Lib.unload();
}
//��ȡ�汾��
QString EHT::GetVesionNo()
{
	return m_Vesion;
}
//��ȡҵ��ID
int EHT::GetServiceID()
{
	return m_ServiceID;
}
//��ȡҵ������
QString EHT::GetServiceName()
{
	return m_ServiceName;
}
//��ȡIP��
QString EHT::GetIP()
{
	return m_IP;
}
//��ȡ�˿ں�
int EHT::GetPort()
{
	return m_Port;
}
//��ȡSocket��
unsigned int EHT::GetSocket(QString StationID)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].StationID==StationID)
			return Clients[i].SocketID;
	}
	return 0;
}

//��ȡҵ������
QString EHT::GetAttribute()
{
	return m_Attribute;
}
//��ȡ���ݽ���
Char2Json EHT::GetDataFunc()
{
	return m_DataFunc;
}
//�����������ݷ���
void EHT::Run(QThreadPool &ThreadPool)
{
	if (pIOCP == NULL)
		InitIOCP();
	pIOCP->func_Char2Json = (Char2Json)m_Lib.resolve("Char2Json");
	m_DataFunc= (Char2Json)m_Lib.resolve("Char2Json");
	pIOCP->SetListenedPort(m_Port, m_IP,m_ServiceID);
	ThreadPool.start(pIOCP);
	m_IsRun = true;
}

//�����������ݷ���
void EHT::Stop()
{
	if (pIOCP == nullptr)
		return;
	//�ر�IOCP
	pIOCP->Stop();
	UnloadLib();
	m_IsRun = false;
	pIOCP = nullptr;
}
//��ʼ��IOCP
void EHT::InitIOCP()
{
	//IOCP���߳�
	pIOCP = new IOCP();
	//�豸����֪ͨ
	connect(pIOCP, SIGNAL(OffLineSignal(unsigned int)), this, SLOT(OffLineSlot(unsigned int)), Qt::QueuedConnection);
	//�豸���ݴ���֪ͨ
	connect(pIOCP, SIGNAL(GetErrorSignal(int)), this, SLOT(GetErrorSlot(int)), Qt::QueuedConnection);
	//�豸������֪ͨ
	connect(pIOCP, SIGNAL(NewDataSignal(QString, QString,int, unsigned int)), this, SLOT(NewDataSlot(QString ,QString ,int, unsigned int)), Qt::QueuedConnection);
	//�豸����״̬֪ͨ
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, int, QString)), this, SLOT(OperationResultSlot(QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString,QString, int, QString)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(OperationResultSignal(QString, QString, QString, QString, QString, int, QString)), this, SLOT(OperationResultSlot(QString, QString, QString, QString, QString, int, QString)),Qt::QueuedConnection);
}
//��������״̬
bool EHT::IsRun()
{
	return m_IsRun;
}
//�ж϶˿ںϷ���
bool EHT::IsLegallyPort(int port)
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
	srvAddr.sin_port = htons(m_Port);
	//��SOCKET������
	int bindResult = ::bind(BindSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == bindResult)
		return false;
	closesocket(BindSocket);
	return true;
}
//���ߴ���
void EHT::OffLineSlot(unsigned int CltSocket)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//�ҵ�����
		if (Clients[i].SocketID == CltSocket)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			LogWrite::SYSLogMsgOutPut("��վ�� " + Clients[i].StationID + "�Ѿ��Ͽ�����");
			Clients[i].SocketID = 0;//Socket����
			Clients[i].Online = false;//��������״̬
			emit OffLineSignal(m_ServiceName, Clients[i].StationID, current_date_time, Clients[i].LoginTime);
			break;
		}
	}
	
}
//�����ݴ���
void EHT::NewDataSlot(QString StationID, QString IP, int Port, unsigned int CltSocket)
{
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
			emit OnLineSignal(m_ServiceName,StationID,Clients[i].LatestTimeOfHeartBeat,Clients[i].LoginTime);//ˢ��UI
			return;
		}
	}
	//�����ڲ���
	CLIENTINFO clientinfo{ IP, Port,CltSocket,StationID,current_date_time,true,current_date_time };
	Clients.push_back(clientinfo);
	LogWrite::SYSLogMsgOutPut("���豸�����ӣ�̨վ��Ϊ��" + clientinfo.StationID);
	emit  OnLineSignal(m_ServiceName, StationID,clientinfo.LatestTimeOfHeartBeat,clientinfo.LoginTime);;//ˢ��UI
}
//�ն��������
void EHT:: OperationResultSlot(QString Value, int SrvPort, QString StationID)
{

}
void EHT::OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID)
{

}

void EHT::OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID)
{

}
//��ȡ����
void EHT:: GetErrorSlot(int ErrorMSG)
{
	
}
//��ȡSIM���������ļ���ת����վ��
void EHT::Convert2StationID()
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
void EHT::SetTime()
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
	if (m_ServiceID == TRSF)
	{
		for (int i = 0; i < Clients.size(); i++)
		{
			//�ж��Ƿ�����
			if (Clients[i].Online == false)
				continue;//���߷���
			int chk = 0;
			int socketID = Clients[i].SocketID;
			int SrcAdrr = Clients[i].StationID.toInt();
			BYTE bytes[1024];
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
			bytes[12] = chk & 0xff;//У��λ �ڰ�λ
			bytes[13] = (chk >> 8) & 0xff;//�߰�λ
			bytes[14] = 0xff;
			QByteArray data;
			for (int i = 0; i < 15; i++)
			{
				data.append(bytes[i]);
			}
			QString str;
			str = QString::fromUtf8(data.data(), data.length());
			int result = ::send(socketID, (char *)bytes, 15, 0);
			LogWrite::DataLogMsgOutPut(str);
			LogWrite::SYSLogMsgOutPut("����ˮ��" + Clients[i].StationID + "�Զ�����ʱ��." );
		}
	}
	else
	{
		for (int  i= 0; i < Clients.size(); i++)
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
			LogWrite::SYSLogMsgOutPut("̨վ�ţ�" + Clients[i].StationID + "�Զ�����ʱ��." );
		}
	}
}

//�Զ��������
void EHT::Disconnect()
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
				emit OffLineSignal(m_ServiceName,Clients[i].StationID,Clients[i].LatestTimeOfHeartBeat,Clients[i].LoginTime);
				LogWrite::SYSLogMsgOutPut("δ��⵽������,��վ�� " + Clients[i].StationID + "������");
			}
	}
}