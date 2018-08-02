#pragma once

#include <QObject>
#include <QWidget>
#include<QLibrary>
#include<QThreadPool>
#include"IOCP.h"
#include<qmap.h>
#include"qtimer.h"
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT(QWidget *parent);
	~EHT();
public:
	//���ض�̬���ӿ�
	LRESULT LoadLib(QString Lib_Path);
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
	//��ȡ�豸Socket��
	unsigned int GetSocket(QString StationID);
	//��ȡҵ������
	QString GetAttribute();
	//������ݽ���
	Char2Json GetDataFunc();
	//��ʼ���м���
	void Run(QThreadPool &ThreadPool);
	//�������м���
	void Stop();
	//��ȡ����״̬
	bool IsRun();
	//��ȡ���ӿͻ�������
	QList<CLIENTINFO> Clients;
private:
	//��ʼ��IOCP
	void InitIOCP();
	//����״̬
	bool m_IsRun;
	//�����߳�
	IOCP *pIOCP;
	//Lib������
	QLibrary m_Lib;
	//�汾��
	QString m_Vesion;
	//�������IP��
	QString m_IP;
	//�豸����Socket
	unsigned int m_Socket;
	//��������˿ں�
	int m_Port;
	//ҵ������
	int m_ServiceID;
	//ҵ������
	QString m_ServiceName;
	//����
	QString m_Attribute;
	//���ݽ���
	Char2Json m_DataFunc;
	//SIM���Ŷ�Ӧ��վ��
	QMap<QString, QString> SIM2Staion;
	//���˿��Ƿ�Ϸ�
	bool IsLegallyPort(int Port);
	//��ȡSIM���������ļ���ת����վ��v
	void Convert2StationID();
	//�Զ���ʱʱ��
	QTimer *SetTimeTimer;
	//�����ж�
	QTimer *OffLineTimer;
private slots:
    //�Զ��������
    void Disconnect();
    //��ʱ����
    void SetTime();
    //����֪ͨ
	void OffLineSlot(unsigned int CltSocket);
	//�µ�����(�۲����ݻ�����������)
	void NewDataSlot(QString StationID, QString IP, int Port, unsigned int CltSocket);
	//������Ϣ
	void GetErrorSlot(int ErrorMSG);
	//�ն˲���ָ��
	void OperationResultSlot(QString Value, int SrvPort, QString StationID);
	void OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID);
	void OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID);
signals:
	 //UI��¼ʱ��
	 void LoginTimeSignal(int SrvPort, QString Station);
	 //UI�豸������Ϣ
	 void OnLineSignal(QString SrvName,QString StationID, QDateTime LastTime, QDateTime LoginTime);
	 //UI�豸������Ϣ
	 void OffLineSignal(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime);
};
