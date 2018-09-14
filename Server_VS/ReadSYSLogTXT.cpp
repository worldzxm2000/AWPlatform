#include "ReadSYSLogTXT.h"
#include<qfile.h>
#include<qtextstream.h>
#include "qcoreapplication.h"
#include"qthread.h"
#include"qdebug.h"
ReadSYSLogTXT::ReadSYSLogTXT(QObject *parent)
{
}

ReadSYSLogTXT::ReadSYSLogTXT(QString txtPath)
{
	m_TXTPath = txtPath;
	FlagOver = false;
}
ReadSYSLogTXT::~ReadSYSLogTXT()
{
}

void ReadSYSLogTXT::run()
{
	FlagOver = true;
	QString path= QCoreApplication::applicationDirPath() + "\\Log\\"+m_TXTPath+".txt";
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	QStringList strlist;
	QString line = in.readLine();
	strlist.append(line);
	//读取数据
	while (!line.isNull())
	{
		if (!FlagOver)
			break;
		line = in.readLine();
		strlist.append(line);
	}
	file.close();	
	SendToUI(strlist);
}

void ReadSYSLogTXT::EndThread()
{
	FlagOver = false;
}