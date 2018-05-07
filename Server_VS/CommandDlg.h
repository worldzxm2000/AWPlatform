#pragma once

#include <QDialog>
#include "ui_CommandDlg.h"
#include"qcompleter.h"
#include<qstringlistmodel.h>
class CommandDlg : public QDialog
{
	Q_OBJECT

public:
	CommandDlg(int ServicType);
	~CommandDlg();

private:
	Ui::CommandDlg ui;
private:
	//����ini�ļ�
	QStringList LoadCommandIni(int ServiceType);
private:
	QCompleter *completer;
	QStringListModel *listModel;
public:
	int Socket;
private slots:
    void on_SendBtn_clicked();
};
