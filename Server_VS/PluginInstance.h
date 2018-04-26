#pragma once

#include <QObject>

class PluginInstance : public QObject
{
	Q_OBJECT

public:
	PluginInstance(QObject *parent);
	~PluginInstance();
};

typedef PluginInstance *(*START_PLUGIN_FUN)();
typedef void(*STOP_PLUGIN_FUN)();