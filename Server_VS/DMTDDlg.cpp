#include "DMTDDlg.h"
#include<process.h>
#include<qfiledialog.h>
#include<qfile.h>
#include<qtextstream.h>
#include<Windows.h>
#include<qjsonobject.h>
#include<qjsondocument.h>
#include"LogWrite.h"
#include<qmessagebox.h>

DMTDDlg::DMTDDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this); 
	setWindowFlags(Qt::WindowCloseButtonHint);
	setFixedSize(525, 160);
	ui.DoingBar->setWindowTitle(QString::fromLocal8Bit("上传要素数据"));
	//读取TXT线程初始化
	loadTxtThread = new LoadTxtThread();
	
	connect(loadTxtThread, SIGNAL(finished()), this, SLOT(LoadTxtThreadFinish()),Qt::QueuedConnection);
	connect(loadTxtThread, SIGNAL(CountOfStrSignal(int)), this, SLOT(QLabelSlot(int)));
	connect(loadTxtThread, SIGNAL(SendJson(QJsonObject)), this, SLOT(RecJsonData(QJsonObject)));
	//上传线程初始化
	impDataThread = new ImpDataThread();
	connect(impDataThread, SIGNAL(finished()), this, SLOT(ImpDataThreadFinish()), Qt::QueuedConnection);
	connect(impDataThread, SIGNAL(ProcessingSignal(int)), this, SLOT(QProcessBarSlot(int)));
	connect(impDataThread, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorMSG(int)));
}

DMTDDlg::~DMTDDlg()
{

}

//读取TXT线程结束
void DMTDDlg::LoadTxtThreadFinish()
{
	loadTxtThread->isRun = false;
	ui.DoingBar->setRange(0, totalCount);
	ui.NumberLabel->setText(QString::fromLocal8Bit("共计:")+QString::number(totalCount));
	
}

//导入线程结束
void DMTDDlg::ImpDataThreadFinish()
{
	ui.ImpBtn->setEnabled(true);
	QMessageBox::about(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("上传完毕!"));

}

//刷新数据个数
void DMTDDlg::QLabelSlot(int count)
{
	ui.NumberLabel->setText(QString::number(count));
	totalCount = count;
}

//上传进度条
void DMTDDlg::QProcessBarSlot(int count)
{
	ui.DoingBar->setValue(count);
}
//接收数据
void DMTDDlg::RecJsonData(QJsonObject json)
{
	JsonList.append(json);
}

void DMTDDlg::GetErrorMSG(int Result)
{
	emit ErrorMSGSignal(Result);
}
//浏览文件夹按钮事件
void DMTDDlg::on_BrowsingBtn_clicked()
{
	JsonList.clear();
	ui.NumberLabel->setText(QString::fromLocal8Bit("0") );
	ui.DoingBar->setValue(0);
	ui.DoingBar->setRange(0, 0);
	QFileDialog *fileDialog = new QFileDialog(this);
	
	fileDialog->setFileMode(QFileDialog::Directory);
	
	if (fileDialog->exec() != QDialog::Accepted)
	{
		path = "";
		ui.PathLineEdit->setText(path);
		return;
	}
	path= fileDialog->selectedFiles()[0];
	ui.PathLineEdit->setText(path);
	loadTxtThread->path = path;
	loadTxtThread->func_Char2Json = func_Char2Json;
	loadTxtThread->isRun = true;
	loadTxtThread->start();


}


//导入按钮事件
void DMTDDlg::on_ImpBtn_clicked()
{
	ui.ImpBtn->setEnabled(false);
	impDataThread->JsonList = JsonList;
	impDataThread->start();
}

//关闭窗体
void DMTDDlg::closeEvent(QCloseEvent *event)
{
    loadTxtThread->isRun = false;
	loadTxtThread->deleteLater();
	impDataThread->deleteLater();
	WaitForSingleObject(this, 3000);//等待线程结束
}
