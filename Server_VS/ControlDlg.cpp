#include "ControlDlg.h"
#include<QMouseEvent>
#include<qDebug>
ControlDlg::ControlDlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	setStyleSheet("background:rgb(100,100,100);color:white;");
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));

	connect(ui.R_ALT_Btn, SIGNAL(clicked()),this,SLOT(SendComm()));
	connect(ui.R_BASEINFO_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.R_DATETIME_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.R_LAT_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.R_LONG_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.W_ALT_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.W_DATETIME_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.W_LAT_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.W_LONG_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
	connect(ui.R_DMTD_Btn, SIGNAL(clicked()), this, SLOT(SendComm()));
}

ControlDlg::~ControlDlg()
{
}

void ControlDlg::slot_minWindow()
{
	this->showMinimized();
}

void ControlDlg::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void ControlDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void ControlDlg::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}


void ControlDlg::show()
{
	ui.StationIDLabel->setText(StationID);
	ui.SrvNameLabel->setText(ServiceName);
	QWidget::show();
}

//发送命令
void ControlDlg::SendComm()
{
	QPushButton *button = (QPushButton*)sender();
	QString text = button->text();
	if (pEHT->GetEHT(ServiceName)==nullptr)
		return;
	unsigned int SocketID= pEHT->GetEHT(ServiceName)->GetSocket(StationID);
	QString Params1 = ui.ParamsEdit->text();
	Params1.trimmed();
	if (text== QString::fromLocal8Bit("读取基本信息"))
	{
		switch (ServiceID)
		{
		case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:

			break;
		default:
			QString Comm = "BASEINFO\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
	}
	else if (text == QString::fromLocal8Bit("读取时钟"))
	{
		switch (ServiceID)
		{
		case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:
		{
			int chk = 0;
			int SrcAdrr = StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x03;//帧长度
			bytes[2] = 0x82;//帧命令
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//源地址
			chk += bytes[3];
			bytes[4] = (SrcAdrr >> 8) & 0xff;
			chk += bytes[4];
			bytes[5] = chk & 0xff;//校验位 低八位
			bytes[6] = (chk >> 8) & 0xff;//高八位
			bytes[7] = 0xdd;
			::send(SocketID, (char *)bytes, 8, 0);
			break;
		}
		default:
		{
			QString Comm = "DATETIME\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		}
	}
	else if (text == QString::fromLocal8Bit("读取经度"))
	{
		switch (ServiceID)
		{
		case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:
		{
			int chk = 0;
			int SrcAdrr = StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x03;//帧长度
			bytes[2] = 0x82;//帧命令
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//源地址
			chk += bytes[3];
			bytes[4] = (SrcAdrr >> 8) & 0xff;
			chk += bytes[4];
			bytes[5] = chk & 0xff;//校验位 低八位
			bytes[6] = (chk >> 8) & 0xff;//高八位
			bytes[7] = 0xdd;
			::send(SocketID, (char *)bytes, 8, 0);
			break;
		}
		default:
		{
			QString Comm = "LONG\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		}
	} 
	else if (text == QString::fromLocal8Bit("读取纬度"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
		{
			QString Comm = "LAT\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		}
	}
	else if (text == QString::fromLocal8Bit("读取海拔高度"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
		{
			QString Comm = "ALT\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
		}
	} 
	else if (text == QString::fromLocal8Bit("设置经度"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
			QString Comm = "LONG " + Params1 + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
	}
	else if (text == QString::fromLocal8Bit("设置纬度"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
			QString Comm = "LAT " + Params1 + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
	}
	else if (text == QString::fromLocal8Bit("设置时钟"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
			QString Comm = "DATETIME " + Params1 + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
	}
	else   if (text == QString::fromLocal8Bit("设置海拔高度"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
			break;
		default:
			QString Comm = "ALT " + Params1 + "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
			break;
		}
	}
	else if(text==QString::fromLocal8Bit("读取数据"))
	{
		switch (ServiceID)
		{
		case TRSF: case TRSF_NM: case TRSF_XJ:
		{
			int chk = 0;
			int SrcAdrr = StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x03;//帧长度
			bytes[2] = 0x83;//帧命令
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//源地址
			chk += bytes[3];
			bytes[4] = (SrcAdrr >> 8) & 0xff;
			chk += bytes[4];
			bytes[5] = chk & 0xff;//校验位 低八位
			bytes[6] = (chk >> 8) & 0xff;//高八位
			bytes[7] = 0xdd;
			::send(SocketID, (char *)bytes, 8, 0);
		}
			break;
		default:
		{
			QString Comm = "SNAPSHOT\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
		}
			break;
		}
	}
	else if (text==QString::fromLocal8Bit("补抄数据"))
	{
		switch (ServiceID)
		{
		case TRSF_NM: case TRSF:case TRSF_XJ:case SH_TRSF_SQ:
		{
			QString yearB, monthB, dayB, hourB, minB, yearE, monthE, dayE, hourE, minE;
			yearB=ui.dateTimeEdit_B->sectionText(QDateTimeEdit::YearSection);
			monthB = ui.dateTimeEdit_B->sectionText(QDateTimeEdit::MonthSection);
			dayB = ui.dateTimeEdit_B->sectionText(QDateTimeEdit::DaySection);
			hourB = ui.dateTimeEdit_B->sectionText(QDateTimeEdit::HourSection);
			minB = ui.dateTimeEdit_B->sectionText(QDateTimeEdit::MinuteSection);
			
			yearE = ui.dateTimeEdit_E->sectionText(QDateTimeEdit::YearSection);
			monthE = ui.dateTimeEdit_E->sectionText(QDateTimeEdit::MonthSection);
			dayE = ui.dateTimeEdit_E->sectionText(QDateTimeEdit::DaySection);
			hourE = ui.dateTimeEdit_E->sectionText(QDateTimeEdit::HourSection);
			minE = ui.dateTimeEdit_E->sectionText(QDateTimeEdit::MinuteSection);
			int chk = 0;
			int SrcAdrr = StationID.toInt();
			BYTE bytes[1024] = { 0 };
			bytes[0] = 0xaa;
			bytes[1] = 0x0d;//帧长度
			bytes[2] = 0x94;//帧命令
			chk += bytes[2];
			bytes[3] = SrcAdrr & 0xff;//源地址
			chk += bytes[3];
			bytes[4] = (SrcAdrr >> 8) & 0xff;
			chk += bytes[4];
			bytes[5] = yearB.toInt()-2000;
			chk += bytes[5];
			bytes[6] = monthB.toInt();
			chk += bytes[6];
			bytes[7] = dayB.toInt();
			chk += bytes[7];
			bytes[8] = hourB.toInt();
			chk += bytes[8];
			bytes[9] = minB.toInt();
			chk += bytes[9];
			bytes[10] = yearE.toInt()-2000;
			chk += bytes[10];
			bytes[11] = monthE.toInt();
			chk += bytes[11];
			bytes[12] = dayE.toInt();
			chk += bytes[12];
			bytes[13] = hourE.toInt();
			chk += bytes[13];
			bytes[14] = minE.toInt();
			chk += bytes[14];
			bytes[15] = chk & 0xff;//校验位 低八位
			bytes[16] = (chk >> 8) & 0xff;//高八位
			bytes[17] = 0xdd;
			::send(SocketID, (char *)bytes, 18, 0);
		}
			break;
		default:
		{
			QString Time_B, Time_E;
			Time_B = ui.dateTimeEdit_B->dateTime().toString("yyyy-MM-dd HH:mm");
			Time_E = ui.dateTimeEdit_E->dateTime().toString("yyyy-MM-dd HH:mm");
			QString Comm = "DMTD " + Time_B +" "+ Time_E+ "\r\n";
			QByteArray ba = Comm.toLatin1();
			LPCSTR ch = ba.data();
			int len = Comm.length();
			::send(SocketID, ch, len, 0);
		}
			break;
		}
	}
	
}