#pragma once

#include <QObject>
#include<QTableWidget>
#include<QPushButton>
class SrvTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	SrvTableWidget(QWidget *parent);
	~SrvTableWidget();
public:
	//添加行数据
	void  AddRow(QString header1,QString header2);
 signals:
	void NoticfyServerRun(int ServerIndex);
	void NoticfyServerStop(int ServerIndex);
private:
	virtual void focusOutEvent(QFocusEvent *event);
	virtual void focusInEvent(QFocusEvent *evnet);
	QPushButton *StatusBtn;
private slots:
	void On_Run_Btn();
};
