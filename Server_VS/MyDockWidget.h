#pragma once

#include <QDockWidget>
#include"MyDockWidgetTitle.h"
class QPushButton;

class NXDockWidgetTabButton;
class NXMainWindow;
class NXDockWidgetTabBar;
class MyDockWidget;
class NXDockWidgetTitle;
class QVBoxLayout;

enum class DockWidgetState
{
	Unknown = -1,
	Docked = 0,    //! DockWidget is docked on MainWindow
	Floating = 1,  //! DockWidget is floating
	Hidden = 2,    //! DockWidget is auto hidden
	Closed = 3,    //! DockWidget is closed by button X
};
class MyDockWidget : public QDockWidget
{
	Q_OBJECT

public:
     explicit	MyDockWidget(const QString& title);
	~MyDockWidget();
public:
	QString windowTitle() const;
	void setWindowTitle(const QString& title);

	bool isMinimized() const { return (m_state == DockWidgetState::Hidden); }
	bool isDocked() const { return (m_state == DockWidgetState::Docked); }
	bool isFloating() const { return (m_state == DockWidgetState::Floating); }

	/*! Return current area of the dockwidget
	*/
	Qt::DockWidgetArea getArea() const { return m_area; }

	DockWidgetState getState() const { return m_state; }
	void setState(DockWidgetState state);

	void closeDockWidget();

	void setWidget(QWidget* widget);

	void setTabifiedDocks(const QList<QDockWidget*>& dockWidgetList);
	const std::vector<MyDockWidget*>& getTabifiedDocks() const { return m_tabifieds; }
	void clearTabifiedDocks() { m_tabifieds.clear(); }

	QAction* getMenuAction() const { return m_menuAction; }
	void setMenuAction(QAction* action) { m_menuAction = action; }

private:
	void autoHideStateToggle();
	void updateDockLocation(Qt::DockWidgetArea area);
	void updateTopLevelState(bool topLevel);
	void removeFromTabifiedDocks(MyDockWidget* dockWidget);

protected:
	virtual bool event(QEvent* event) override;

signals:
	void signal_pinned(MyDockWidget* dockWidget);
	void signal_unpinned(MyDockWidget* dockWidget);
	void signal_docked(MyDockWidget* dockWidget);
	void signal_undocked(MyDockWidget* dockWidget);
	void signal_close(MyDockWidget *dockWidget);
	private slots:
	void slot_menuAction() {}

private:
	Qt::DockWidgetArea m_area;
	MyDockWidgetTitle* m_titleWidget;
	DockWidgetState m_state;
	QVBoxLayout* m_layout;
	std::vector<MyDockWidget*> m_tabifieds;
	QAction* m_menuAction;
};
