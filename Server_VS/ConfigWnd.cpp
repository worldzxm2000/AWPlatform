﻿#include "ConfigWnd.h"
#include <QtNetwork>
#include<Windows.h>
#include<qmessagebox.h>
using namespace std;
ConfigWnd::ConfigWnd(QWidget *parent)
{
	ui.setupUi(this);
	
	GetLocalIP();
	ui.IPEdit->setText(m_IP);
	ui.PortEdit->setText("1031");
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

void ConfigWnd::on_SetBtn_clicked()
{
	bool ok;
	m_Port = ui.PortEdit->text().toInt(&ok,10);
	m_IP = ui.IPEdit->text();
	this->close();
}
