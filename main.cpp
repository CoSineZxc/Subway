#include"SubwayDemo.h"
#include<QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SubwayDemo w;
	w.show();
	return a.exec();
}

