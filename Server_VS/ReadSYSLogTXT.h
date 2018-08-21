#pragma once

#include <QObject>
#include<QThread>
class ReadSYSLogTXT :public QThread
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
	bool FlagOver;
signals:
	//将数据返回给主线程
	void SendToUI(QStringList strlist);
public slots:
    //强制结束线程
	void EndThread();
};
