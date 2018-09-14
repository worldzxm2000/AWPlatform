#pragma once

#include <QObject>
#include<qmutex.h>
#include <QFile>  
#include <QApplication>  
#include <iostream>  
#include <cstdlib>  
#include <QString>  
#include <QTextStream>  
#include <QDateTime>  

class LogWrite : public QObject
{
	Q_OBJECT

public:
	LogWrite(QObject *parent);
	LogWrite();
	~LogWrite();

	//д��ϵͳ��־
   static void SYSLogMsgOutPut(QString ErrMSG);
   static void DataLogMsgOutPut(QString MSG);
   static void WarningLogMsgOutPut(QString ErrMSG);

};
