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

   static void LogMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
   void test(int x);
};
