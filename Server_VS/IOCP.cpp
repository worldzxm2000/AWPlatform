#include "IOCP.h"
#include<process.h>
#include<qmessagebox.h>
#include"LogWrite.h"
#include"Dictionary.h"
#include<qdebug.h>
#include<qthread.h>
#include<qjsondocument.h>
using namespace std;
//IOCP *g_iocp;

HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

IOCP::IOCP()
{
	bIsListened = false;
	//g_iocp = this;
	bIsGetStationID = false;
}

IOCP::~IOCP()
{
	/*WaitForSingleObject(hMutex, INFINITE);
	if (bIsListened)
		Stop();
	ReleaseMutex(hMutex);*/
}

void IOCP::SetListenedPort(int port)
{
	bIsListened = true;
	this->m_port = port;

}

void IOCP::Stop()
{
	if (bIsListened != true)
		return;
	int result = -1;
	int count = Sockets.count();
	for (int i = 0; i <count; i++)
	{
		result = closesocket(Sockets.at(i));
	}
	Sockets.clear();
	result= closesocket(srvSocket);
	//CloseHandle((HANDLE)srvSocket);
	for (int i = 0; i < iThreadsCount; i++)
	{
		// 通知所有的完成端口操作退出  
		PostQueuedCompletionStatus(completionPort, 0, NULL, NULL);
	}
	bIsListened = false;
	

}

//获取当前运行状态
bool IOCP::GetStatus()
{
	return bIsListened;
}

void IOCP::SendSocket()
{

}

void IOCP::run()
{
	//初始化WSA    加载socket动态链接库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // 接收Windows Socket的结构信息
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		NoticfyServerError(-1);
	}
	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (NULL == completionPort)
	{
		NoticfyServerError(-1);
	}

	PARAMS pparam;
	pparam.completionPort = completionPort;
	pparam.fatherClass = (HANDLE)this;
	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);
	iThreadsCount = (mySysInfo.dwNumberOfProcessors * 2);
	for (unsigned i = 0; i < iThreadsCount; ++i)
	{
		HANDLE threadhandle = (HANDLE)_beginthreadex(NULL, 0, ServerWorkThread, &pparam, 0, NULL);
		::ResumeThread(threadhandle);
	}


	//设置socket
	srvSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	sockaddr_in srvAddr;
	srvAddr.sin_addr.s_addr = INADDR_ANY;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(m_port);
	//绑定SOCKET到本机
	int bindResult = ::bind(srvSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr));
	if (SOCKET_ERROR == bindResult)
	{

		NoticfyServerError(-1);
	}
	// 将SOCKET设置为监听模式
	int listenResult = listen(srvSocket, SOMAXCONN);
	if (SOCKET_ERROR == listenResult)
	{

		NoticfyServerError(-1);
	}

	while (1)
	{
		//结束监听
		if (false == bIsListened)
			return;
		LPPER_HANDLE_DATA PerHandleData = NULL;
		SOCKADDR_IN saRemote;
		int RemoteLen = sizeof(saRemote);
		//接收客户端连接
		SOCKET acceptSocket;
		acceptSocket = accept(srvSocket, (SOCKADDR*)&saRemote, &RemoteLen);
		if (SOCKET_ERROR == (signed)acceptSocket)
		{  
			// 接收客户端失败
			break;
		}

		//客户端socket与IOCP关联
		PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		PerHandleData->socket = acceptSocket;
		PerHandleData->IsWholeFrame = true;
		memcpy(&PerHandleData->ClientAddr, &saRemote, RemoteLen);

		//客户端socket绑定IOCP
		CreateIoCompletionPort((HANDLE)(PerHandleData->socket), completionPort, (DWORD)PerHandleData, 0);
		//客户端信息
		LPPER_IO_OPERATION_DATA PerIoData = NULL;
		PerIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATEION_DATA));
		ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
		PerIoData->databuff.len = 4 * 1024;
		PerIoData->databuff.buf = PerIoData->buffer;
		PerIoData->operationType = 0;

		//PerHandleData->ClientIP ;
	   LPCSTR ch = inet_ntoa(saRemote.sin_addr);
		QString ip = QString(QLatin1String(ch));
		//PerHandleData->ClientIP.append(ch);
		//= QString(ip);

		PerHandleData->Port = saRemote.sin_port;
		int port = PerHandleData->Port;
		PerHandleData->count = 0;
		PerHandleData->Connected = true;
		//客户端socket添加入客户端数组，通知主程序
		Sockets.push_back(acceptSocket);

		NoticfyUINewClient(ip, port, m_port, acceptSocket);
	
		//读取区站号信息
		//send(acceptSocket, "ID\r\n", 4, 0);
	//	bIsGetStationID = true;
		DWORD RecvBytes = 0;
		DWORD Flags = 0;
		WSARecv(PerHandleData->socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);

	}
	//结束监听
	//NoticfyServerError(-1);
}

