#include "QtWidgetClass.h"

QtWidgetClass::QtWidgetClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtWidgetClass::~QtWidgetClass()
{
}
