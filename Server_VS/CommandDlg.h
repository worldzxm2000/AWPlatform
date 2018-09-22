#pragma once

#include <QDialog>
#include "ui_CommandDlg.h"
#include<QCompleter>
#include<QStringListModel>
class CommandDlg : public QDialog
{
	Q_OBJECT

public:
	CommandDlg(int ServicType);
	~CommandDlg();

private:
	Ui::CommandDlg ui;
private:
	//加载终端命令INI文件
	QStringList LoadCommandIni(int ServiceType);
	//查找终端命令名称
    QString FindCommName(QString comm);
private:
	QCompleter *completer;
	QStringListModel *listModel;
	QMap<QString,QString> map;
public:
	//当前设备Socket
	int Socket;
signals:
	void NoticfyUICOMMSTR(QString CommName);

private slots:
    void on_SendBtn_clicked();
};
