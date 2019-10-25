#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	init_bfm();
	
	MainWindow w;
	w.show();

	return a.exec();
}
