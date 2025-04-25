#include "nissywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NissyWindow w;
	w.show();
	return a.exec();
}
