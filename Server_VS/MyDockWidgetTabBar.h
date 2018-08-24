#pragma once

#include <QToolBar>

class MyDockWidgetTabButton;
class MyDockWidget;

class MyDockWidgetTabBar : public QToolBar
{
	Q_OBJECT
public:
	explicit MyDockWidgetTabBar(Qt::DockWidgetArea area);
	~MyDockWidgetTabBar();

public:
	void addDockWidget(MyDockWidget* dockWidget);
	bool removeDockWidget(MyDockWidget* dockWidget);

	void insertSpacing();
	void removeSpacing();

private:
	void dockWidgetButton_clicked();

signals:
	void signal_dockWidgetButton_clicked(MyDockWidget* dockWidget);

private:
	Qt::DockWidgetArea m_area;
	QWidget* m_spacer;
	std::map<MyDockWidgetTabButton*, MyDockWidget*> m_tabs;
};
