#pragma once

#include <QObject>
#include <QWidget>
#include<QLibrary>
#include<QThreadPool>
#include"IOCP.h"
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT(QWidget *parent);
	~EHT();
public:
	//�����߳�
	IOCP *pIOCP;
	//���ض�̬���ӿ�
	bool LoadLib(QString Lib_Path);
	//ж�ض�̬���ӿ�
	bool UnloadLib();
	//��ȡ�汾��
	QString GetVesionNo();
	//��ȡҵ��ID
	int GetServiceID();
	//��ȡҵ������
	QString GetServiceName();
	//��ȡIP��
	QString GetIP();
	//��ȡ�˿ں�
	int GetPort();
	//��ȡSocket��
	int GetSocket();
	//��ȡҵ������
	QString GetAttribute();
	//��ʼ���м���
	void Run(QThreadPool &ThreadPool);
protected:
	//Lib������
	QLibrary m_Lib;
	//�汾��
	QString m_Vesion;
	//IP��
	QString m_IP;
	//Socket
	int m_Socket;
	//�˿ں�
	int m_Port;
	//ҵ������
	int m_ServiceID;
	//ҵ������
	QString m_ServiceName;
	//����
	QString m_Attribute;
	//���˿��Ƿ�Ϸ�
	bool IsLegallyPort(int Port);
};
