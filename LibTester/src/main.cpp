#include <QtWidgets/QApplication>

#include "Button/CustomButton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CustomButton ww(900);
    ww.buttonOperation();
    ww.show();

    return a.exec();
}
