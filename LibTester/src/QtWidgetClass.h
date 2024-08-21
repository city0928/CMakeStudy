#pragma once

#include <QWidget>
#include "ui_QtWidgetClass.h"

class QtWidgetClass : public QWidget
{
  Q_OBJECT;

public:
	QtWidgetClass(QWidget *parent = nullptr);
	~QtWidgetClass();

private:
	Ui::QtWidgetClass ui;

};
