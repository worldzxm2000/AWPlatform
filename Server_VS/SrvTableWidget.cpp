#include "SrvTableWidget.h"
#include<qheaderview.h>
#include<qpushbutton.h>
#include<qmessagebox.h>
#include <qlabel.h>
#include<QDateTimeEdit.h>
#include<QComboBox.h>
#include<QSpinBox>
SrvTableWidget::SrvTableWidget(QWidget *parent)
	:QTableWidget(parent)
{

	//setWindowTitle(tr("table"));
	//setColumnCount(5);
	//setRowCount(5);

	//QTableWidgetItem *tableWidgetItemSex = new QTableWidgetItem(tr("sex"));
	//setItem(0, 0, tableWidgetItemSex);
	//QTableWidgetItem *tableWidgetItemName = new QTableWidgetItem(tr("Name"));
	//setItem(0, 1, tableWidgetItemName);
	//QTableWidgetItem *tableWidgetItemBrith = new QTableWidgetItem(tr("Brith"));
	//setItem(0, 2, tableWidgetItemBrith);
	//QTableWidgetItem *tableWidgetItemWork = new QTableWidgetItem(tr("Work"));
	//setItem(0, 3, tableWidgetItemWork);
	//QTableWidgetItem *tableWidgetItemIncome = new QTableWidgetItem(tr("Income"));
	//setItem(0, 4, tableWidgetItemIncome);

	//QLabel *LabelPixmap1 = new QLabel();
	//LabelPixmap1->setPixmap(QPixmap(":/images/Male.png"));
	//setCellWidget(1, 0, LabelPixmap1);
	//QTableWidgetItem *TableWidgetItem1 = new QTableWidgetItem(tr("Tom"));
	//setItem(1, 1, TableWidgetItem1);
	//QDateTimeEdit *DateTimeEdit1 = new QDateTimeEdit();
	//DateTimeEdit1->setDateTime(QDateTime::currentDateTime());
	//DateTimeEdit1->setDisplayFormat("dd/M/yyyy");
	//DateTimeEdit1->setCalendarPopup(true);
	//setCellWidget(1, 2, DateTimeEdit1);
	//QComboBox *ComboBoxWork1 = new QComboBox();
	//ComboBoxWork1->addItem(tr("Worker"));
	//ComboBoxWork1->addItem(tr("Farmer"));
	//ComboBoxWork1->addItem(tr("Doctor"));
	//ComboBoxWork1->addItem(tr("Lawyer"));
	//ComboBoxWork1->addItem(tr("Soldier"));
	//setCellWidget(1, 3, ComboBoxWork1);
	//QSpinBox *SpiBoxIncome1 = new QSpinBox();
	//SpiBoxIncome1->setRange(1000, 10000);
	//setCellWidget(1, 4, SpiBoxIncome1);

	//QLabel *LabelPixmap2 = new QLabel();
	//LabelPixmap2->setPixmap(QPixmap(":/images/Male.png"));
	//setCellWidget(2, 0, LabelPixmap2);
	//QTableWidgetItem *TableWidgetItem2 = new QTableWidgetItem(tr("Jack"));
	//setItem(2, 1, TableWidgetItem2);
	//QDateTimeEdit *DateTimeEdit2 = new QDateTimeEdit();
	//DateTimeEdit2->setDateTime(QDateTime::currentDateTime());
	//DateTimeEdit2->setDisplayFormat("dd/M/yyyy");
	//DateTimeEdit2->setCalendarPopup(true);
	//setCellWidget(2, 2, DateTimeEdit2);
	//QComboBox *ComboBoxWork2 = new QComboBox();
	//ComboBoxWork2->addItem(tr("Worker"));
	//ComboBoxWork2->addItem(tr("Farmer"));
	//ComboBoxWork2->addItem(tr("Doctor"));
	//ComboBoxWork2->addItem(tr("Lawyer"));
	//ComboBoxWork2->addItem(tr("Soldier"));
	//setCellWidget(2, 3, ComboBoxWork2);
	//QSpinBox *SpiBoxIncome2 = new QSpinBox();
	//SpiBoxIncome2->setRange(1000, 10000);
	//setCellWidget(2, 4, SpiBoxIncome2);

	//QLabel *LabelPixmap3 = new QLabel();
	//LabelPixmap3->setPixmap(QPixmap(":/images/Female.png"));
	//setCellWidget(3, 0, LabelPixmap3);
	//QTableWidgetItem *TableWidgetItem3 = new QTableWidgetItem(tr("Alice"));
	//setItem(3, 1, TableWidgetItem3);
	//QDateTimeEdit *DateTimeEdit3 = new QDateTimeEdit();
	//DateTimeEdit3->setDateTime(QDateTime::currentDateTime());
	//DateTimeEdit3->setDisplayFormat("dd/M/yyyy");
	//DateTimeEdit3->setCalendarPopup(true);
	//setCellWidget(3, 2, DateTimeEdit3);
	//QComboBox *ComboBoxWork3 = new QComboBox();
	//ComboBoxWork3->addItem(tr("Worker"));
	//ComboBoxWork3->addItem(tr("Farmer"));
	//ComboBoxWork3->addItem(tr("Doctor"));
	//ComboBoxWork3->addItem(tr("Lawyer"));
	//ComboBoxWork3->addItem(tr("Soldier"));
	//setCellWidget(3, 3, ComboBoxWork3);
	//QSpinBox *SpiBoxIncome3 = new QSpinBox();
	//SpiBoxIncome3->setRange(1000, 10000);
	//setCellWidget(3, 4, SpiBoxIncome3);

	//QLabel *LabelPixmap4 = new QLabel();
	//LabelPixmap4->setPixmap(QPixmap(":/images/Male.png"));
	//setCellWidget(4, 0, LabelPixmap4);
	//QTableWidgetItem *TableWidgetItem4 = new QTableWidgetItem(tr("John"));
	//setItem(4, 1, TableWidgetItem4);
	//QDateTimeEdit *DateTimeEdit4 = new QDateTimeEdit();
	//DateTimeEdit4->setDateTime(QDateTime::currentDateTime());
	//DateTimeEdit4->setDisplayFormat("dd/M/yyyy");
	//DateTimeEdit4->setCalendarPopup(true);
	//setCellWidget(4, 2, DateTimeEdit4);
	//QComboBox *ComboBoxWork4 = new QComboBox();
	//ComboBoxWork4->addItem(tr("Worker"));
	//ComboBoxWork4->addItem(tr("Farmer"));
	//ComboBoxWork4->addItem(tr("Doctor"));
	//ComboBoxWork4->addItem(tr("Lawyer"));
	//ComboBoxWork4->addItem(tr("Soldier"));
	//setCellWidget(4, 3, ComboBoxWork4);
	//QSpinBox *SpiBoxIncome4 = new QSpinBox();
	//SpiBoxIncome4->setRange(1000, 10000);
	//setCellWidget(4, 4, SpiBoxIncome4);

	setColumnCount(3);
	int row = 0;
	//setRowCount(1);
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
	this->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	setColumnWidth(0, 230);
	setColumnWidth(1, 50);//设置第二列宽度50
	this->horizontalHeader()->setStretchLastSection(true);//列宽

	/*int rowIndex = this->rowCount();
	QTableWidgetItem *firstTableWidgetItem = new QTableWidgetItem("111");
	setItem(rowIndex-1, 0, firstTableWidgetItem);
	
	QTableWidgetItem *thirdTableWidgetItem = new QTableWidgetItem("222");
	setItem(rowIndex-1, 2, thirdTableWidgetItem);

	QPushButton *StatusBtn = new QPushButton();
	connect(StatusBtn, SIGNAL(clicked()), this, SLOT(On_Run_Btn()));
	StatusBtn->setText(QString::fromLocal8Bit("运行"));
	setCellWidget(rowIndex-1, 1, StatusBtn);*/
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

	QTableWidgetItem *thirdTableWidgetItem = new QTableWidgetItem(header2);
	setItem(rowIndex, 2, thirdTableWidgetItem);

	QPushButton *StatusBtn = new QPushButton();
	connect(StatusBtn, SIGNAL(clicked()), this, SLOT(On_Run_Btn()));
	StatusBtn->setText(QString::fromLocal8Bit("运行"));
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