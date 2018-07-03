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
protected:
	void run();
private:
	QString m_TXTPath;
signals:
	void SendToUI(QStringList strlist);
};
