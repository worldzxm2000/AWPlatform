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
	int result = -1;
	for (int i = 0; i <Sockets.count(); i++)
	{
		result = closesocket(Sockets.at(i));
	}
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

	pParam pparam;
	pparam.HandleIOCP = completionPort;
	pparam.HandleClass = (HANDLE)this;
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
		if (SOCKET_ERROR == (signed)acceptSocket) {   // 接收客户端失败

			NoticfyServerError(-1);
			break;
		}

		//客户端socket与IOCP关联
		PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		PerHandleData->socket = acceptSocket;
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


		LPCSTR ch = inet_ntoa(saRemote.sin_addr);
		PerHandleData->ClientIP = ch;
		QString ip = QString(QLatin1String(ch));

		PerHandleData->Port = saRemote.sin_port;
		int port = PerHandleData->Port;
		PerHandleData->count = 0;
		PerHandleData->Connected = true;
		//客户端socket添加入客户端数组，通知主程序
		Sockets.push_back(acceptSocket);

		NoticfyUINewClient(ip, port, m_port, acceptSocket);
	
		//读取区站号信息
		send(acceptSocket, "ID\r\n", 4, 0);
		bIsGetStationID = true;
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
		struct pParam *p = (struct pParam*)pParam;

		HANDLE completionPort =p->HandleIOCP;
		IOCP *pIOCP = (IOCP *)p->HandleClass;
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
		///**************************解析动态链接库***********************************
		LRESULT pResult = p->func_Char2Json(perIOData->buffer, len, JsonObj);
		switch (pResult)
		{
		case 1://1：表示BG,ED的要素数据
		{
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
			QString strStationID = JsonObj.find("StationID").value().toString();
			QByteArray baStationID = strStationID.toLatin1();
			PerHandleData->StationID = baStationID.data();
			//获取
			QString strServiceTypeID = JsonObj.find("ServiceTypeID").value().toString();
			QByteArray baServiceTypeID = strServiceTypeID.toLatin1();
			PerHandleData->ServiceTypeID = baServiceTypeID.data();

			QString strObserveTime = JsonObj.find("UploadTime").value().toString();
			QByteArray bastrObserveTime = strObserveTime.toLatin1();
			PerHandleData->ObserveTime = bastrObserveTime.data();

			PerHandleData->count += 1;
			PerHandleData->StationStatus = true;
			PerHandleData->Connected = true;
			


			p->NoticfyServerUpdateUI(PerHandleData->ServiceTypeID,
				PerHandleData->StationID,
				PerHandleData->ObserveTime,
				PerHandleData->count,
				PerHandleData->StationStatus,
				PerHandleData->Connected,
				PerHandleData->ClientIP,
				PerHandleData->Port);
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
		case 4:
		{
			QString ip(PerHandleData->ClientIP);
			JsonObj.insert("IP", ip);
			JsonObj.insert("Port", PerHandleData->Port);
			//服务器第一次发送ID获取站台号
			if (p->bIsGetStationID)
			{
				p->NoticfyServerNewConnectionStationID(JsonObj);
				p->bIsGetStationID = false;
				break;
			}
			
			p->NoticfyServerRecvValue(JsonObj);
			break;
		}
		case 0://0：表示非法的终端命令
		{
			p->NoticfyServerOperateStatus(-1);
			break;
		}
		default://-1：表示无效数据//-2：表示非航空气象数据
		{
			QJsonDocument document;
			document.setObject(JsonObj);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);
			LPCSTR dataChar;
			dataChar = byteArray.data();
			g_SimpleProducer.send(dataChar, strlen(dataChar));
			break;
		}
			
		}
	}
	catch (QString  exception)
	{
		qInstallMessageHandler(LogWrite::LogMsgOutput);
	}
}

