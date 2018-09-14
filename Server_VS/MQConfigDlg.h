#pragma once

#include <QWidget>
#include "ui_MQConfigDlg.h"

class MQConfigDlg : public QWidget
{
	Q_OBJECT

public:
	MQConfigDlg(QWidget *parent = Q_NULLPTR);
	~MQConfigDlg();

private:
	Ui::MQConfigDlg ui;
};
