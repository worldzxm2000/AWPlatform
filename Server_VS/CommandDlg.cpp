#include "CommandDlg.h"
#include<QSettings>
#include"param.h"
#include<qmessagebox.h>
CommandDlg::CommandDlg(int ServiceType)
{
	
	ui.setupUi(this);
	completer = new QCompleter();
	completer->setFilterMode(Qt::MatchContains);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	QStringList valueList;
	valueList = LoadCommandIni(ServiceType);
	listModel = new QStringListModel(valueList, this);
	completer->setModel(listModel);
	ui.COMMText->setCompleter(completer);
	ui.SendBtn->setFocus(); //设置默认焦点
	ui.SendBtn->setDefault(true); //设置默认按钮，设置了这个属性，当用户按下回车的时候，就会按下该按钮
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
	//锟斤拷取ini路锟斤拷
	QString path = QCoreApplication::applicationDirPath()+"//Command.ini";
	//锟斤拷锟截碉拷ini锟侥硷拷锟斤拷锟斤拷
	QSettings configIniRead(path, QSettings::IniFormat);
	QStringList list;
	switch (ServiceType)
	{
	case HKQX:
	{
		//锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
		int Count = configIniRead.value("HKQX/COMMCount").toInt();
		//锟斤拷取锟斤拷锟斤拷
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
	default:
		break;
	}
	return list;
}
//发送按钮事件
void CommandDlg::on_SendBtn_clicked()
{
	QString comm = ui.COMMText->text().trimmed();
	comm += "\r\n";
	QByteArray byteArray = comm.toLatin1();
	LPCSTR dataChar;
	dataChar = byteArray.data();
	int len = comm.count();
	send(Socket,dataChar,len,0);
	ui.StatusLabel->setText(QString::fromLocal8Bit("已发送!"));
}
