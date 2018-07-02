#include "ReadSYSLogTXT.h"
#include<qfile.h>
#include<qtextstream.h>
#include "qcoreapplication.h"
ReadSYSLogTXT::ReadSYSLogTXT(QObject *parent)
	: QObject(parent)
{
}

ReadSYSLogTXT::ReadSYSLogTXT()
{

}
ReadSYSLogTXT::~ReadSYSLogTXT()
{
}

void ReadSYSLogTXT::run()
{
	QString path= QCoreApplication::applicationDirPath() + "\\Log\\SYSLog.txt";
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