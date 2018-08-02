#include "DMTDDlg.h"
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
	setWindowFlags(Qt::WindowCloseButtonHint);
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
	pDMTDDlg->ui.DoingBar->setRange(0, pDMTDDlg->count);
	pDMTDDlg->ui.NumberLabel->setText(QString::fromLocal8Bit("共计: ") + QString::number(pDMTDDlg->count));
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
				QString line=in.readLine();

				while ((!line.isNull())&&(isRun == true))
				{
					
					QString st = line;
					st.simplified();
					QJsonObject json;
					if (func_Char2Json == NULL)
					{
						QMessageBox::warning(NULL,"警告","解析函数未加载！");
						return;
					}
						
					LRESULT pResult;
					pResult = func_Char2Json(st, json);

					//判断接收情况
					switch (pResult)
					{
					case 1://1：表示观测数据
					{
						//接收到数据个数
						int Count = json.find("DataLength").value().toInt();
						//遍历JSON中数据
						for (int i = 0; i < Count; i++)
						{
							//解析数据数组
							QJsonObject data_json = json.find(QString::number(i + 1)).value().toObject();
							//获取数据类型（1为观测数据，2位操作数据，3为心跳数据）
							int DataType = data_json.find("DataType").value().toInt();
							switch (DataType)
							{
							case 1://观测数据
							{
								JsonList.append(data_json);
								count++;
								break;
							}
							case 2://操作数据
							{
								int ValueCount = data_json.find("ValueCount").value().toInt();
								switch (ValueCount)
								{
								case 1:
								{
									QString Value = data_json.find("RecvValue1").value().toString();
									break;
								}
								case 2:
								{
									QString Value1 = data_json.find("RecvValue1").value().toString();
									QString Value2 = data_json.find("RecvValue2").value().toString();
									break;
								}
								default:
									break;
								}

							}
							case 3://心跳数据
							{
								//获取区站号
								break;
							}
							}
						}
						break;
					}
					default://-1：表示未知数据
						break;
					}
					
					ui.NumberLabel->setText(QString::number(count));
					Sleep(10);
					line = in.readLine();
				}
				file.close();
			}
		}
		i++;
	} while (i < fileInfo->size());

	
}

//导入按钮事件
void DMTDDlg::on_ImpBtn_clicked()
{
	LRESULT pResult = ImpData();
	switch (pResult)
	{
	case -1:
		//LogWrite::SYSLogMsgOutPut("消息中间件通信异常,数据未发送成功！");
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
		//pResult= g_SimpleProducer.send(dataChar, strlen(dataChar));
		pResult=g_SimpleProducer_ZDH.send(dataChar, strlen(dataChar));
		if (pResult<0)
		{
			QMessageBox::warning(NULL, "错误", "消息中间件发生错误");
			return 1;
		}
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
