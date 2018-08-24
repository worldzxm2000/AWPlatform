#include "MyDockWidgetTabBar.h"
#include "MyDockWidgetTabButton.h"
#include "MyDockWidget.h"
#include "Server_VS.h"
#include <QLayout>
#include <memory>

MyDockWidgetTabBar::MyDockWidgetTabBar(Qt::DockWidgetArea area)
	: m_area(area)
{
	setObjectName("DockWidgetBar");
	setStyleSheet("QToolTip{ color: white; background-color:rgb(77,77,77); border: none;}");
	setFloatable(false);
	setMovable(false);

	setContextMenuPolicy(Qt::PreventContextMenu);

	setOrientation(areaToOrientation(m_area));

	layout()->setSpacing(0);
	if (orientation() == Qt::Horizontal)
	{
		m_spacer = new QWidget();
		m_spacer->setFixedWidth(0);
		addWidget(m_spacer);
	}

	hide();
}

MyDockWidgetTabBar::~MyDockWidgetTabBar()
{
}

void MyDockWidgetTabBar::insertSpacing()
{
	if (m_spacer != nullptr) {
		m_spacer->setFixedWidth(26);
	}
}

void MyDockWidgetTabBar::removeSpacing()
{
	if (m_spacer != nullptr) {
		m_spacer->setFixedWidth(0);
	}
}

void MyDockWidgetTabBar::addDockWidget(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return;
	}

	MyDockWidgetTabButton* dockWidgetTabButton = new MyDockWidgetTabButton(dockWidget->windowTitle(), dockWidget->getArea());
	dockWidgetTabButton->setStyleSheet("background:rgb(100,100,100);color:white");
	connect(dockWidgetTabButton, &QPushButton::clicked, this, &MyDockWidgetTabBar::dockWidgetButton_clicked);

	m_tabs[dockWidgetTabButton] = dockWidget;

	QAction* action = addWidget(dockWidgetTabButton);
	dockWidgetTabButton->setAction(action);

	if (m_tabs.size() == 1) {
		show();
	}
}

bool MyDockWidgetTabBar::removeDockWidget(MyDockWidget* dockWidget)
{
	if (dockWidget == nullptr) {
		return false;
	}

	auto it = std::find_if(std::begin(m_tabs), std::end(m_tabs), [dockWidget](const std::pair<MyDockWidgetTabButton*, MyDockWidget*> v) {
		return v.second == dockWidget;
	});

	if (it == m_tabs.end()) {
		return false;
	}

	MyDockWidgetTabButton* dockWidgetTabButton = it->first;

	m_tabs.erase(it);

	removeAction(dockWidgetTabButton->getAction());

	if (m_tabs.empty()) {
		hide();
	}

	return true;
}

void MyDockWidgetTabBar::dockWidgetButton_clicked()
{
	MyDockWidgetTabButton* dockWidgetTabButton = dynamic_cast<MyDockWidgetTabButton*>(sender());
	if (dockWidgetTabButton == nullptr) {
		return;
	}

	auto it = m_tabs.find(dockWidgetTabButton);
	if (it == m_tabs.end()) {
		return;
	}

	emit signal_dockWidgetButton_clicked(it->second);
}
