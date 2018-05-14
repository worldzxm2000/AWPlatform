#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include<qdatetime.h>
typedef int(*Fun)(int, int, string*); //定义函数指针,int add(int a,int b);   
typedef LRESULT(*Char2Json)(LPCSTR buff, int len, QJsonObject &json);//解析数据函数
typedef int(*GetServiceTypeID)();//获取业务类型
typedef QString(*GetServiceTypeName)();//获取业务名称


const int DataBuffSize = 4 * 1024;
extern 	SimpleProducer g_SimpleProducer;
typedef void* HLIB;		//动态库句柄
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//单次接收字节
//	char perBuff[1024];//单次接收字节;
	char buffer[DataBuffSize]; //总接收字节
	int BufferLen;  //单次接收字节大小
	//int TotalBufferLen;//总接受字节数
	int operationType; // 记录重叠IO操作类型 accp或recv
}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET socket;  //客户端socekt
	SOCKADDR_IN ClientAddr;  //客户端socekt地址
	int ClientIndex;//客户端对应索引号
	LPCSTR ClientIP;//客户端IP
	int Port;//客户端端口
	bool Status;//客户端连接状态
	int count;//数据接收量
	LPCSTR ServiceTypeID;//服务类型
	LPCSTR StationID;//区站号
	LPCSTR ObserveTime;//观察时间
	bool Connected;//设备状态
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	HANDLE completionPort;
	HANDLE fatherClass;
}PARAMS,*LPPARAMS;
//业务编号
enum FacilityID
{
	AirforceFacilityID = 1031,
	AgricultureFacilityID = 1032
};

enum ServiceID
{
	NW=01,//郑州农田管理
	TRSF=02,//土壤水分
	HKQX = 05//航空气象
};
typedef struct
{
	char data[1024 * 8];
	int len;
} Recv_Data;
//客户端socket信息
typedef struct
{
	
	//IP号
	QString IP;
	//端口号
	int Port;
	//socket号
	SOCKET SocketID;
	//区站号
	int StationID;
	//最新心跳时间
	QDateTime LatestTimeOfHeartBeat;
} CLIENTINFO, *LPCLIENTINFO;

//终端命令
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
