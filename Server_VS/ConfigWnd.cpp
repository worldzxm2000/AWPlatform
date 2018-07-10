#include "ConfigWnd.h"
//#include <QtNetwork>
#include<Windows.h>
#include<qmessagebox.h>
using namespace std;
ConfigWnd::ConfigWnd(QWidget *parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint);
	GetLocalIP();

}
void ConfigWnd::GetLocalIP()
{
	string strResult;
	WSADATA wsaData;
	char name[155];
	char *ip;
	PHOSTENT hostinfo;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{ 
				//这些就是获得IP的函数
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	m_IP=QString("%1").arg(ip);
}


ConfigWnd::~ConfigWnd()
{

}
void ConfigWnd::SetServicePort(int Port)
{
	m_Port = Port;
	ui.PortEdit->setText(QString::number(m_Port));
}
void ConfigWnd::on_SetBtn_clicked()
{
	bool ok;
	m_Port = ui.PortEdit->text().toInt(&ok,10);
	m_IP = ui.IPEdit->text();
	m_Attribute = ui.AttrTextEdit->toPlainText();
	this->accept();
}

int ConfigWnd::exec()
{
	if (!DialogMode)
	{
		ui.PortEdit->setEnabled(false);
		ui.IPEdit->setEnabled(false);
		ui.AttrTextEdit->setEnabled(false);
		ui.IPEdit->setText(m_IP);
		ui.PortEdit->setText(QString::number(m_Port));
		ui.AttrTextEdit->setPlainText(m_Attribute);
		ui.SetBtn -> setVisible(false);
	}
	else
	{
		ui.IPEdit->setText(m_IP);
		ui.PortEdit->setText(QString::number(m_Port));
	}
	return QDialog::exec();
}