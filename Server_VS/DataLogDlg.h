#pragma once

#include <QDialog>
#include "ui_DataLogDlg.h"
#include<qthreadpool.h>
#include<qstringlist.h>
class DataLogDlg : public QDialog
{
	Q_OBJECT

public:
	DataLogDlg(QWidget *parent = Q_NULLPTR);
	~DataLogDlg();
private slots:
	void GetLogTxt(QStringList strlist);

	void on_PageToBeginBtn_clicked();

	void on_PageDownBtn_clicked();

	void on_PageUpBtn_clicked();

	void on_PageToEndBtn_clicked();

	void ShowToolTip(QModelIndex index);
private:
	Ui::DataLogDlg ui;
	//读取数据线程
	QThreadPool pool;
	//存放数据线程
	QStringList dataList;
	//当前页数
	int currentPage;
	//总共页数
	int TotalPage;
private:
	//获取当前页数数据
	void GetDataInCurrentPage(int CurrentPage);
};
