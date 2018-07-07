#include "EHT.h"

EHT::EHT(QWidget *parent)
	: QWidget(parent)
{
	//�豸����֪ͨ
	connect(this, SIGNAL(NoticfyOffLine(int, int)), parent, SLOT(OffLine(int, int)), Qt::QueuedConnection);
	//�豸���ݴ���֪ͨ
	connect(this, SIGNAL(NoticfyServerError(int)), parent, SLOT(GetErrorMSG(int)), Qt::QueuedConnection);
	//�豸������֪ͨ
	connect(this, SIGNAL(NoticfyServerUpdateUI(QString, QString, int, bool, QString, int, int, int)), parent, SLOT(UpdateUI(QString, QString, int, bool, QString, int, int, int)), Qt::QueuedConnection);
	//�豸����״̬֪ͨ
	connect(this, SIGNAL(NoticfyServerOperateStatus(int)), parent, SLOT(GetCommandStatus(int)), Qt::QueuedConnection);
	//��������
	connect(this, SIGNAL(NoticfyServerHB(QString, int, int, int, QString, QString)), parent, SLOT(HeartBeat(QString, int, int, int, QString, QString)), Qt::QueuedConnection);

	//IOCP���߳�
//	m_pIOCP = new IOCP(parent);
}

EHT::~EHT()
{
}
