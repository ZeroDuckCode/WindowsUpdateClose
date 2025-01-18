#include "MainUi.h"

MainUi::MainUi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUiClass())
{
    ui->setupUi(this);
}

MainUi::~MainUi()
{
    delete ui;
}
