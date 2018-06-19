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

   static void LogMsgOutput(QString ErrMSG);

signals:
   void test(int x);
};
