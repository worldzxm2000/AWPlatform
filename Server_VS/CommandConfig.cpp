#include "CommandConfig.h"
#include<QSettings>
#include"param.h"
CommandConfig::CommandConfig(QObject *parent)
	: QObject(parent)
{
}

CommandConfig::~CommandConfig()
{
}


QStringList CommandConfig::LoadCommandIni(int ServiceType)
{
	QSettings configIniRead("Command.ini", QSettings::IniFormat);
	QStringList list;
	switch (ServiceType)
	{
	case HKQX:
	{
		int Count = configIniRead.value("/HKQX/COMMCount").toInt();
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/HKQX/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
			break;
	}
	case TRSF:
	{
		int Count = configIniRead.value("/TRSF/COMMCount").toInt();
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/TRSF/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	default:
		break;
	}
	return list;
}