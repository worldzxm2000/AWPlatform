#pragma once
#include"param.h"
#include <QObject>
#include<vector>
#
using namespace std;
class PluginInstance;
class PluginManager : public QObject
{
	Q_OBJECT

public:
	PluginManager();
	PluginManager(QObject *parent);
	~PluginManager();
	//获得句柄
	static PluginManager &GetInstance();
	//加载插件
	PER_PLUGIN_DATA Load(LPCSTR strName, int &errCode);
	//卸载插件
	void UnLoad(LPCSTR strName);
	//获得所有动态链接库
   vector <PluginInstance *> GetAllPlugins();
private:
	//加载DLL
	bool LoadLib(LPCSTR LibPath, LPCSTR LibName);
	//通过路径获取DLL名称
    bool Path2Name(LPCSTR LibPath, LPCSTR LibName);
	//动态库句柄
	HLIB m_hDynLib;
	//动态库名称
	char* m_pszLibName;

	//存放数据的数组
	vector<LPPER_PLUGIN_DATA> m_vecPlugins;
};
