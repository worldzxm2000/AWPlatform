#include "CommandDlg.h"
#include<QSettings>
#include"param.h"
#include<QMessageBox>
CommandDlg::CommandDlg(int ServiceType)
{
	
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint);
	completer = new QCompleter();
	completer->setFilterMode(Qt::MatchContains);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	QStringList valueList;
	valueList = LoadCommandIni(ServiceType);
	listModel = new QStringListModel(valueList, this);
	completer->setModel(listModel);
	ui.COMMText->setCompleter(completer);
	//ui.SendBtn->setFocus(); //设置默认焦点
	ui.SendBtn->setDefault(true); //设置默认按钮，设置了这个属性，当用户按下回车的时候，就会按下该按钮

	map.insert("BASEINFO",QString::fromLocal8Bit("采集器基本信息"));
	map.insert("ID", QString::fromLocal8Bit("观测站区站号"));
	map.insert("DATETIME", QString::fromLocal8Bit("采集器时间"));
	map.insert("LAT", QString::fromLocal8Bit("观测站纬度"));
	map.insert("ALT", QString::fromLocal8Bit("观测场拔海高度")); 
	map.insert("LONG", QString::fromLocal8Bit("观测站经度"));
	map.insert("CAPTIME", QString::fromLocal8Bit("采集时间范围"));
	map.insert("CFSET ", QString::fromLocal8Bit("CF卡模块配置"));
	map.insert("CAPINTERVAL", QString::fromLocal8Bit("采集时间间隔"));
	map.insert("SNAPSHOT", QString::fromLocal8Bit("手动采集"));
	map.insert("RESET", QString::fromLocal8Bit("重新启动采集器"));
	map.insert("UPDATE", QString::fromLocal8Bit("远程升级开关"));
	map.insert("DMTD", QString::fromLocal8Bit("补抄数据"));
}

CommandDlg::~CommandDlg()
{
	delete completer;
	delete listModel;
	completer = NULL;
	listModel = NULL;
}


QStringList CommandDlg::LoadCommandIni(int ServiceType)
{
	//读取Command.ini路径
	QString path = QCoreApplication::applicationDirPath()+"//Command.ini";
	//打开INI文件
	QSettings configIniRead(path, QSettings::IniFormat);
	QStringList list;
	switch (ServiceType)
	{
	case HKQX:
	{
		//终端命令个数
		int Count = configIniRead.value("HKQX/COMMCount").toInt();
		//遍历终端命令
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/HKQX/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	case TRSF:
	{
		int Count = configIniRead.value("/TRSF/COMMCount").toInt();
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/TRSF/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	case JTQX:
	{
		//终端命令个数
		int Count = configIniRead.value("JTQX/COMMCount").toInt();
		//遍历终端命令
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/JTQX/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	case NW:
	{
		//终端命令个数
		int Count = configIniRead.value("NW/COMMCount").toInt();
		//遍历终端命令
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/NW/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	case NTXQH:
	{
		//终端命令个数
		int Count = configIniRead.value("NTXQH/COMMCount").toInt();
		//遍历终端命令
		for (int i = 0; i < Count; i++)
		{
			QString comm = "/NTXQH/COMM" + QString::number(i);
			list.append(configIniRead.value(comm).toString());
		}
		break;
	}
	default:
		break;
	}
	return list;
}
//发送按钮事件
void CommandDlg::on_SendBtn_clicked()
{
	QString comm = ui.COMMText->text().trimmed();
	QString commName = FindCommName(comm);
	comm += "\r\n";
	QByteArray byteArray = comm.toLatin1();
	LPCSTR dataChar;
	dataChar = byteArray.data();
	int len = comm.count();
	send(Socket,dataChar,len,0);
	ui.StatusLabel->setText(QString::fromLocal8Bit("已发送!"));
	NoticfyUICOMMSTR(commName);
	this->accept();
}

QString CommandDlg::FindCommName(QString comm)
{
	QStringList commlist = comm.split(" ");
	comm = commlist.at(0);
	QString commName = QString::fromLocal8Bit("未知命令");
	QMap<QString, QString>::const_iterator mi = map.find(comm);
	if (mi != map.end())
		return map[comm];
	return commName;
}