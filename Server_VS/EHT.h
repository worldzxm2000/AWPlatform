#pragma once

#include <QObject>
#include <QWidget>
#include<QLibrary>
#include<QThreadPool>
#include"IOCP.h"
#include<QMap>
#include<QTimer>
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT();
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
	bool Run(QThreadPool &ThreadPool);
	//�������м���
	bool Stop();
	//��ȡ����״̬
	bool IsRun();
	//��ȡ���ӿͻ�������
	QList<CLIENTINFO> Clients;
	//����COMMANDָ��
	void SendCommand(int cmm,QString StationID, QString Params1, QString Params2);
	//��ȡ�����豸����
	int GetOnlineCount();
	//���豸���ƴ���
	void OpenCtrlWnd(QString StationID, QString DeviceID);
private:
	//ֲ�����´���ʱ��
	QTimer *ReHandleZB_IMAGE;
	QTimer *ReHandleZB_XML;
	QTimer *ReHandleZB_TXT;
	//�Ƿ����JPG�ļ�
	bool IsExistImage;
	//�Ƿ����TXT
	bool IsExistTXT;
	//��ʼ��IOCP
	void InitIOCP();
	//��Ϣ�м����������
	void ReConnectActiveMq();
	//������ʱ��
	QTimer *ReconnectTimer;
	//����״̬
	bool b_IsReconnect;
	//����״̬
	bool b_IsRunMQ;
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
	//��ʱ����
	SetTime_Lib func_SetTime_Lib;
	//�豸���ƴ���
	GetControlWidget_Lib func_GetControlWidget;
	//��ʾ����ֵ
	SetValueToControlWidget_Lib func_SetValueToControlWidget;
	//�ն�����
	SetCommand_Lib func_SetCommand;
private slots:
    //�Զ��������
    void Disconnect();
    //��ʱ����
    void SetTime();
	//����MQ����
	void Reconnect();
    //����֪ͨ
	void OffLineSlot(unsigned int CltSocket);
	//�µ�����(�۲����ݻ�����������)
	void NewDataSlot(QString StationID, QString IP, int Port, unsigned int CltSocket,QString DeviceID);
	void NewDataSlot(QString StationID, QString IP, int Port, int File, unsigned int CltSocket,QString DeviceID);
	//������Ϣ
	void GetErrorSlot(int ErrorMSG);
	//�ն˲���ָ��
	void OperationResultSlot(QString Value, int SrvPort, QString StationID, QString DeviceID);
	void OperationResultSlot(QString Value1, QString Value2, int SrvPort, QString StationID, QString DeviceID);
	void OperationResultSlot(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID, QString DeviceID);
	//ͼƬ����
	void MoveImageToDesAddr();
	//�ı�����
	void MoveTXTToDesAddr();
	//XML����
	void MoveXMLToDesAddr();
signals:
	 //UI��¼ʱ��
	 void LoginTimeSignal(int SrvPort, QString Station);
	 //UI�豸������Ϣ
	 void OnLineSignal(QString SrvName,QString StationID, QDateTime LastTime, QDateTime LoginTime,QString DeviceID);
	 //UI�豸������Ϣ
	 void OffLineSignal(QString SrvName, QString StationID, QDateTime LastTime, QDateTime LoginTime,QString DeviceID);
	 //UI��ʾ�ն˷���ֵ
	 void SendWarningInfoToUI(QString Result);
	 //������Web
	void  SendToWebServiceSignal(QJsonObject Json);
};
