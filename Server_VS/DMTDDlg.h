#pragma once
#include <QDialog>
#include "ui_DMTDDlg.h"
#include"param.h"
#include"LoadTxtThread.h"
#include"ImpDataThread.h"
class DMTDDlg : public QDialog
{
	Q_OBJECT

public:
	DMTDDlg(QWidget *parent = Q_NULLPTR);
	~DMTDDlg();

private slots:
    void on_BrowsingBtn_clicked();

    void on_ImpBtn_clicked();
private:
	Ui::DMTDDlg ui;
	//数据路径
	QString path;
	//存放解析数据的json数组
	QList<QJsonObject> JsonList;
protected:
	void closeEvent(QCloseEvent *event);
	LoadTxtThread *loadTxtThread;//读取TXT线程
	ImpDataThread *impDataThread;//上传数据线程
	int totalCount;//总个数
public:
	//解析数据
	Char2Json func_Char2Json;
public slots:
    void LoadTxtThreadFinish();//读取TXT线程结束
    void ImpDataThreadFinish();//导入线程结束
	void QLabelSlot(int count);//刷新UI数据个数
	void RecJsonData(QJsonObject json);//接收数据
	void QProcessBarSlot(int count);//进度条刷新
	void GetErrorMSG(int Result);//导出错误
signals:
	void finished();
	void ErrorMSGSignal(int Error);//发送错误
};