//IOCP线程队列
unsigned IOCP::ServerWorkThread(LPVOID pParam)
{
	try
	{
		LPPARAMS p = (LPPARAMS)pParam;
		HANDLE completionPort =p->completionPort;
		IOCP *pIOCP = (IOCP *)p->fatherClass;
		DWORD BytesTransferred = 0;
		LPOVERLAPPED IpOverlapped;
		LPPER_IO_DATA PerIoData = NULL;
		LPPER_HANDLE_DATA PerHandleData = NULL;
		DWORD RecvBytes;
		DWORD Flags = 0;
		BOOL bRet = FALSE;

		while (1)
		{
			bRet = GetQueuedCompletionStatus(completionPort, &BytesTransferred, (PULONG_PTR)&PerHandleData, (LPOVERLAPPED*)&IpOverlapped, INFINITE);
			//退出线程
			if (IpOverlapped == NULL)
			{
				break;
			}
			if (bRet == 0)
			{
				return -1;
			}

			PerIoData = (LPPER_IO_DATA)CONTAINING_RECORD(IpOverlapped, PER_IO_DATA, overlapped);
			if (0 == BytesTransferred)
			{
				closesocket(PerHandleData->socket);
				GlobalFree(PerHandleData);
				GlobalFree(PerIoData);
				continue;
			}
			//线程处理函数
			UnboxData(PerIoData, BytesTransferred, PerHandleData,pIOCP);


			//为下一个重叠调用建立IO操作
			ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
			memset(PerIoData->buffer, 0, 4 * 1024);
			PerIoData->databuff.len = 4 * 1024;
			PerIoData->databuff.buf = PerIoData->buffer;
			PerIoData->operationType = 0;

			WSARecv(PerHandleData->socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
			//WSARecvFrom(PerHandleData->socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, (SOCKADDR*)&PerHandleData->ClientAddr, &len, &(PerIoData->overlapped), NULL);

		}
		return 0;
	}
	catch (QString  exception)
	{
		qInstallMessageHandler(LogWrite::LogMsgOutput);
		return 0;
	}

}

//接收处理数据
void IOCP::UnboxData(LPPER_IO_DATA perIOData, u_short len, LPPER_HANDLE_DATA PerHandleData,IOCP *p)
{
	try
	{
		QJsonObject JsonObj;
		LRESULT pResult = -99;
		//数据内存判断，如果数据内存大于3M说明有错误数据 需要清空内存，否则会造成内存溢
		if (PerHandleData->DataCount>1024*3)
			memset(PerHandleData->Frame, 0, sizeof(PerHandleData->Frame) / sizeof(char));
		///**************************解析动态链接库***********************************
		if (PerHandleData->IsWholeFrame == false)
		{
			//一帧数据的两次接收数据
			strcat(PerHandleData->Frame, perIOData->buffer);
			PerHandleData->DataCount += len;
			pResult = p->func_Char2Json(PerHandleData->Frame, PerHandleData->DataCount, JsonObj);
		}
		else
		{
		
			pResult = p->func_Char2Json(perIOData->buffer, len, JsonObj);
		}
	
		switch (pResult)
		{
		case 1://1：表示BG,ED的要素数据
		{
			PerHandleData->IsWholeFrame = true;
			PerHandleData->DataCount = 0;
			memset(PerHandleData->Frame, 0, sizeof(PerHandleData->Frame) / sizeof(char));
			//发送给消息中间件
			QJsonDocument document;
			document.setObject(JsonObj);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);

			QString DataTypeID = JsonObj.find("DataTypeID").value().toString();
			//即时采集数据
			if (DataTypeID=="01")
			{
				p->NoticfyServerRecvValue(JsonObj);
				return;
			}
			LPCSTR dataChar;
			dataChar = byteArray.data();
			g_SimpleProducer.send(dataChar, strlen(dataChar));
			//获取区站号
			QString StationID = JsonObj.find("StationID").value().toString();
			//获取业务号
			QString ServiceTypeID = JsonObj.find("ServiceTypeID").value().toString();
	        //获取时间
			QString ObserveTime = JsonObj.find("UploadTime").value().toString();
			PerHandleData->count += 1;
			PerHandleData->Connected = true;
			//获取IP
			 LPCSTR ch = inet_ntoa(PerHandleData->ClientAddr.sin_addr);
			QString ip = QString(QLatin1String(ch));
			p->NoticfyServerUpdateUI(ServiceTypeID,
				StationID,
				ObserveTime,
				PerHandleData->count,
				true,
				ip,
				PerHandleData->Port,
				PerHandleData->socket);
			break;
		}
		case 2://2：表示终端命令操作成功
		{
			p->NoticfyServerOperateStatus(1);
			break;
		}
		case 3://3：表示终端命令操作失败
		{
			p->NoticfyServerOperateStatus(0);
			break;
		}
		//发送的终端命令返回值
		case 4:
		{
			QString ip(PerHandleData->ClientIP);
			JsonObj.insert("IP", ip);
			JsonObj.insert("Port", PerHandleData->Port);
			p->NoticfyServerRecvValue(JsonObj);
			break;
		}
		//农委数据 两根
		case 20:
		{
			QJsonObject json_one;
			QJsonObject json_another;

			json_one =JsonObj.find("1").value().toObject();
			json_another = JsonObj.find("2").value().toObject();

			QString DataTypeID = json_one.find("DataTypeID").value().toString();
			//即时采集数据
			//if (DataTypeID == "01")
			//{
			//	p->NoticfyServerRecvValue(json_one);
			//	p->NoticfyServerRecvValue(json_another);
			//	return;
			//}
			//发送消息第一根
			QJsonDocument document_one;
			document_one.setObject(json_one);
			QByteArray byteArray_one = document_one.toJson(QJsonDocument::Compact);
			LPCSTR dataChar_one;
			dataChar_one = byteArray_one.data();
			g_SimpleProducer.send(dataChar_one, strlen(dataChar_one));
			//发送消息第二根
			QJsonDocument document_another;
			document_another.setObject(json_another);
			QByteArray byteArray_another = document_another.toJson(QJsonDocument::Compact);
			LPCSTR dataChar_another;
			dataChar_another = byteArray_another.data();
			g_SimpleProducer.send(dataChar_another, strlen(dataChar_another));
			//获取区站号
			QString StationID = json_one.find("StationID").value().toString();
			//获取业务号
			QString ServiceTypeID = json_one.find("ServiceTypeID").value().toString();
			//获取时间
			QString ObserveTime = json_one.find("UploadTime").value().toString();
			PerHandleData->count += 1;
			PerHandleData->Connected = true;

			p->NoticfyServerUpdateUI(ServiceTypeID,
				StationID,
				ObserveTime,
				PerHandleData->count,
				true,
				PerHandleData->ClientIP,
				PerHandleData->Port,
				PerHandleData->socket);
			break;

		}
		case 0://0：表示非法的终端命令
		{
			p->NoticfyServerOperateStatus(-1);
			break;
		}
		//心跳数据
		case 8:
		{
			//获取区站号
			QString strStationID = JsonObj.find("StationID").value().toString();
			//获取
			QString strServiceTypeID = JsonObj.find("ServiceTypeID").value().toString();
			QString ip = PerHandleData->ClientIP;
			p->NoticfyServerHB(PerHandleData->socket);
			break;
		}
		//非业务数据
		case -2:
		{
			p->NoticfyServerError(-2);
			break;
		}
		//不完整数据
		case -6:
		{
			
			strcat(PerHandleData->Frame, perIOData->buffer);
			PerHandleData->DataCount += len;
			PerHandleData->IsWholeFrame = false;
			break;
		}
		default://-1：表示无效数据
		{
			QJsonDocument document;
			document.setObject(JsonObj);
			p->NoticfyServerNewConnectionStationID(JsonObj);
		//	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		//	LPCSTR dataChar;
		//	dataChar = byteArray.data();
		//	g_SimpleProducer.send(dataChar, strlen(dataChar));
			break;
		}
			
		}
	}
	catch (QString  exception)
	{
		qInstallMessageHandler(LogWrite::LogMsgOutput);
	}
}

