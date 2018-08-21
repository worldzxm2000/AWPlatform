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
	//�����ݷ��ظ����߳�
	void SendToUI(QStringList strlist);
public slots:
    //ǿ�ƽ����߳�
	void EndThread();
};
