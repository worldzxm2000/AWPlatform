#ifndef IOCP_H
#define IOCP_H

#endif // IOCP_H
#include<QWidget>
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
struct pParam
{
	HANDLE HandleIOCP;
	HANDLE HandleClass;
};
class  IOCP:public QObject,public QRunnable
{

    Q_OBJECT

public:
    IOCP();
    ~IOCP();
	Char2Json func_Char2Json;
protected:
    void run();
public:
    //设置监听号
    void SetListenedPort(int port,QString IP);
	//停止监听
	void Stop();
	//获取服务端Socket号
	int GetSocket();
private:
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
    // 端口号
    int m_port;
	//IP
	QString m_IP;
    //信号量
signals:
	//发送错误信息
	void NoticfyServerError(int errorMSG);
	//数据通知
	void NoticfyServerUpdateUI(
		QString StationID,
		QString ObserveTime,
		int count,
		bool Connected,
		QString IP,
		int Port,
		int Socket,
		int SrvPort);
	//新设备连接信号
	void NoticfyUINewClient(QString IP, int Port, int m_port, int socketNo);
	//终端操作命令信号
	void NoticfyServerOperateStatus(int Result);
	//终端操作命令返回值
	void NoticfyServerRecvValue(QJsonObject RecvJson);
	void NoticfyServerRecvValue(QJsonObject RecvJson,bool IsComm);
	//心跳处理
	void NoticfyServerHB(QString IP,int Port,int SrvPort,int CltSocket,QString StationID,QString ServiceTypeID);
	//离线通知
	void NoticfyOffLine(int SrvPort,int CltSocket);
};

