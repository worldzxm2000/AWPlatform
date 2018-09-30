#include "LoadTxtThread.h"
#include<QFile>
#include<QDir>
#include<QTextStream>
#include<QJsonObject>
#include<QMessageBox>
LoadTxtThread::LoadTxtThread()
{
	count = 0;
}

LoadTxtThread::~LoadTxtThread()
{
}

void LoadTxtThread::run()
{
	LoadTXT(path);
}

void LoadTxtThread::LoadTXT(QString path)
{
	QDir dir(path);
	if (!dir.exists())
		return;
	QStringList filter;
	dir.setNameFilters(filter);

	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int i = 0;
	bool bIsDir = true;
	do//寻找当前文件夹下txt文件
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

				while ((!line.isNull()) && (isRun == true))
				{

					QString st = line;
					st.trimmed();
					QJsonObject json;
					if (func_Char2Json == NULL)
					{
						QMessageBox::warning(NULL, "警告", "解析函数未加载！");
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
								emit SendJson(data_json);
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

					emit CountOfStrSignal(count);
					line = in.readLine();
				}
				file.close();
			}
		}
		i++;
	} while (i < fileInfo->size());
}