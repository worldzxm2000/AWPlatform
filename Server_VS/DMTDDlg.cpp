﻿#include "DMTDDlg.h"
#include<process.h>
#include<qfiledialog.h>
#include<qfile.h>
#include<qtextstream.h>
#include<Windows.h>
#include<qjsonobject.h>
#include<qjsondocument.h>
#include"LogWrite.h"
#include<qmessagebox.h>
#include<qthread.h>
DMTDDlg::DMTDDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this); 
	setFixedSize(525, 160);
	ui.DoingBar->setWindowTitle(QString::fromLocal8Bit("上传要素数据"));
	count = 0;
	isRun = false;
}

DMTDDlg::~DMTDDlg()
{

}

//浏览文件夹按钮事件
void DMTDDlg::on_BrowsingBtn_clicked()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	
	fileDialog->setFileMode(QFileDialog::Directory);
	
	if (fileDialog->exec() != QDialog::Accepted)
	{
		path = "";
		ui.PathLineEdit->setText(path);
		return;
	}
	path= fileDialog->selectedFiles()[0];
	ui.PathLineEdit->setText(path);
	
	
	threadhandle = (HANDLE)_beginthreadex(NULL, 0, Process, (HANDLE)this, 0, NULL);
	isRun = true;
	::ResumeThread(threadhandle);
}

unsigned DMTDDlg::Process(LPVOID pParam)
{
	DMTDDlg *pDMTDDlg = (DMTDDlg*)pParam;
	if (pDMTDDlg->path == "")
		return 0;
	pDMTDDlg->LoadTXT(pDMTDDlg->path);
	return 1;
}

void DMTDDlg::LoadTXT(QString path)
{

	QDir dir(path);
	if (!dir.exists())
		return;

	QStringList filter;
	dir.setNameFilters(filter);

	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int i = 0;
	bool bIsDir = true;
	do 
	{
		if (fileInfo->at(i).fileName() == "." | fileInfo->at(i).fileName() == "..")
		{
			i++;
			continue;
		}
		else
		{

			bIsDir = fileInfo->at(i).isDir();
			if (bIsDir)
			{
				QString path = fileInfo->at(i).filePath();
				QString name = fileInfo->at(i).fileName();
				LoadTXT(fileInfo->at(i).filePath());

			}
			else
			{

				QString path = fileInfo->at(i).filePath();
				QString name = fileInfo->at(i).fileName();
				QFile file(path);
				if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
					return;
				QTextStream in(&file);
				QString line = in.readLine();

				while ((!line.isNull())&&(isRun == true))
				{
					line = in.readLine();
					//line += "\r\n";
					QByteArray byteArray =line.toLatin1();
					byteArray.append('\r');
					byteArray.append('\n');
					LPCSTR buff= byteArray.data();
					int len=line.length()+2;
					QJsonObject json;
					if (func_Char2Json == NULL)
					{
						QMessageBox::warning(NULL,"警告","解析函数未加载！");
						return;
					}
						
					LRESULT pResult =func_Char2Json(buff, len, json);
					if (pResult != 1)
						continue;
					JsonList.append(json);
					count++;
					ui.NumberLabel->setText(QString::number(count));
					Sleep(10);
				}
				file.close();
			}
		}
		i++;
	} while (i < fileInfo->size());

	ui.DoingBar->setRange(0, count);
	ui.NumberLabel->setText(QString::fromLocal8Bit("共计: ")+QString::number(count));
}

//导入按钮事件
void DMTDDlg::on_ImpBtn_clicked()
{
	LRESULT pResult = ImpData();
	switch (pResult)
	{
	case -1:
		LogWrite::LogMsgOutput("消息中间件通信异常,数据未发送成功！");
		break;
	default:
		break;
	}
}

//导入处理
LRESULT DMTDDlg::ImpData()
{
	LRESULT pResult = -1;
	int iCount = JsonList.size();
	for (int i = 0; i < iCount; i++)
	{
		QJsonDocument document;
		document.setObject(JsonList[i]);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		pResult= g_SimpleProducer.send(dataChar, strlen(dataChar));
		ui.DoingBar->setValue(i+1);
		Sleep(10);
	}
	JsonList.clear();
	return pResult;
}
//进度条
void DMTDDlg::on_DoingBar_valueChanged(int value)
{
	
}
//关闭窗体
void DMTDDlg::closeEvent(QCloseEvent *event)
{
	isRun = false;
	WaitForSingleObject(threadhandle, 3000);//等待线程结束
}