#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainUi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainUiClass; };
QT_END_NAMESPACE

class MainUi : public QMainWindow
{
    Q_OBJECT

public:
    MainUi(QWidget *parent = nullptr);
    ~MainUi();

private:
    Ui::MainUiClass *ui;
};
