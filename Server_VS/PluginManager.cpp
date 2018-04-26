#include "PluginManager.h"

PluginManager::PluginManager(QObject *parent)
	: QObject(parent)
{
}

PluginManager::PluginManager()
{

}
PluginManager::~PluginManager()
{
}
PluginManager &PluginManager::GetInstance()
{
	static PluginManager instance;
	return instance;
 }

PER_PLUGIN_DATA PluginManager::Load(LPCSTR strName, int &errCode)
{
	PER_PLUGIN_DATA pPerPluginData;
	pPerPluginData.Name = "Char2Json";
	pPerPluginData.pPlugin = NULL;
	bool result = this->LoadLib(strName, pPerPluginData.Name);
	if (false == result)
	{
		errCode = -1;
		return pPerPluginData;
	}
	//判断数组是否含有该动态库
	for (vector<LPPER_PLUGIN_DATA>::const_iterator iter = m_vecPlugins.begin(); iter != m_vecPlugins.end(); iter++)
	{
		//已经添加该动态库，则返回
		if (0 == strcmp(((LPPER_PLUGIN_DATA)*iter)->Name, pPerPluginData.Name))
		{
			errCode = -2;
			return pPerPluginData;
		}
	}
	//创建
	START_PLUGIN_FUN pFun = (START_PLUGIN_FUN)GetProcAddress((HMODULE)m_hDynLib, pPerPluginData.Name);
	int readlen = 0;
	pPerPluginData.pPlugin = pFun();

	// pPerPluginData.pPlugin->Bytes2Json(NULL,0,NULL,NULL,readlen);
	m_vecPlugins.push_back(new PER_PLUGIN_DATA(pPerPluginData));
	return pPerPluginData;
	errCode = 1;
	//将加载的动态库添加到数组中
}

//加载动态库
bool PluginManager::LoadLib(LPCSTR LibPath, LPCSTR LibName)
{
	if (!Path2Name(LibPath, LibName))
		return false;
	wchar_t wLibPath[1024];
	mbstowcs(wLibPath, LibPath, strlen(LibPath) + 1);
	m_hDynLib = LoadLibrary(wLibPath);
	if (NULL == m_hDynLib)
	{
		FreeLibrary((HINSTANCE)m_hDynLib);
		return true;
	}
	return false;
}

//通过路径找到动态库名
bool PluginManager::Path2Name(LPCSTR LibPath, LPCSTR LibName)
{
	string path(LibPath);
	string name;
	//字符串长度
	int size = 0;
	int pos = 1;
	int i = 0;
	//查找名称
	while (pos)
	{

		size = path.length();
		pos = path.find('/', i);
		if (pos<0)
		{
			name = path;
			break;
		}
		path = path.substr(pos+1, size);
	}
	//判断名称里面是否含有.dll
	if (name.find(".dll"))
	{
		LibName = name.c_str();
		return true;
	}
	LibName = NULL;
	return  false;
}