#pragma once

#include <QObject>
#include<qrunnable.h>
class ReadSYSLogTXT : public QObject,public QRunnable
{
	Q_OBJECT

public:
	ReadSYSLogTXT(QObject *parent);
	ReadSYSLogTXT();
	~ReadSYSLogTXT();
protected:
	void run();
signals:
	void SendToUI(QStringList strlist);
};
