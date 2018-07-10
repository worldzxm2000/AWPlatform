#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include<qdatetime.h>
typedef int(*Fun)(int, int, string*); //���庯��ָ��,int add(int a,int b);   
typedef LRESULT(*Char2Json)(LPCSTR buff, int len, QJsonObject &json);//�������ݺ���
typedef int(*GetServiceTypeID_Lib)();//��ȡҵ������
typedef QString(*GetServiceTypeName_Lib)();//��ȡҵ������
typedef int(*GetPort_Lib)();//��ȡ�˿�
typedef QString(*GetVersionNo_Lib)();//��ȡ�汾��

const int DataBuffSize = 4 * 1024;
extern 	SimpleProducer g_SimpleProducer;
typedef void* HLIB;		//��̬����
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//���ν����ֽ�
	//char totleBuff[1024*4];//��������ֽ�
	char buffer[DataBuffSize]; //�ܽ����ֽ�
	int BufferLen;  //���ν����ֽڴ�С
	//int TotalBufferLen;//�ܽ����ֽ���
	int operationType; // ��¼�ص�IO�������� accp��recv
	

}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET socket;  //�ͻ���socekt
	SOCKADDR_IN ClientAddr;  //�ͻ���socekt��ַ
	//int ClientIndex;//�ͻ��˶�Ӧ������
	LPCSTR ClientIP;//�ͻ���IP
	int Port;//�ͻ��˶˿�
	//bool Status;//�ͻ�������״̬
	int Count;//�����ݽ�����
	char Frame[DataBuffSize] = {0};//һ֡����
	int DataCount;//һ֡�������ֽڸ���
   bool IsWholeFrame;//�ж��Ƿ���һ֡����
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//IOCP�нṹ��
typedef struct
{
	HANDLE completionPort;//IO�˿ں�
	HANDLE fatherClass;//�����ַ
}PARAMS,*LPPARAMS;

//ҵ���б�
enum ServiceID
{
	NW=01,//ũί
	TRSF=02,//����ˮ��
	NTXQH=03,//ũ��С����
	JTQX=04,//��ͨ����
	HKQX = 05//��������
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
