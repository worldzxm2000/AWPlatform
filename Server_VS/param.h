#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include<qdatetime.h>
typedef int(*Fun)(int, int, string*); //定义函数指针,int add(int a,int b);   
typedef LRESULT(*Char2Json)(LPCSTR buff, int len, QJsonObject &json);//解析数据函数
typedef int(*GetServiceTypeID_Lib)();//获取业务类型
typedef QString(*GetServiceTypeName_Lib)();//获取业务名称
typedef int(*GetPort_Lib)();//获取端口
typedef QString(*GetVersionNo_Lib)();//获取版本号

const int DataBuffSize = 4 * 1024;
extern 	SimpleProducer g_SimpleProducer;
typedef void* HLIB;		//动态库句柄
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//单次接收字节
	//char totleBuff[1024*4];//总体接收字节
	char buffer[DataBuffSize]; //总接收字节
	int BufferLen;  //单次接收字节大小
	//int TotalBufferLen;//总接受字节数
	int operationType; // 记录重叠IO操作类型 accp或recv
	

}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET socket;  //客户端socekt
	SOCKADDR_IN ClientAddr;  //客户端socekt地址
	//int ClientIndex;//客户端对应索引号
	LPCSTR ClientIP;//客户端IP
	int Port;//客户端端口
	//bool Status;//客户端连接状态
	int Count;//总数据接收量
	char Frame[DataBuffSize] = {0};//一帧数据
	int DataCount;//一帧数据中字节个数
   bool IsWholeFrame;//判断是否是一帧数据
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//IOCP中结构体
typedef struct
{
	HANDLE completionPort;//IO端口号
	HANDLE fatherClass;//父类地址
}PARAMS,*LPPARAMS;

//业务列表
enum ServiceID
{
	NW=01,//农委
	TRSF=02,//土壤水分
	NTXQH=03,//农田小气候
	JTQX=04,//交通气象
	HKQX = 05//航空气象
};

//区站号信息
typedef struct
{
	//IP号
	QString IP;
	//端口号
	int Port;
	//socket号
	SOCKET SocketID;
	//区站号
	QString StationID;
	//最新心跳时间
	QDateTime LatestTimeOfHeartBeat;
	//状态
	bool Online;
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
