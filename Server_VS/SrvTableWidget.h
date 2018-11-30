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
	bool NoticfyServerRun(int ServerIndex);
	bool NoticfyServerStop(int ServerIndex);
private:

private slots:
	void On_Run_Btn();
};
