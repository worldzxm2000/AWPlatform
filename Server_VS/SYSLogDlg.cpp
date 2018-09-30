#include "SYSLogDlg.h"
#include<qtooltip.h>
#include<QFile>
#include<QTextStream>
SYSLogDlg::SYSLogDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint|Qt::FramelessWindowHint|Qt::Tool);
	setFixedSize(623, 470);

	m_pLoadingLabel = new QLabel(this);
	m_pLoadingLabel->setGeometry(this->width()/2-75, this->height()/2-200, 200, 200);
	m_pTimer = new QTimer(this);

	// 设定超时时间100毫秒
	m_pTimer->setInterval(100);
	connect(m_pTimer, SIGNAL(timeout()), this,SLOT(updatePixmap()));
	StartAnimation();

	//读取线程
	readTxtThread =new ReadSYSLogTXT("SYSLog");
	connect(readTxtThread,SIGNAL(SendToUI(QStringList)), this, SLOT(GetLogTxt(QStringList)),Qt::BlockingQueuedConnection);
	connect(readTxtThread, SIGNAL(finished()), readTxtThread, SLOT(deleteLater()));
	connect(this, SIGNAL(SetFlagOverSignal()), readTxtThread, SLOT(EndThread()));
	readTxtThread->start();
	//pool.start(readTxtThread);
	//设置显示列表控件
	ui.DataListTable->setColumnCount(1);
	ui.DataListTable->setHorizontalHeaderLabels(QStringList() <<QString::fromLocal8Bit( "日志详情"));
    ui.DataListTable->verticalHeader()->setHidden(true);
	ui.DataListTable->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.DataListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.DataListTable->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.DataListTable->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.DataListTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(77,77,77);}"); //设置表头背景色
	ui.DataListTable->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.DataListTable->setMouseTracking(true);//tip提示
	connect(ui.DataListTable, SIGNAL(entered(QModelIndex)), this, SLOT(ShowToolTip(QModelIndex)));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	currentPage = 0;
	TotalPage = 0;
}

SYSLogDlg::SYSLogDlg( QString LogName,QWidget *parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);
	setFixedSize(623, 470);
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	if (LogName=="SYSLog")
	{
		ui.NameLabel->setText(QString::fromLocal8Bit( "运行日志"));
	}
	else
	{
		ui.NameLabel->setText(QString::fromLocal8Bit("终端日志"));

	}
	
	m_pLoadingLabel = new QLabel(this);
	m_pLoadingLabel->setGeometry(this->width() / 2 -80, this->height() / 2 - 150, 200, 200);
	m_pTimer = new QTimer(this);

	// 设定超时时间100毫秒
	m_pTimer->setInterval(100);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
	StartAnimation();

	//读取线程
	readTxtThread = new ReadSYSLogTXT(LogName);
	connect(readTxtThread, SIGNAL(SendToUI(QStringList)), this, SLOT(GetLogTxt(QStringList)), Qt::BlockingQueuedConnection);
	connect(readTxtThread, SIGNAL(finished()), readTxtThread, SLOT(deleteLater()));
	connect(this, SIGNAL(SetFlagOverSignal()), readTxtThread, SLOT(EndThread()));
	readTxtThread->start();
	//pool.start(readTxtThread);
	//设置显示列表控件
	ui.DataListTable->setColumnCount(1);
	ui.DataListTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("日志详情"));
	ui.DataListTable->verticalHeader()->setHidden(true);
	ui.DataListTable->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.DataListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.DataListTable->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.DataListTable->horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	ui.DataListTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(77,77,77);}"); //设置表头背景色
	ui.DataListTable->horizontalHeader()->setStretchLastSection(true);//列宽
	ui.DataListTable->setMouseTracking(true);//tip提示
	connect(ui.DataListTable, SIGNAL(entered(QModelIndex)), this, SLOT(ShowToolTip(QModelIndex)));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	currentPage = 0;
	TotalPage = 0;
}
SYSLogDlg::~SYSLogDlg()
{
}



void SYSLogDlg::slot_minWindow()
{
	this->showMinimized();
}

void SYSLogDlg::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void SYSLogDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void SYSLogDlg::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}
// 启动定时器
void SYSLogDlg::StartAnimation()
{
	m_pTimer->start();
}

// 停止定时器
void SYSLogDlg::StopAnimation()
{
	m_pLoadingLabel->hide();
	m_pTimer->stop();
}

// 更新图标
void SYSLogDlg::updatePixmap()
{
	// 若当前图标下标超过8表示到达末尾，重新计数。
	m_nIndex++;
	if (m_nIndex > 8)
		m_nIndex = 1;

	QPixmap pixmap(QString("..//Image//png//Loading%1.png").arg(m_nIndex));
	m_pLoadingLabel->setPixmap(pixmap);
}
void SYSLogDlg::ShowToolTip(QModelIndex index)
{
	if (!index.isValid()) {
		return;

	}

	QToolTip::showText(QCursor::pos(), index.data().toString());
}
//获取SYSLog数据
void SYSLogDlg::GetLogTxt(QStringList strlist)
{
	dataList = strlist;
	float f = float(dataList.count()) / 20.0;
	TotalPage = ceil(f);
	currentPage = 1;
	ui.PageDownBtn->setEnabled(false);
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("第1页"));
	ui.TotalPageabel->setText(QString::fromLocal8Bit("共")+QString::number(TotalPage)+ QString::fromLocal8Bit("页"));
	int len = strlist.count() <= 20 ? strlist.count() : 20;
	for (int i = 0; i < len; i++)
	{
		ui.DataListTable->insertRow(i);
		ui.DataListTable->setItem(i, 0, new QTableWidgetItem(dataList.at(i)));
	}
	StopAnimation();
}
//获取当前页数的数据
void SYSLogDlg:: GetDataInCurrentPage(int CurrentPage)
{
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("第")+QString::number(CurrentPage)+ QString::fromLocal8Bit("页"));
	int len = CurrentPage == TotalPage ? len = dataList.count() - (dataList.count() / 20) * 20 : 20;
	CurrentPage -= 1;
	ui.DataListTable->clearContents ();

	for (int i =0 ; i < len; i++)
	{
		ui.DataListTable->setItem(i, 0, new QTableWidgetItem(dataList.at(CurrentPage*20+i)));
	}
	ui.DataListTable->scrollToTop();
//	ui.DataListTable->setCursor(0);
}

//向前翻页
void SYSLogDlg::on_PageDownBtn_clicked()
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
void SYSLogDlg::on_PageUpBtn_clicked()
{
	//当前页数加一
	currentPage += 1;
	ui.PageDownBtn->setEnabled(true);
	//向前按钮变灰
	if (currentPage == TotalPage)
	{
		ui.PageUpBtn->setEnabled(false);

	}
	
	//填充数据列表
	GetDataInCurrentPage(currentPage);
}

//翻页至首页
void SYSLogDlg::on_PageToBeginBtn_clicked()
{
	ui.PageUpBtn->setEnabled(true);
	ui.PageDownBtn ->setEnabled(false);
	currentPage = 1;
	GetDataInCurrentPage(currentPage);
}

//翻页至末页
void SYSLogDlg::on_PageToEndBtn_clicked()
{
	ui.PageDownBtn->setEnabled(true);
	ui.PageUpBtn->setEnabled(false);
	currentPage = TotalPage;
	GetDataInCurrentPage(currentPage);
}

void SYSLogDlg::closeEvent(QCloseEvent *e)
{
	emit SetFlagOverSignal();
}