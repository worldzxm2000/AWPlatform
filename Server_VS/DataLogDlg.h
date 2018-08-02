#pragma once

#include <QDialog>
#include "ui_DataLogDlg.h"
#include<qthreadpool.h>
#include<qstringlist.h>
#include"ReadSYSLogTXT.h"
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
	//��ȡ�����߳�
	QThreadPool pool;
	//��������߳�
	QStringList dataList;
	//��ǰҳ��
	int currentPage;
	//�ܹ�ҳ��
	int TotalPage;
	ReadSYSLogTXT *readTxtThread;
private:
	//��ȡ��ǰҳ������
	void GetDataInCurrentPage(int CurrentPage);
	//�رմ���
	virtual void closeEvent(QCloseEvent *e);
};
