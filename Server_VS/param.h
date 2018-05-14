#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include<qdatetime.h>
typedef int(*Fun)(int, int, string*); //���庯��ָ��,int add(int a,int b);   
typedef LRESULT(*Char2Json)(LPCSTR buff, int len, QJsonObject &json);//�������ݺ���
typedef int(*GetServiceTypeID)();//��ȡҵ������
typedef QString(*GetServiceTypeName)();//��ȡҵ������


const int DataBuffSize = 4 * 1024;
extern 	SimpleProducer g_SimpleProducer;
typedef void* HLIB;		//��̬����
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//���ν����ֽ�
//	char perBuff[1024];//���ν����ֽ�;
	char buffer[DataBuffSize]; //�ܽ����ֽ�
	int BufferLen;  //���ν����ֽڴ�С
	//int TotalBufferLen;//�ܽ����ֽ���
	int operationType; // ��¼�ص�IO�������� accp��recv
}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET socket;  //�ͻ���socekt
	SOCKADDR_IN ClientAddr;  //�ͻ���socekt��ַ
	int ClientIndex;//�ͻ��˶�Ӧ������
	LPCSTR ClientIP;//�ͻ���IP
	int Port;//�ͻ��˶˿�
	bool Status;//�ͻ�������״̬
	int count;//���ݽ�����
	LPCSTR ServiceTypeID;//��������
	LPCSTR StationID;//��վ��
	LPCSTR ObserveTime;//�۲�ʱ��
	bool Connected;//�豸״̬
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	HANDLE completionPort;
	HANDLE fatherClass;
}PARAMS,*LPPARAMS;
//ҵ����
enum FacilityID
{
	AirforceFacilityID = 1031,
	AgricultureFacilityID = 1032
};

enum ServiceID
{
	NW=01,//֣��ũ�����
	TRSF=02,//����ˮ��
	HKQX = 05//��������
};
typedef struct
{
	char data[1024 * 8];
	int len;
} Recv_Data;
//�ͻ���socket��Ϣ
typedef struct
{
	
	//IP��
	QString IP;
	//�˿ں�
	int Port;
	//socket��
	SOCKET SocketID;
	//��վ��
	int StationID;
	//��������ʱ��
	QDateTime LatestTimeOfHeartBeat;
} CLIENTINFO, *LPCLIENTINFO;

//�ն�����
enum Command
{
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
