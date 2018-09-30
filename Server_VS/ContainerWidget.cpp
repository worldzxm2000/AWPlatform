#include "ContainerWidget.h"

ContainerWidget::ContainerWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setGeometry(100, 100, 1024, 720);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);
	MainWidget = new QWidget(this);
	MainWidget->setGeometry(2, 35, this->width(),this->height()- 35);
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ContainerWidget::~ContainerWidget()
{
}

void ContainerWidget::slot_minWindow()
{
	this->showMinimized();
}

void ContainerWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void ContainerWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void ContainerWidget::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}
void ContainerWidget::show()
{
	ui.groupBox_6->setGeometry(QRect(this->width() - 50, 2, 46, 26));
	 QDialog::show();
}