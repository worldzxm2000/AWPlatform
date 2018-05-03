#pragma once

#include <QDialog>
#include "ui_CommandDlg.h"

class CommandDlg : public QDialog
{
	Q_OBJECT

public:
	CommandDlg(QWidget *parent = Q_NULLPTR);
	~CommandDlg();

private:
	Ui::CommandDlg ui;

public:
	int Socket;
};
