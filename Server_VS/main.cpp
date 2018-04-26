#include "server_vs.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Server_VS w;
	w.show();
	return a.exec();
}
