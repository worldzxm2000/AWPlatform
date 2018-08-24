#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include<qdatetime.h>
typedef int(*Fun)(int, int, string*); //���庯��ָ��,int add(int a,int b);   
typedef LRESULT(*Char2Json)(QString &buff,QJsonObject &json);//�������ݺ���
typedef int(*GetServiceTypeID_Lib)();//��ȡҵ������
typedef QString(*GetServiceTypeName_Lib)();//��ȡҵ������
typedef int(*GetPort_Lib)();//��ȡ�˿�
typedef QString(*GetVersionNo_Lib)();//��ȡ�汾��
extern 	SimpleProducer g_SimpleProducer;
extern SimpleProducer g_SimpleProducer_ZDH;
const int DataBuffSize = 4 * 1024;
typedef void* HLIB;		//��̬����
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//���ν����ֽ�
	char buffer[DataBuffSize]; //�ܽ����ֽ�
	int BufferLen;  //���ν����ֽڴ�С
	int operationType; // ��¼�ص�IO�������� accp��recv
	

}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET Socket;  //�ͻ���socekt
	QString ClientIP;//�ͻ���IP
	int Port;//�ͻ��˶˿�
	int Count;//�����ݽ�����
	QString Frame;//һ֡����
	QString StationID;//̨վ��
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//IOCP�нṹ��
typedef struct
{
	HANDLE CompletionPort;//IO�˿ں�
	HANDLE Parent;//�����ַ
}PARAMS,*LPPARAMS;


//ҵ���б�
enum ServiceID
{
	NW = 01,//ũί
	JTQX = 02,//��ͨ����
	NTXQH = 03,//ũ��С����
	TRSF = 04,//����ˮ��
	HKQX = 05,//��������
	TRSF_NM = 9,//����ˮ������
	TRSF_XJ=10//����ˮ���½�
};

//���󷵻�ֵ
enum ErrorMSG
{
	SOCKET_INIT_ERROR=10300,//SOCKET��ʼ��ʧ��
	IOCP_INIT_ERROR=10301,//IOCP����ʧ��
	SOCKET_BIND_ERROR=10302,//SOCKET��ʧ��
	SOCKET_LISTEN_ERROR=10303,//SOCKET����ʧ��
	MQ_SEND_ERROR=10304//��Ϣ�м����������ʧ��
};

//��վ����Ϣ
typedef struct
{
	//IP��
	QString IP;
	//�˿ں�
	int Port;
	//socket��
	SOCKET SocketID;
	//��վ��
	QString StationID;
	//��������ʱ��
	QDateTime LatestTimeOfHeartBeat;
	//״̬
	bool Online;
	//��¼ʱ��
	QDateTime LoginTime;
} CLIENTINFO, *LPCLIENTINFO;

//�ն�����
enum OPCommand
{
	NONE = -1,
	BASEINFO = 231,
	DATETIME = 232,
	ID = 233,
	LAT = 234,
	LONGITUDE = 235,
	ALT=236,
	CFSET=237,
	CAPTIME=238,
	CAPINTERVAL=239,
	SNAPSHOT=2310,
	RESET=2311,
	UPDATE=2312
};

#endif // PARAM_H
