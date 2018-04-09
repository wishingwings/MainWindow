#include "mainwindow.h"
#include "rect.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	
	//w.pScene->addItem(item_rect);
	w.show();
	
	
	return a.exec();
}
