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
	//ÎÄ¼þÂ·¾¶
	QString m_path;
};
