#ifndef IOCP_H
#define IOCP_H

#endif // IOCP_H
#include<QObject>
#include"param.h"
#include<Windows.h>
#include<qvector.h>
#include<qthread.h>
#include<QRunnable>
#include<QString>
#include<QJsonObject>

using namespace std;
class IOCP;
//extern IOCP *pIocp;

struct pParam
{
	HANDLE HandleIOCP;
	HANDLE HandleClass;
};
class  IOCP:public QObject,public QRunnable
{

    Q_OBJECT
    QThread listenthread;
public:
    IOCP();
    ~IOCP();
	Char2Json func_Char2Json;
protected:
    void run();
public:
    //设置监听号
    void SetListenedPort(int port);
    //开启监听Socket
    void StartSever(int port);
    //结束监听socket
    void EndListenSocket(int port);
    //存储客户端
    vector < PER_HANDLE_DATA* > clientGroup;
	//停止监听
	void Stop();
	//测试
	//ceshi
	void SendSocket();
    //通知信号
    FacilityID facilityID;
	//返回运行状态
	//true：运行
	//false:停止
	bool GetStatus();
private:
	//获取区站号
	bool bIsGetStationID;
	//服务器端
	SOCKET srvSocket;
	//存放Socket数组
	QVector<SOCKET> Sockets;
	//创建完成端口号
	HANDLE completionPort;
	//创建线程个数
	int iThreadsCount;
    //IOCP处理线程
    static unsigned __stdcall ServerWorkThread(LPVOID pParam);
    //处理设备发送数据
	static void UnboxData(LPPER_IO_DATA perIOData, u_short len, LPPER_HANDLE_DATA PerHandleData, IOCP *P);
    //加载DLL
    LRESULT AddDll(char* dllpath);
    // 端口号
    int m_port;
    //监听启动/结束
    bool bIsListened;
    //信号量
signals:
    //线程状态信号
    void GetStatus(int result);
	//发送错误信息
	void NoticfyServerError(int errorMSG);
	//数据通知
	void NoticfyServerUpdateUI(QString ServiceTypeID,
		QString StationID,
		QString ObserveTime,
		int count,
		bool Connected,
		QString IP,
		int Port,
		int Socket);
	//新设备连接信号
	void NoticfyUINewClient(QString IP, int Port, int m_port, int socketNo);
	//终端操作命令信号
	void NoticfyServerOperateStatus(int Result);
	//终端操作命令返回值
	void NoticfyServerRecvValue(QJsonObject RecvJson);
	void NoticfyServerRecvValue(QJsonObject RecvJson,bool IsComm);
	//第一次设备连接发送ID获取值
	void NoticfyServerNewConnectionStationID(QJsonObject RecvJson);
	//心跳处理
	void NoticfyServerHB(int Socket);
    //线程操作信号
    void operate();
private slots:
    //监听处理线程
};

