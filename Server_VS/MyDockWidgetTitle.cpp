#include "MyDockWidgetTitle.h"
#include"MyDockWidget.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QPushButton>

static const QString s_autoHideDisabledStyle =
R"(QPushButton
{
	border: 0px;
	width: 15px; height: 15px;
    image: url("../Image/png/pin_dockwidget_normal.png");
}
QPushButton:hover {
    image: url("../Image/png/pin_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url("../Image/png/pin_dockwidget_pressed.png");
})";

static const QString s_autoHideEnabledStyle =
R"(QPushButton 
{
	border: 0px;
	width: 15px; height: 15px;
    image: url("../Image/png/unpin_dockwidget_normal.png");
}
QPushButton:hover {
    image: url("../Image/png/unpin_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url("../Image/png/unpin_dockwidget_pressed.png");
})";

static const QString s_closeButtonStyle =
R"(QPushButton 
{
	border: 0px;
	width: 15px; height: 15px;
    image: url("../Image/png/close_dockwidget_normal.png");
}
QPushButton:hover {
    image: url("../Image/png/close_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url("../Image/png/close_dockwidget_pressed.png");
})";

MyDockWidgetTitle::MyDockWidgetTitle()
	: QFrame(nullptr)
	, m_LMPressed(false)
	, m_autoHideEnabled(false)
	, m_textLabel(nullptr)
{
	setObjectName("DockWidgetTitle");

	QHBoxLayout* layout = new QHBoxLayout();
	setLayout(layout);

	layout->setContentsMargins(3, 2, 3, 2);
	layout->setSpacing(1);

	m_textLabel = new QLabel();

	layout->addWidget(m_textLabel);

	layout->addStretch(1);

	m_autoHideButton = new QPushButton();
	m_autoHideButton->setStyleSheet(s_autoHideDisabledStyle);
	m_autoHideButton->setToolTip(QString::fromLocal8Bit("自动隐藏"));
	m_autoHideEnabled = true;
	layout->addWidget(m_autoHideButton);

	m_closeButton = new QPushButton();
	m_closeButton->setStyleSheet(s_closeButtonStyle);
	m_closeButton->setToolTip(QString::fromLocal8Bit("关闭"));
	layout->addWidget(m_closeButton);

	connect(m_autoHideButton, &QPushButton::clicked, this, &MyDockWidgetTitle::autoHideButton_pressed);
	connect(m_closeButton, &QPushButton::clicked, this, &MyDockWidgetTitle::closeButton_pressed);
}

MyDockWidgetTitle::~MyDockWidgetTitle()
{
}

void MyDockWidgetTitle::mousePressEvent(QMouseEvent* event)
{
	if ((event->button() == Qt::LeftButton) && m_autoHideEnabled) {
		m_LMPressed = true;
	}

	QFrame::mousePressEvent(event);
}

void MyDockWidgetTitle::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_LMPressed = false;
	}

	QFrame::mouseReleaseEvent(event);
}

void MyDockWidgetTitle::mouseMoveEvent(QMouseEvent* event)
{
	if (m_LMPressed)
	{
		MyDockWidget* dockWidget = static_cast<MyDockWidget*>(parentWidget());
		if (dockWidget != nullptr)
		{
			m_LMPressed = false;

			dockWidget->setFloating(true);

			event = new QMouseEvent(QEvent::MouseButtonPress,
				event->pos(),
				mapToGlobal(event->pos()),
				Qt::LeftButton,
				Qt::LeftButton,
				Qt::NoModifier);

			QCoreApplication::postEvent(this, event);
		}
	}

	QFrame::mouseMoveEvent(event);
}

void MyDockWidgetTitle::setAutoHideEnadled(bool enabled)
{
	m_autoHideEnabled = enabled;

	if (enabled) {
		m_autoHideButton->setStyleSheet(s_autoHideEnabledStyle);
	}
	else {
		m_autoHideButton->setStyleSheet(s_autoHideDisabledStyle);
	}
}


void MyDockWidgetTitle::setFloating(bool state)
{
	m_autoHideButton->setVisible(state);
}
