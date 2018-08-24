#pragma once
#include <QDialog>
#include "ui_SYSLogDlg.h"
#include<qthreadpool.h>
#include<qstringlist.h>
#include"ReadSYSLogTXT.h"
#include<QLabel>
#include<QTimer>
#include<QMouseEvent>
class SYSLogDlg : public QDialog
{
	Q_OBJECT

public:
	SYSLogDlg(QWidget *parent = Q_NULLPTR);
	SYSLogDlg(QString LogName,QWidget *parent = Q_NULLPTR);
	~SYSLogDlg();

private:
	Ui::SYSLogDlg ui;
	//读取数据线程
	ReadSYSLogTXT *readTxtThread;
	//存放数据线程
	QStringList dataList;
	//当前页数
	int currentPage;
	//总共页数
	int TotalPage;
	//等待界面控件
	QLabel *m_pLoadingLabel;
	QLabel *m_pTipLabel;
	//等待界面时间
	QTimer *m_pTimer;
	//图片编号
	int m_nIndex;
	//加载txt标识位
	bool FlagOver;
private:
	//获取当前页数数据
	void GetDataInCurrentPage(int CurrentPage);
	//关闭窗体
	virtual void closeEvent(QCloseEvent *e);
	void StartAnimation();
	void StopAnimation();
	//窗体移动
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;                //判断鼠标左键是否按下
	QPoint m_DragPosition;
private slots:
	void GetLogTxt(QStringList strlist);
    void on_PageDownBtn_clicked();
    void on_PageUpBtn_clicked();
    void on_PageToBeginBtn_clicked();
    void on_PageToEndBtn_clicked();
	void ShowToolTip(QModelIndex index);
	void updatePixmap();
	void slot_minWindow();
signals:
	
	void SetFlagOverSignal();
};
