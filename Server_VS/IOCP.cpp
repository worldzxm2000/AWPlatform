#include "IOCP.h"
#include<process.h>
#include<qmessagebox.h>
#include"LogWrite.h"
#include"Dictionary.h"
#include<qdebug.h>
#include<qthread.h>
#include<qjsondocument.h>
#include<qdir.h>
#include <mswsock.h> 
using namespace std;

IOCP::IOCP()
{
	m_ThreadsCount = 0;
}

IOCP::~IOCP(){}

void IOCP::SetListenedPort(int Port,QString IP,int SrvID)
{
	this->m_Port = Port;
	this->m_IP = IP;
	this->m_SrvID = SrvID;
}

void IOCP::Stop()
{
	int result = -1;
	for (int i = 0; i < m_ThreadsCount; i++)
	{
		// 通知所有的完成端口操作退出  
		result=PostQueuedCompletionStatus(m_CompletionPort, 0, NULL, NULL);
	}
	//断开socket连接
	for (int i = 0; i < Sockets.count(); i++)
	{
		result = shutdown((SOCKET)Sockets.at(i), 2);//先关闭
		result = closesocket(Sockets.at(i));//再断开
	}
	Sockets.clear();
	result = closesocket(m_SrvSocket);
	WSACleanup();
	LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("服务已关闭，端口号为：") + QString::number(m_Port));
}

void IOCP::run()
{
	//初始化WSA    加载socket动态链接库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // 接收Windows Socket的结构信息
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		ErrorMSGSignal(10300);
	}
	m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (NULL == m_CompletionPort)
	{
		ErrorMSGSignal(10301);
	}

	PARAMS pparam;
	pparam.CompletionPort = m_CompletionPort;
	pparam.Parent = (HANDLE)this;

	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);
	m_ThreadsCount = (mySysInfo.dwNumberOfProcessors*2);
	for (int i = 0; i < m_ThreadsCount; ++i)
	{
		HANDLE threadhandle = (HANDLE)_beginthreadex(NULL, 0, ServerWorkThread, &pparam, 0, NULL);
		::ResumeThread(threadhandle);
	}
	//设置socket
	m_SrvSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN  srvAddr;
	//获取本地IP
	LPCSTR  ch;
	QByteArray ba = m_IP.toLatin1();
	ch = ba.data();
	srvAddr.sin_addr.S_un.S_addr = inet_addr(ch);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(m_Port);
	//绑定SOCKET到本机
	int bindResult = ::bind(m_SrvSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == bindResult)
	{
		//Stop();
		ErrorMSGSignal(10302);
		return;
	}
	// 将SOCKET设置为监听模式
	int listenResult = ::listen(m_SrvSocket, SOMAXCONN);
	if (SOCKET_ERROR == listenResult)
	{
		//Stop();
		ErrorMSGSignal(10303);
		return;
	}

	//LPFN_ACCEPTEX




	//accept
	while (1)
	{
		LPPER_HANDLE_DATA PerHandleData = new PER_HANDLE_DATA;;
		SOCKADDR_IN saRemote;
		int RemoteLen = sizeof(saRemote);
		//接收客户端连接
		SOCKET acceptSocket;

		//WSAID_ACCEPTEX
		acceptSocket = accept(m_SrvSocket, (SOCKADDR*)&saRemote, &RemoteLen);
		if (SOCKET_ERROR == (signed)acceptSocket)
		{
			// 接收客户端失败
			ErrorMSGSignal(10311);
			break;
		}
	
		//客户端socket与IOCP关联
		PerHandleData->Socket = acceptSocket;//Sccket号
		PerHandleData->Port = saRemote.sin_port;//端口号
		PerHandleData->Count = 0;//接收个数
        PerHandleData->ClientIP = inet_ntoa(saRemote.sin_addr);	//客户端IP

		//客户端socket绑定IOCP
		CreateIoCompletionPort((HANDLE)(PerHandleData->Socket), m_CompletionPort, (DWORD)PerHandleData, 0);
		//客户端信息
		LPPER_IO_OPERATION_DATA PerIoData = NULL;
		PerIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATEION_DATA));
		ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
		PerIoData->databuff.len = 4 * 1024;
		PerIoData->databuff.buf = PerIoData->buffer;
		PerIoData->operationType = 0;

		//客户端socket添加入客户端数组，通知主程序
		Sockets.push_back(acceptSocket);
		DWORD RecvBytes = 0;
		DWORD Flags = 0;
		WSARecv(PerHandleData->Socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
	}
}

