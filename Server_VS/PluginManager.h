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
	//��þ��
	static PluginManager &GetInstance();
	//���ز��
	PER_PLUGIN_DATA Load(LPCSTR strName, int &errCode);
	//ж�ز��
	void UnLoad(LPCSTR strName);
	//������ж�̬���ӿ�
   vector <PluginInstance *> GetAllPlugins();
private:
	//����DLL
	bool LoadLib(LPCSTR LibPath, LPCSTR LibName);
	//ͨ��·����ȡDLL����
    bool Path2Name(LPCSTR LibPath, LPCSTR LibName);
	//��̬����
	HLIB m_hDynLib;
	//��̬������
	char* m_pszLibName;

	//������ݵ�����
	vector<LPPER_PLUGIN_DATA> m_vecPlugins;
};
