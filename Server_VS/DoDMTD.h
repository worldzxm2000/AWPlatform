#pragma once

#include <QObject>
#include<QRunnable>
#include<Windows.h>
class DoDMTD : public QObject,public QRunnable
{
	Q_OBJECT

public:
	DoDMTD(QObject *parent);
	~DoDMTD();
private:
	void run();
public:
	//�ļ�·��
	QString m_path;
};
