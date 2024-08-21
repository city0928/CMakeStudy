#include "QtWidgetClass.h" 
#include <QtWidgets/QApplication>

#include "Button/CustomButton.h"


int main(int argc, char *argv[]) 
{
	QApplication a(argc, argv);
	QtWidgetClass w;
	w.show();

	CustomButton waw(900);
	waw.show();
	return a.exec();
}