//IOCP线程队列
unsigned IOCP::ServerWorkThread(LPVOID pParam)
{
	try
	{
		LPPARAMS p = (LPPARAMS)pParam;
		HANDLE m_CompletionPort = p->CompletionPort;
		IOCP *pIOCP = (IOCP *)p->Parent;
		DWORD BytesTransferred = 0;
		LPOVERLAPPED IpOverlapped;
		LPPER_IO_DATA PerIoData = NULL;
		LPPER_HANDLE_DATA PerHandleData = NULL;
		DWORD RecvBytes;
		DWORD Flags = 0;
		BOOL bRet = FALSE;
		int nError = -1;
		while (1)
		{
			bRet = GetQueuedCompletionStatus(m_CompletionPort, &BytesTransferred, (PULONG_PTR)&PerHandleData, (LPOVERLAPPED*)&IpOverlapped, INFINITE);
			if (bRet== FALSE)
			{
				nError = GetLastError();
				if (IpOverlapped==NULL)
				{
					if (pIOCP != NULL)
						LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("服务器监听线程意外断开！"));
					break;
				}
			}
			
			PerIoData = (LPPER_IO_DATA)CONTAINING_RECORD(IpOverlapped, PER_IO_DATA, overlapped);
			if (0 == BytesTransferred)
			{
				//客户端主动断开连接
				if (PerHandleData != NULL)
				{
					BOOL bOK= CancelIo((HANDLE)PerHandleData->Socket);
					//更新UI客户端断开连接
					emit pIOCP->OffLineSignal(PerHandleData->Socket);
					for (int i = 0; i <pIOCP->Sockets.size(); i++)
					{
						if (pIOCP->Sockets[i]==PerHandleData->Socket)
						{
							pIOCP->Sockets.erase(pIOCP->Sockets.begin() + i);
							break;
						}
					}
					delete PerHandleData;
					PerHandleData = NULL;
					GlobalFree(PerIoData);
					continue;
				}
				break;
			}
			//线程处理函数
		   pIOCP->UnboxData(PerIoData, BytesTransferred, PerHandleData);

			//为下一个重叠调用建立IO操作
			ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
			memset(PerIoData->buffer, 0, 4 * 1024);
			PerIoData->databuff.len = 4 * 1024;
			PerIoData->databuff.buf = PerIoData->buffer;
			PerIoData->operationType = 0;
			WSARecv(PerHandleData->Socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
		}
		return 0;
	}
	catch (QString  exception)
	{
		return 0;
	}

}

