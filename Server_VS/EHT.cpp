#include "EHT.h"
#include "ConfigWnd.h"
EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//IOCP���߳�
	pIOCP = new IOCP();
	//�豸����֪ͨ
	connect(pIOCP, SIGNAL(NoticfyOffLine(int, int)), parent, SLOT(OffLine(int, int)), Qt::QueuedConnection);
	//�豸���ݴ���֪ͨ
	connect(pIOCP, SIGNAL(NoticfyServerError(int)), parent, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//�豸������֪ͨ
	connect(pIOCP, SIGNAL(NoticfyServerUpdateUI(QString, QString, int, bool, QString, int, int, int)), parent, SLOT(UpdateUI(QString, QString, int, bool, QString, int, int, int)), Qt::QueuedConnection);
	//�豸����״̬֪ͨ
	connect(pIOCP, SIGNAL(NoticfyServerOperateStatus(int)), parent, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//��������
	connect(pIOCP, SIGNAL(NoticfyServerHB(QString, int, int, int, QString, QString)), parent, SLOT(HeartBeat(QString, int, int, int, QString, QString)), Qt::QueuedConnection);

}

EHT::~EHT()
{
}
//���ض�̬���ӿ�
bool EHT::LoadLib(QString Lib_Path)
{
	m_Lib.setFileName(Lib_Path);
	//(strName);
	//��ȡ�ɹ�
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//��ȡҵ��ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//��ȡҵ������
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("");
		if (!(func_GetServiceTypeID&&func_GetServiceTypeName))
			return false;

		//��ȡҵ������
		m_ServiceID = func_GetServiceTypeID();
		//��ȡ�˿ں�
		m_Port = func_GetPort();
		//��ȡҵ������
		m_ServiceName = func_GetServiceTypeName();
		//����IP�Ͷ˿����ô���
		ConfigWnd CfgWnd(this);
		CfgWnd.DialogMode = true;
		CfgWnd.SetServicePort(m_Port);
		int r = CfgWnd.exec();
		if (r != QDialog::Accepted)
			return false;
		//�ж϶˿ںϷ���
		if (!IsLegallyPort(CfgWnd.m_Port))
			return false;
		//��ȡIP
		m_IP= CfgWnd.m_IP; 
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
int EHT::GetSocket()
{
	return m_Socket;
}
//��ȡҵ������
QString EHT::GetAttribute()
{
	return m_Attribute;
}
void EHT::Run(QThreadPool &ThreadPool)
{
	ThreadPool.start(pIOCP);
}

bool EHT::IsLegallyPort(int port)
{
	//for (int i = 0; i < ClientInfo.size(); i++)
	//{
	//	if (ClientInfo[i].ServerPortID == port)
	//		return false;
	//}
	return true;
}