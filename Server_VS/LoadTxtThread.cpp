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
	do//Ѱ�ҵ�ǰ�ļ�����txt�ļ�
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
						QMessageBox::warning(NULL, "����", "��������δ���أ�");
						return;
					}

					LRESULT pResult;
					pResult = func_Char2Json(st, json);

					//�жϽ������
					switch (pResult)
					{
					case 1://1����ʾ�۲�����
					{
						//���յ����ݸ���
						int Count = json.find("DataLength").value().toInt();
						//����JSON������
						for (int i = 0; i < Count; i++)
						{
							//������������
							QJsonObject data_json = json.find(QString::number(i + 1)).value().toObject();
							//��ȡ�������ͣ�1Ϊ�۲����ݣ�2λ�������ݣ�3Ϊ�������ݣ�
							int DataType = data_json.find("DataType").value().toInt();
							switch (DataType)
							{
							case 1://�۲�����
							{
								emit SendJson(data_json);
								count++;
								break;
							}
							case 2://��������
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
							case 3://��������
							{
								//��ȡ��վ��
								break;
							}
							}
						}
						break;
					}
					default://-1����ʾδ֪����
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