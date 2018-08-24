#include "MyDockWidget.h"
#include"Server_VS.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QToolBar>
#include "qcoreevent.h"
#include <QEvent>
#include <iostream>

MyDockWidget::MyDockWidget(const QString& title)
	: QDockWidget(nullptr)
	, m_area(Qt::NoDockWidgetArea)
	, m_state(DockWidgetState::Unknown)
{
	setObjectName("DockWidget");
	m_titleWidget = new MyDockWidgetTitle();
	setWindowTitle(title);

	setTitleBarWidget(m_titleWidget);

	
	m_layout = new QVBoxLayout;
	m_layout->setContentsMargins(0, 2, 0, 0);

	QWidget* widget = new QWidget();
	widget->setLayout(m_layout);
	QDockWidget::setWidget(widget);


	connect(m_titleWidget, &MyDockWidgetTitle::autoHideButton_pressed, this, &MyDockWidget::autoHideStateToggle);
	connect(m_titleWidget, &MyDockWidgetTitle::closeButton_pressed, this, &MyDockWidget::closeDockWidget);

	connect(this, &QDockWidget::dockLocationChanged, this, &MyDockWidget::updateDockLocation);
	connect(this, &QDockWidget::topLevelChanged, this, &MyDockWidget::updateTopLevelState);
	hide();
}

MyDockWidget::~MyDockWidget()
{
	
}

QString MyDockWidget::windowTitle() const
{
	return m_titleWidget->getText();
}

void MyDockWidget::setWindowTitle(const QString& text)
{
	QString title = text.isEmpty() ? "Noname" : text;

	m_titleWidget->setText(title);
	QDockWidget::setWindowTitle(title);
}

void MyDockWidget::closeDockWidget()
{
	if (isMinimized()) {
		emit signal_pinned(this);
	}

	emit signal_close(this);
	setState(DockWidgetState::Closed);
	
	hide();
}


void MyDockWidget::autoHideStateToggle()
{
	if (isMinimized())
	{
		setState(DockWidgetState::Docked);
		emit signal_pinned(this);
	}
	else
	{
		setState(DockWidgetState::Hidden);
		emit signal_unpinned(this);
	}
}

void MyDockWidget::updateDockLocation(Qt::DockWidgetArea area)
{
	m_area = area;

	if (m_area != Qt::NoDockWidgetArea) {
		updateTopLevelState(false);
	}
}

void MyDockWidget::updateTopLevelState(bool topLevel)
{
	m_titleWidget->setAutoHideEnadled(false);

	if (topLevel)
	{
		setState(DockWidgetState::Floating);

		std::for_each(m_tabifieds.begin(), m_tabifieds.end(), [&](MyDockWidget* dockWidget) {
			dockWidget->removeFromTabifiedDocks(this);
		});

		clearTabifiedDocks();

		emit signal_undocked(this);
	}
	else
	{
		setState(DockWidgetState::Docked);

		QList<QDockWidget*> tabifiedDockWidgetList = static_cast<Server_VS*>(parentWidget())->tabifiedDockWidgets(this);
		tabifiedDockWidgetList.push_back(this);

		std::for_each(std::begin(tabifiedDockWidgetList), std::end(tabifiedDockWidgetList), [&](QDockWidget* qDockWidget) {
			qobject_cast<MyDockWidget*>(qDockWidget)->setTabifiedDocks(tabifiedDockWidgetList);
		});

		emit signal_docked(this);
	}
}

void MyDockWidget::setState(DockWidgetState state)
{
	m_state = state;

	switch (state)
	{
	case DockWidgetState::Docked:
		m_titleWidget->setFloating(true);
		break;
	case DockWidgetState::Floating:
		m_titleWidget->setFloating(false);
		break;
	case DockWidgetState::Hidden:
		m_titleWidget->setAutoHideEnadled(true);
		break;
	case DockWidgetState::Closed:
		break;
	default:
		break;
	}
}

bool MyDockWidget::event(QEvent* event)
{
	//	qDebug() << event->type();

	if (event->type() == QEvent::Enter)
	{

	}
	else if (event->type() == QEvent::Leave)
	{

	}
	else if (event->type() == QEvent::FocusOut)
	{

	}

	// Make sure the rest of events are handled
	return QDockWidget::event(event);
}

void MyDockWidget::setWidget(QWidget* widget)
{
	m_layout->addWidget(widget);
}

void MyDockWidget::setTabifiedDocks(const QList<QDockWidget*>& dockWidgetList)
{
	m_tabifieds.clear();

	std::transform(std::begin(dockWidgetList), std::end(dockWidgetList), std::back_inserter(m_tabifieds), [&](QDockWidget* qDockWidget) {
		return static_cast<MyDockWidget*>(qDockWidget);
	});
}

void MyDockWidget::removeFromTabifiedDocks(MyDockWidget* dockWidget)
{
	m_tabifieds.erase(std::remove(std::begin(m_tabifieds), std::end(m_tabifieds), dockWidget), std::end(m_tabifieds));
}