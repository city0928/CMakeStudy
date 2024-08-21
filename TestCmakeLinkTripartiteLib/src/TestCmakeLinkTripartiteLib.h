#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestCmakeLinkTripartiteLib.h"

class TestCmakeLinkTripartiteLib : public QWidget
{
    Q_OBJECT

public:
    TestCmakeLinkTripartiteLib(QWidget *parent = nullptr);
    ~TestCmakeLinkTripartiteLib();

private:
    Ui::TestCmakeLinkTripartiteLibClass ui;
};
