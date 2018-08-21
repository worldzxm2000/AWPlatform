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
    void SetListenedPort(int Port, QString IP, int SrvID);
	//停止监听
	void Stop();
	//获取服务端Socket号
	int GetSocket();
private:
	//服务器端
	SOCKET m_SrvSocket;
	//存放Socket数组
	QVector<SOCKET> Sockets;
	//创建完成端口号
	HANDLE m_CompletionPort;
	//创建线程个数
	int m_ThreadsCount;
    //IOCP处理线程
    static unsigned __stdcall ServerWorkThread(LPVOID pParam);
    //处理设备发送数据
    void UnboxData(LPPER_IO_DATA perIOData, u_short len, LPPER_HANDLE_DATA PerHandleData);
    // 端口号
    int m_Port;
	//IP
	QString m_IP;
	//业务ID
	int m_SrvID;
    //信号量
signals:
	void WebCommandSignal();
	//发送错误信息
	void GetErrorSignal(int errorMSG);
	//数据通知(观测数据或者心跳数据)
	void NewDataSignal(QString StationID,QString IP,int Port, unsigned int Socket);
	//新设备连接信号
	void NewConnectionSignal(QString IP, int Port, int m_Port, unsigned int Socket);
	//终端操作命令信号
	void NoticfyServerOperateStatus(int Result);
	//终端操作命令返回值dd
	void OperationResultSignal(QString Value,int SrvPort,QString StationID);
	void OperationResultSignal(QString Value1, QString Value2, int SrvPort, QString StationID);
	void OperationResultSignal(QString Command, QString Value1, QString Value2, QString Value3, QString Value4, int SrvPort, QString StationID);
	//离线通知
	void OffLineSignal(unsigned int CltSocket);
	//发送至消息中间件
	void SendToActiveMQSignal(QJsonObject Json);
};

