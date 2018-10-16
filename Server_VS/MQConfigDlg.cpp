#include "MQConfigDlg.h"

MQConfigDlg::MQConfigDlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::FramelessWindowHint);
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.SetAdminBtn, SIGNAL(clicked()), this, SLOT(SetAdmin()));
	connect(ui.SetPasswordBtn, SIGNAL(clicked()), this, SLOT(SetPassword()));
	connect(ui.SetURLBtn, SIGNAL(clicked()), this, SLOT(SetURL()));
}

MQConfigDlg::~MQConfigDlg()
{
}

void MQConfigDlg::slot_minWindow()
{
	this->showMinimized();
}

void MQConfigDlg::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void MQConfigDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void MQConfigDlg::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

void MQConfigDlg::SetAdmin()
{
	g_SimpleProducer.UserName = ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_ZDH.UserName = ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_sh.UserName = ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();

	g_SimpleProducer.start();
	g_SimpleProducer_ZDH.start();
	g_SimpleProducer_sh.start();
}

void MQConfigDlg::SetPassword()
{
	g_SimpleProducer.Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_ZDH.Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_sh.Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	
	g_SimpleProducer.start();
	g_SimpleProducer_ZDH.start();
	g_SimpleProducer_sh.start();
}

void MQConfigDlg::SetURL()
{
	g_SimpleProducer.brokerURI = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_ZDH.brokerURI = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();
	g_SimpleProducer_sh.brokerURI = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();

	g_SimpleProducer.start();
	g_SimpleProducer_ZDH.start();
	g_SimpleProducer_sh.start();
}