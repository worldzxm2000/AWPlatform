#include "EHT.h"

EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//设备离线通知
	connect(this, SIGNAL(NoticfyOffLine(int, int)), parent, SLOT(OffLine(int, int)), Qt::QueuedConnection);
	//设备数据错误通知
	connect(this, SIGNAL(NoticfyServerError(int)), parent, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(this, SIGNAL(NoticfyServerUpdateUI(QString, QString, int, bool, QString, int, int, int)), parent, SLOT(UpdateUI(QString, QString, int, bool, QString, int, int, int)), Qt::QueuedConnection);
	//设备操作状态通知
	connect(this, SIGNAL(NoticfyServerOperateStatus(int)), parent, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//心跳处理
	connect(this, SIGNAL(NoticfyServerHB(QString, int, int, int, QString, QString)), parent, SLOT(HeartBeat(QString, int, int, int, QString, QString)), Qt::QueuedConnection);

	//IOCP子线程
//	m_pIOCP = new IOCP(parent);
}

EHT::~EHT()
{
}
