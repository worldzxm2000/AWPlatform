#include "LogWrite.h"
#include"qdir.h"
QMutex mutex;//��־���뻥����  
LogWrite::LogWrite(QObject *parent)
	: QObject(parent)
{
}

LogWrite::LogWrite()
{

}
LogWrite::~LogWrite()
{
}


void LogWrite::SYSLogMsgOutPut(QString ErrMSG)
{
	mutex.lock();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	QString fileName = QCoreApplication::applicationDirPath() + "\\Log";
	QDir dir(fileName);
	if (!dir.exists())
		dir.mkpath(fileName);//�����༶Ŀ¼
	fileName += "\\SYSLog.txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
	}
	QTextStream in(&file);
	in << current_date << " " << ErrMSG<<"\r\n";
	file.close();
	mutex.unlock();
}

void LogWrite::DataLogMsgOutPut(QString MSG)
{
	mutex.lock();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	QString fileName = QCoreApplication::applicationDirPath() + "\\Log";
	QDir dir(fileName);
	if (!dir.exists())
		dir.mkpath(fileName);//�����༶Ŀ¼
	fileName += "\\DataLog.txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
	}
	QTextStream in(&file);
	in << current_date << " " << MSG << "\r\n";
	file.close();
	mutex.unlock();
}

void LogWrite::WarningLogMsgOutPut(QString ErrMSG)
{
	mutex.lock();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	QString fileName = QCoreApplication::applicationDirPath() + "\\Log";
	QDir dir(fileName);
	if (!dir.exists())
		dir.mkpath(fileName);//�����༶Ŀ¼
	fileName += "\\WarningLog.txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
	}
	QTextStream in(&file);
	in << current_date <<"\r\n"<< ErrMSG<<"\r\n";
	file.close();
	mutex.unlock();
}