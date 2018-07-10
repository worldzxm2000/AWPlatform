#include "EHT.h"
#include "ConfigWnd.h"
EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//IOCP子线程
	pIOCP = new IOCP();
	//设备离线通知
	connect(pIOCP, SIGNAL(NoticfyOffLine(int, int)), parent, SLOT(OffLine(int, int)), Qt::QueuedConnection);
	//设备数据错误通知
	connect(pIOCP, SIGNAL(NoticfyServerError(int)), parent, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(pIOCP, SIGNAL(NoticfyServerUpdateUI(QString, QString, int, bool, QString, int, int, int)), parent, SLOT(UpdateUI(QString, QString, int, bool, QString, int, int, int)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(pIOCP, SIGNAL(NoticfyServerOperateStatus(int)), parent, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//心跳处理
	connect(pIOCP, SIGNAL(NoticfyServerHB(QString, int, int, int, QString, QString)), parent, SLOT(HeartBeat(QString, int, int, int, QString, QString)), Qt::QueuedConnection);

}

EHT::~EHT()
{
}
//加载动态链接库
bool EHT::LoadLib(QString Lib_Path)
{
	m_Lib.setFileName(Lib_Path);
	//(strName);
	//读取成功
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//获取业务名称
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("");
		if (!(func_GetServiceTypeID&&func_GetServiceTypeName))
			return false;

		//获取业务类型
		m_ServiceID = func_GetServiceTypeID();
		//获取端口号
		m_Port = func_GetPort();
		//获取业务名称
		m_ServiceName = func_GetServiceTypeName();
		//开启IP和端口设置窗体
		ConfigWnd CfgWnd(this);
		CfgWnd.DialogMode = true;
		CfgWnd.SetServicePort(m_Port);
		int r = CfgWnd.exec();
		if (r != QDialog::Accepted)
			return false;
		//判断端口合法性
		if (!IsLegallyPort(CfgWnd.m_Port))
			return false;
		//获取IP
		m_IP= CfgWnd.m_IP; 
		//获取描述
		m_Attribute = CfgWnd.m_Attribute;
		return true;
	}
	return false;
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
int EHT::GetSocket()
{
	return m_Socket;
}
//获取业务描述
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