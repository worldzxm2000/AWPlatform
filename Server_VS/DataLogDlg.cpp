#include "DataLogDlg.h"
#include"qtooltip.h"
DataLogDlg::DataLogDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setFixedSize(623, 470);
	setWindowFlags(Qt::WindowCloseButtonHint);
	//读取线程
	ReadSYSLogTXT *readTxtThread= new ReadSYSLogTXT("DataLog");
	connect(readTxtThread, SIGNAL(SendToUI(QStringList)), this, SLOT(GetLogTxt(QStringList)), Qt::BlockingQueuedConnection);
	connect(readTxtThread, &QThread::finished, this, &QObject::deleteLater);
	readTxtThread->start();
	//设置显示列表控件
	ui.DataListTable->setColumnCount(1);
	ui.DataListTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("日志详情"));
	ui.DataListTable->verticalHeader()->setHidden(true);
	ui.DataListTable->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.DataListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.DataListTable->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.DataListTable->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.DataListTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	ui.DataListTable->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.DataListTable->setMouseTracking(true);//tip提示
	connect(ui.DataListTable, SIGNAL(entered(QModelIndex)), this, SLOT(ShowToolTip(QModelIndex)));
	currentPage = 0;
	TotalPage = 0;
}

DataLogDlg::~DataLogDlg()
{
	delete readTxtThread;
	readTxtThread = NULL;
}

void DataLogDlg::ShowToolTip(QModelIndex index)
{
	if (!index.isValid()) {
		return;

	}

	QToolTip::showText(QCursor::pos(), index.data().toString());
}
//获取SYSLog数据
void DataLogDlg::GetLogTxt(QStringList strlist)
{
	dataList = strlist;
	float f = float(dataList.count()) / 20.0;
	TotalPage = ceil(f);
	currentPage = 1;
	ui.PageDownBtn->setEnabled(false);
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("第1页"));
	ui.TotalPageabel->setText(QString::fromLocal8Bit("共") + QString::number(TotalPage) + QString::fromLocal8Bit("页"));
	int len = strlist.count()<= 20 ? strlist.count() : 20;
	for (int i = 0; i < len; i++)
	{
		ui.DataListTable->insertRow(i);
		ui.DataListTable->setItem(i, 0, new QTableWidgetItem(dataList.at(i)));
	}
}
//获取当前页数的数据
void DataLogDlg::GetDataInCurrentPage(int CurrentPage)
{
	if (TotalPage < 1)
		return;
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("第") + QString::number(CurrentPage) + QString::fromLocal8Bit("页"));
	int len = CurrentPage == TotalPage ? len = dataList.count() - (dataList.count() / 20) * 20 : 20;
	CurrentPage -= 1;
	ui.DataListTable->clearContents();

	for (int i = 0; i < len; i++)
	{
		ui.DataListTable->setItem(i, 0, new QTableWidgetItem(dataList.at(CurrentPage * 20 + i)));
	}
	ui.DataListTable->scrollToTop();
	//	ui.DataListTable->setCursor(0);
}

//向前翻页
void DataLogDlg::on_PageDownBtn_clicked()
{
	//当前页数减一
	currentPage -= 1;
	ui.PageUpBtn->setEnabled(true);
	//向前按钮变灰
	if (currentPage < 2)
	{
		ui.PageDownBtn->setEnabled(false);
		ui.PageToBeginBtn->setFocus();
	}
		
	//只有一页
	if (currentPage == 0)
		return;
	//填充数据列表
	GetDataInCurrentPage(currentPage);
}

//向后翻页
void DataLogDlg::on_PageUpBtn_clicked()
{
	//当前页数加一
	currentPage += 1;
	ui.PageDownBtn->setEnabled(true);
	//向前按钮变灰
	if (currentPage ==TotalPage)
		ui.PageUpBtn->setEnabled(false);

	//填充数据列表
	GetDataInCurrentPage(currentPage);
}

//翻页至首页
void DataLogDlg::on_PageToBeginBtn_clicked()
{
	ui.PageUpBtn->setEnabled(true);
	ui.PageDownBtn->setEnabled(false);
	currentPage = 1;
	GetDataInCurrentPage(currentPage);
}

//翻页至末页
void DataLogDlg::on_PageToEndBtn_clicked()
{
	ui.PageDownBtn->setEnabled(true);
	ui.PageUpBtn->setEnabled(false);
	currentPage = TotalPage;
	GetDataInCurrentPage(currentPage);
}

void DataLogDlg::closeEvent(QCloseEvent *e)
{
	emit SetFlagOverSignal();
}