//接收处理数据
void IOCP::UnboxData(LPPER_IO_DATA perIOData, u_short len, LPPER_HANDLE_DATA PerHandleData)
{
	try
	{
		//接收封装统一的Json
		QJsonObject JsonObj;
		//单次接收的数据
		QString RecvStr = QString(QLatin1String(perIOData->buffer,len));
		//去除多余符号
		RecvStr = RecvStr.trimmed();
		PerHandleData->Frame += RecvStr;
		LRESULT pResult = -1;
		//数据内存判断，如果数据内存大于40M说明有错误数据 需要清空内存，否则会造成内存溢
		if (PerHandleData->Frame.length() > 40960)
		{
			PerHandleData->Frame.clear();
			emit ErrorMSGSignal(10305);
			return;
		}
		///**************************解析动态链接库***********************************
	pResult = func_Char2Json(PerHandleData->Frame,JsonObj);
		//判断接收情况
		switch (pResult)
		{
		//1：解析成功
		case 1:
		{
			//接收到数据个数
			int Count = JsonObj.find("DataLength").value().toInt();
			//遍历JSON中数据
			for (int i = 0; i < Count; i++)
			{
				//解析数据数组
				QJsonObject data_json = JsonObj.find(QString::number(i + 1)).value().toObject();
				//获取数据类型（1为观测数据，2位操作数据，3为心跳数据）
				int DataType = data_json.find("DataType").value().toInt();
				switch (DataType)
				{
				case 1://观测数据
				{
					//JSON转成字符串
					QJsonDocument document;
					document.setObject(data_json);
					QByteArray byteArray = document.toJson(QJsonDocument::Compact);
					LPCSTR dataChar;
					dataChar = byteArray.data();
					QString ServiceID = data_json.find("ServiceTypeID").value().toString();
					if (ServiceID.toInt() == 18)//植被
					{
						//获取区站号
						PerHandleData->StationID = data_json.find("StationID").value().toString();
						PerHandleData->DeviceID = data_json.find("DeviceID").value().toString();
						int file = data_json.find("FileType").value().toInt();
						//通知EHT,新的数据
						emit NewDataSignal(
							PerHandleData->StationID,
							PerHandleData->ClientIP,
							PerHandleData->Port,
							file,
							PerHandleData->Socket,
							PerHandleData->DeviceID);
						break;
					}

					//发送至消息中间件
					if (g_SimpleProducer.send(dataChar, strlen(dataChar)) < 0)
						emit ErrorMSGSignal(10304);
					//if (g_SimpleProducer_ZDH.send(dataChar, strlen(dataChar)) < 0)
					//	emit ErrorMSGSignal(10304);


					//获取区站号
					PerHandleData->StationID = data_json.find("StationID").value().toString();
					//获取设备号
					PerHandleData->DeviceID = data_json.find("DeviceID").value().toString();
					//通知EHT,新的数据
					emit NewDataSignal(
						PerHandleData->StationID,
						PerHandleData->ClientIP,
						PerHandleData->Port,
						PerHandleData->Socket,
						PerHandleData->DeviceID);
					break;
				}
				break;
				case 2://操作数据
				{
					int ValueCount = data_json.find("ValueCount").value().toInt();
					switch (ValueCount)
					{
					case 1:
					{
						QString Value = data_json.find("RecvValue1").value().toString();
						emit OperationResultSignal(Value,m_Port,PerHandleData->StationID,PerHandleData->DeviceID);
						break;
					}
					case 2:
					{
						QString Value1 = data_json.find("RecvValue1").value().toString();
						QString Value2 = data_json.find("RecvValue2").value().toString();
						emit OperationResultSignal(Value1,Value2, m_Port, PerHandleData->StationID,PerHandleData->DeviceID);
						break;
					}
					//航空操作数据或水体液位
					case 7:
					{
						QString StationID = data_json.find("StationID").value().toString();
						QString Command = data_json.find("Command").value().toString();
						QString DeviceID = data_json.find("DeviceID").value().toString() == NULL ? "NULL" : data_json.find("DeviceID").value().toString();
						QString Value1 = data_json.find("RecvValue1").value().toString();
						QString Value2 = data_json.find("RecvValue2").value().toString();
						emit OperationResultSignal(Command,Value1,Value2,NULL,NULL, m_Port, PerHandleData->StationID, PerHandleData->DeviceID);
						}
					default:
						break;
					}
				
				}
				break;
				case 3://心跳数据
				{
					//获取区站号
					PerHandleData->StationID = data_json.find("StationID").value().toString();
					//获取设备号
					PerHandleData->DeviceID = data_json.find("DeviceID").value().toString();
					//if (m_Port == 8005)
				//	{
					/*	QJsonObject HBJson;
						HBJson.insert("DeviceID", PerHandleData->StationID);
						HBJson.insert("ServiceTypeID","18");
						QDateTime current_date_time = QDateTime::currentDateTime();
						QString current_date = current_date_time.toString("yyyy-MM-dd hh24:mm:ss");
						HBJson.insert("HBTime", current_date);
						HBJson.insert("OnLineStatus",true);*/
						QJsonDocument document;
						document.setObject(data_json);
						QByteArray byteArray = document.toJson(QJsonDocument::Compact);
						LPCSTR dataChar;
						dataChar = byteArray.data();
						//发送至消息中间件
					//	if (g_SimpleProducer_sh.send(dataChar, strlen(dataChar)) < 0)
						//	emit ErrorMSGSignal(10304);
				//	}
					emit NewDataSignal(
						PerHandleData->StationID,
						PerHandleData->ClientIP,
						PerHandleData->Port,
						PerHandleData->Socket,
						PerHandleData->DeviceID);
					break;
				}
				break;
				}
			}
			break;
		}
		default://-1：表示未知数据
			LogWrite::SYSLogMsgOutPut(QString::fromLocal8Bit("台站号")+PerHandleData->StationID+QString::fromLocal8Bit("意外的接收字节:")+ PerHandleData->Frame);
			break;
		}
	}
	catch (const std::exception&)
	{
		LogWrite::SYSLogMsgOutPut("解析数据发生异常错误!");
		return;
	}
		
}

int IOCP:: GetSocket()
{
	return m_SrvSocket;
}

void IOCP::SetWebCommand(bool bCommand)
{
	m_bIsWebCommand = bCommand;
}