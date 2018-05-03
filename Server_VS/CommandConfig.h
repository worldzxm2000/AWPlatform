#pragma once

#include <QObject>

class CommandConfig : public QObject
{
	Q_OBJECT

public:
	CommandConfig(QObject *parent);
	~CommandConfig();
public:
	//¶ÁÈ¡iniÎÄ¼þ
	QStringList LoadCommandIni(int ServiceType);
private:
	QString Path;
};
