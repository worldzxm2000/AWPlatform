#pragma once

#include <QWidget>
#include "ui_test.h"
#include"BaseWindow.h"
class test : public BaseWindow
{
	Q_OBJECT

public:
	test(QWidget *parent = Q_NULLPTR);
	~test();

private:
	Ui::test ui;
};
