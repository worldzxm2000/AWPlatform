#pragma once

#include <QObject>
#include<qrunnable.h>
class ReadSYSLogTXT : public QObject,public QRunnable
{
	Q_OBJECT

public:
	ReadSYSLogTXT(QObject *parent);
	ReadSYSLogTXT(QString txtPath);
	~ReadSYSLogTXT();
	void SetFlagOver();
protected:
	void run();
private:
	QString m_TXTPath;
	bool FlagOver;
	
signals:
	void SendToUI(QStringList strlist);
};
