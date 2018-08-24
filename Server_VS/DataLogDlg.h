#pragma once

#include <QDialog>
#include "ui_DataLogDlg.h"
#include<qstringlist.h>
#include"ReadSYSLogTXT.h"
#include<QMouseEvent>
#include<QTimer>
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
	void updatePixmap();
	void slot_minWindow();
private:
	Ui::DataLogDlg ui;
	//��������߳�
	QStringList dataList;
	//��ǰҳ��
	int currentPage;
	//�ܹ�ҳ��
	int TotalPage;
	ReadSYSLogTXT *readTxtThread;
	//�ȴ�����ؼ�
	QLabel *m_pLoadingLabel;
	QLabel *m_pTipLabel;
	//�ȴ�����ʱ��
	QTimer *m_pTimer;
	//ͼƬ���
	int m_nIndex;
	//����txt��ʶλ
	bool FlagOver;
	bool m_Drag;                //�ж��������Ƿ���
	QPoint m_DragPosition;
private:
	//��ȡ��ǰҳ������
	void GetDataInCurrentPage(int CurrentPage);
	//�رմ���
	virtual void closeEvent(QCloseEvent *e);
	void StartAnimation();
	void StopAnimation();
	//�����ƶ�
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
signals:
	void SetFlagOverSignal();
};
