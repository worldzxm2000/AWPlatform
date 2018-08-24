#include "DataLogDlg.h"
#include"qtooltip.h"
DataLogDlg::DataLogDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setFixedSize(623, 470);
	setWindowFlags(Qt::WindowCloseButtonHint);
	//¶ÁÈ¡Ïß³Ì
	ReadSYSLogTXT *readTxtThread= new ReadSYSLogTXT("DataLog");
	connect(readTxtThread, SIGNAL(SendToUI(QStringList)), this, SLOT(GetLogTxt(QStringList)), Qt::BlockingQueuedConnection);
	connect(readTxtThread, &QThread::finished, this, &QObject::deleteLater);
	readTxtThread->start();
	//ÉèÖÃÏÔÊ¾ÁÐ±í¿Ø¼þ
	ui.DataListTable->setColumnCount(1);
	ui.DataListTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("ÈÕÖ¾ÏêÇé"));
	ui.DataListTable->verticalHeader()->setHidden(true);
	ui.DataListTable->setSelectionBehavior(QAbstractItemView::SelectRows);//ÕûÐÐÑ¡ÖÐµÄ·½Ê½
	ui.DataListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//½ûÖ¹ÐÞ¸Ä
	ui.DataListTable->setSelectionMode(QAbstractItemView::SingleSelection);//¿ÉÒÔÑ¡ÖÐµ¥¸ö
	ui.DataListTable->horizontalHeader()->setHighlightSections(false);//½ûÖ¹±íÍ·Ñ¡ÖÐ¸ßÁÁ
	ui.DataListTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //ÉèÖÃ±íÍ·±³¾°É«
	ui.DataListTable->horizontalHeader()->setStretchLastSection(true);//ÁÐ¿í
	ui.DataListTable->setMouseTracking(true);//tipÌáÊ¾
	connect(ui.DataListTable, SIGNAL(entered(QModelIndex)), this, SLOT(ShowToolTip(QModelIndex)));
	currentPage = 0;
	TotalPage = 0;
}

DataLogDlg::~DataLogDlg()
{
}



void DataLogDlg::slot_minWindow()
{
	this->showMinimized();
}

void DataLogDlg::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void DataLogDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void DataLogDlg::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}
// 启动定时器
void DataLogDlg::StartAnimation()
{
	m_pTimer->start();
}

// 停止定时器
void DataLogDlg::StopAnimation()
{
	m_pLoadingLabel->hide();
	m_pTimer->stop();
}

// 更新图标
void DataLogDlg::updatePixmap()
{
	// 若当前图标下标超过8表示到达末尾，重新计数。
	m_nIndex++;
	if (m_nIndex > 8)
		m_nIndex = 1;

	QPixmap pixmap(QString("F:\\Server_VS\\Image\\png\\Loading%1.png").arg(m_nIndex));
	m_pLoadingLabel->setPixmap(pixmap);
}
void DataLogDlg::ShowToolTip(QModelIndex index)
{
	if (!index.isValid()) {
		return;

	}

	QToolTip::showText(QCursor::pos(), index.data().toString());
}
//获取DataLog数据
void DataLogDlg::GetLogTxt(QStringList strlist)
{
	dataList = strlist;
	float f = float(dataList.count()) / 20.0;
	TotalPage = ceil(f);
	currentPage = 1;
	ui.PageDownBtn->setEnabled(false);
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("第一页"));
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

//ÏòÇ°·­Ò³
void DataLogDlg::on_PageDownBtn_clicked()
{
	//µ±Ç°Ò³Êý¼õÒ»
	currentPage -= 1;
	ui.PageUpBtn->setEnabled(true);
	//ÏòÇ°°´Å¥±ä»Ò
	if (currentPage < 2)
	{
		ui.PageDownBtn->setEnabled(false);
		ui.PageToBeginBtn->setFocus();
	}
		
	//Ö»ÓÐÒ»Ò³
	if (currentPage == 0)
		return;
	//Ìî³äÊý¾ÝÁÐ±í
	GetDataInCurrentPage(currentPage);
}

//Ïòºó·­Ò³
void DataLogDlg::on_PageUpBtn_clicked()
{
	//µ±Ç°Ò³Êý¼ÓÒ»
	currentPage += 1;
	ui.PageDownBtn->setEnabled(true);
	//ÏòÇ°°´Å¥±ä»Ò
	if (currentPage ==TotalPage)
		ui.PageUpBtn->setEnabled(false);

	//Ìî³äÊý¾ÝÁÐ±í
	GetDataInCurrentPage(currentPage);
}

//·­Ò³ÖÁÊ×Ò³
void DataLogDlg::on_PageToBeginBtn_clicked()
{
	ui.PageUpBtn->setEnabled(true);
	ui.PageDownBtn->setEnabled(false);
	currentPage = 1;
	GetDataInCurrentPage(currentPage);
}

//·­Ò³ÖÁÄ©Ò³
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