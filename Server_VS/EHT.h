#pragma once

#include <QObject>
#include <QWidget>
#include"IOCP.h"
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT(QWidget *parent);
	~EHT();
public:
	IOCP *m_pIOCP;
signals:
	//ÀëÏßÍ¨Öª
	void NoticfyOffLine(int no1,int no2);
};
