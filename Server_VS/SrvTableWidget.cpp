#include "SrvTableWidget.h"
#include<QHeaderview>
#include<QMessageBox>
#include <QLabel>
#include<QDateTimeEdit.h>
#include<QComboBox.h>
#include<QSpinBox>
SrvTableWidget::SrvTableWidget(QWidget *parent)
	:QTableWidget(parent)
{
	setColumnCount(3);
	StatusBtn = nullptr;
	int row = 0;
	QStringList headerlist;
	headerlist.append(QString::fromLocal8Bit("业务类型"));
	headerlist.append(QString::fromLocal8Bit("运行状态"));
	headerlist.append(QString::fromLocal8Bit("业务名称"));
	setHorizontalHeaderLabels(headerlist);
	this->verticalHeader()->setHidden(true);// 隐藏行号 
	setColumnHidden(2, true);//隐藏第三列
	setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(77,77,77);color:white;}"); //设置表头背景色
	setColumnWidth(0,150);
	setColumnWidth(1, 30);//设置第二列宽度50
	horizontalHeader()->setStretchLastSection(true);//列宽
}

SrvTableWidget::~SrvTableWidget()
{
}

//添加行
void SrvTableWidget::AddRow(QString header1="header", QString header2="header")
{
	int rowIndex = this->rowCount();
	setRowCount(rowIndex+1);
	QTableWidgetItem *firstTableWidgetItem = new QTableWidgetItem(header1);
	setItem(rowIndex, 0, firstTableWidgetItem);

	firstTableWidgetItem->setForeground(Qt::white);
	firstTableWidgetItem->setBackgroundColor(QColor(77, 77, 77));
	QTableWidgetItem *thirdTableWidgetItem = new QTableWidgetItem(header2);
	setItem(rowIndex, 2, thirdTableWidgetItem);

	StatusBtn = new QPushButton(this);
	StatusBtn->setStyleSheet("QPushButton{background:rgb(77,77,77);color:white;}");
	connect(StatusBtn, SIGNAL(clicked()), this, SLOT(On_Run_Btn()));
	StatusBtn->setText(QString::fromLocal8Bit("停止"));
	setCellWidget(rowIndex, 1, StatusBtn);
}
//运行按钮
void SrvTableWidget::On_Run_Btn()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
		return;
	QModelIndex idx = this->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	int row = idx.row();
	QString strText = senderObj->text();
	if (strText==QString::fromLocal8Bit("运行"))
	{
		NoticfyServerRun(row);
		senderObj->setText(QString::fromLocal8Bit("停止"));
	}
	else
	{
		NoticfyServerStop(row);
		senderObj->setText(QString::fromLocal8Bit("运行"));
	}
}

void SrvTableWidget::focusOutEvent(QFocusEvent *event)
{
	if (StatusBtn == NULL)
		return;
	StatusBtn->setStyleSheet("QPushButton{background:rgb(77,77,77);color:white;}");
	clearSelection();
}

void SrvTableWidget::focusInEvent(QFocusEvent *event)
{
	if (StatusBtn == NULL)
		return;
	StatusBtn->setStyleSheet("QPushButton{background:rgb(50,50,50);color:white;}");
}