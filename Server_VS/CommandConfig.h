#pragma once

#include <QObject>

class CommandConfig : public QObject
{
	Q_OBJECT

public:
	CommandConfig(QObject *parent);
	~CommandConfig();
public:
	//��ȡini�ļ�
	QStringList LoadCommandIni(int ServiceType);
private:
	QString Path;
};
