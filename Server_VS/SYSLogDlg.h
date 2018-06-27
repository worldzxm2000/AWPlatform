#pragma once

#include <QDialog>
#include "ui_SYSLogDlg.h"

class SYSLogDlg : public QDialog
{
	Q_OBJECT

public:
	SYSLogDlg(QWidget *parent = Q_NULLPTR);
	~SYSLogDlg();

private:
	Ui::SYSLogDlg ui;
};
