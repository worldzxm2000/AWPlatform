#include "DataLogDlg.h"
#include"ReadSYSLogTXT.h"
#include"qtooltip.h"
DataLogDlg::DataLogDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setFixedSize(623, 470);
	setWindowFlags(Qt::WindowCloseButtonHint);
	ReadSYSLogTXT *readTxtThread = new ReadSYSLogTXT("DataLog");
	connect(readTxtThread, SIGNAL(SendToUI(QStringList)), this, SLOT(GetLogTxt(QStringList)));
	pool.start(readTxtThread);
	//������ʾ�б�ؼ�
	ui.DataListTable->setColumnCount(1);
	ui.DataListTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("��־����"));
	ui.DataListTable->verticalHeader()->setHidden(true);
	ui.DataListTable->setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ�еķ�ʽ
	ui.DataListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�޸�
	ui.DataListTable->setSelectionMode(QAbstractItemView::SingleSelection);//����ѡ�е���
	ui.DataListTable->horizontalHeader()->setHighlightSections(false);//��ֹ��ͷѡ�и���
	ui.DataListTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	ui.DataListTable->horizontalHeader()->setStretchLastSection(true);//�п�
	ui.DataListTable->setMouseTracking(true);//tip��ʾ
	connect(ui.DataListTable, SIGNAL(entered(QModelIndex)), this, SLOT(ShowToolTip(QModelIndex)));
}

DataLogDlg::~DataLogDlg()
{
}

void DataLogDlg::ShowToolTip(QModelIndex index)
{
	if (!index.isValid()) {
		return;

	}

	QToolTip::showText(QCursor::pos(), index.data().toString());
}
//��ȡSYSLog����
void DataLogDlg::GetLogTxt(QStringList strlist)
{
	dataList = strlist;
	float f = float(dataList.count()) / 20.0;
	TotalPage = ceil(f);
	currentPage = 1;
	ui.PageDownBtn->setEnabled(false);
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("��1ҳ"));
	ui.TotalPageabel->setText(QString::fromLocal8Bit("��") + QString::number(TotalPage) + QString::fromLocal8Bit("ҳ"));
	int len = strlist.count()<= 20 ? strlist.count() : 20;
	for (int i = 0; i < len; i++)
	{
		ui.DataListTable->insertRow(i);
		ui.DataListTable->setItem(i, 0, new QTableWidgetItem(dataList.at(i)));
	}
}
//��ȡ��ǰҳ��������
void DataLogDlg::GetDataInCurrentPage(int CurrentPage)
{
	ui.CurrentPageLabel->setText(QString::fromLocal8Bit("��") + QString::number(CurrentPage) + QString::fromLocal8Bit("ҳ"));
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

//��ǰ��ҳ
void DataLogDlg::on_PageDownBtn_clicked()
{
	//��ǰҳ����һ
	currentPage -= 1;
	ui.PageUpBtn->setEnabled(true);
	//��ǰ��ť���
	if (currentPage < 2)
		ui.PageDownBtn->setEnabled(false);
	//��������б�
	GetDataInCurrentPage(currentPage);
}

//���ҳ
void DataLogDlg::on_PageUpBtn_clicked()
{
	//��ǰҳ����һ
	currentPage += 1;
	ui.PageDownBtn->setEnabled(true);
	//��ǰ��ť���
	if (currentPage + 1 > TotalPage)
	{
		ui.PageUpBtn->setEnabled(false);
		return;
	}

	//��������б�
	GetDataInCurrentPage(currentPage);
}

//��ҳ����ҳ
void DataLogDlg::on_PageToBeginBtn_clicked()
{
	ui.PageUpBtn->setEnabled(true);
	ui.PageDownBtn->setEnabled(false);
	currentPage = 1;
	GetDataInCurrentPage(currentPage);
}

//��ҳ��ĩҳ
void DataLogDlg::on_PageToEndBtn_clicked()
{
	ui.PageDownBtn->setEnabled(true);
	ui.PageUpBtn->setEnabled(false);
	currentPage = TotalPage;
	GetDataInCurrentPage(currentPage);
}
