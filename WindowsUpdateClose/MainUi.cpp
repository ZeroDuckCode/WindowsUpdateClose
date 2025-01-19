#include "MainUi.h"

MainUi::MainUi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUiClass())
{
    ui->setupUi(this);

    connect(ui->pushButton_Reg, &QPushButton::clicked, this, &MainUi::RegClose);
    connect(ui->pushButton_ServerClose, &QPushButton::clicked, this, &MainUi::BnServerClose);
    connect(ui->pushButton_ServerOpen, &QPushButton::clicked, this, &MainUi::BnServerOpen);
    connect(ui->pushButton_ServerSelect, &QPushButton::clicked, this, &MainUi::UpdateServerStatus);

    ui->label_auther->setOpenExternalLinks(true);

    QPixmap pixmap(":/MainUi/pic/chigua.png");
    pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ServerInfo->setPixmap(pixmap);

    Init();
}

MainUi::~MainUi()
{
    delete ui;
}

void MainUi::RegClose()
{
    bool ret = RegSetting();
    if (ret) {
        QMessageBox::information(this, u8"提示", u8"注册表修改成功");
    }
    else
    {
        QMessageBox::information(this, u8"提示", u8"注册表修改失败");
    }
    return;
}

void MainUi::BnServerClose()
{
    bool ret = ServerClose();
    if (ret) {
        QMessageBox::information(this, u8"提示", u8"服务关闭成功");
    }
    else
    {
        QMessageBox::information(this, u8"提示", u8"服务关闭失败");
    }
    return;
}

void MainUi::BnServerOpen()
{
    bool ret = ServerOpen();
    if (ret) {
        QMessageBox::information(this, u8"提示", u8"服务打开成功");
    }
    else
    {
        QMessageBox::information(this, u8"提示", u8"服务打开失败");
    }
    return;
}

void MainUi::UpdateServerStatus()
{
    bool ret = SelectServerState();
    if (ret == 0) {
        //服务关闭
        ui->label_ServerStatus->setText(u8"服务状态:已经关闭");
        QPixmap pixmap(":/MainUi/pic/guzhang.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
    else if (ret==1) {
        //服务打开
        ui->label_ServerStatus->setText(u8"服务状态:正在运行");
        QPixmap pixmap(":/MainUi/pic/cry.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
    else {
        //服务状态未知
        ui->label_ServerStatus->setText(u8"服务状态:未知");
        QPixmap pixmap(":/MainUi/pic/dalian.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
}

void MainUi::Init()
{
    UpdateServerStatus();
}
