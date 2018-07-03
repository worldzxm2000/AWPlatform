#include "ReadSYSLogTXT.h"
#include<qfile.h>
#include<qtextstream.h>
#include "qcoreapplication.h"
ReadSYSLogTXT::ReadSYSLogTXT(QObject *parent)
	: QObject(parent)
{
}

ReadSYSLogTXT::ReadSYSLogTXT(QString txtPath)
{
	m_TXTPath = txtPath;
}
ReadSYSLogTXT::~ReadSYSLogTXT()
{
}

void ReadSYSLogTXT::run()
{
	QString path= QCoreApplication::applicationDirPath() + "\\Log\\"+m_TXTPath+".txt";
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	QStringList strlist;
	QString line = in.readLine();
	strlist.append(line);
	while (!line.isNull())
	{
		line = in.readLine();
		strlist.append(line);
	}
	file.close();	
	SendToUI(strlist);
}