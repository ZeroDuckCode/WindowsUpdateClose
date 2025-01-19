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
        QMessageBox::information(this, u8"��ʾ", u8"ע����޸ĳɹ�");
    }
    else
    {
        QMessageBox::information(this, u8"��ʾ", u8"ע����޸�ʧ��");
    }
    return;
}

void MainUi::BnServerClose()
{
    bool ret = ServerClose();
    if (ret) {
        QMessageBox::information(this, u8"��ʾ", u8"����رճɹ�");
    }
    else
    {
        QMessageBox::information(this, u8"��ʾ", u8"����ر�ʧ��");
    }
    return;
}

void MainUi::BnServerOpen()
{
    bool ret = ServerOpen();
    if (ret) {
        QMessageBox::information(this, u8"��ʾ", u8"����򿪳ɹ�");
    }
    else
    {
        QMessageBox::information(this, u8"��ʾ", u8"�����ʧ��");
    }
    return;
}

void MainUi::UpdateServerStatus()
{
    bool ret = SelectServerState();
    if (ret == 0) {
        //����ر�
        ui->label_ServerStatus->setText(u8"����״̬:�Ѿ��ر�");
        QPixmap pixmap(":/MainUi/pic/guzhang.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
    else if (ret==1) {
        //�����
        ui->label_ServerStatus->setText(u8"����״̬:��������");
        QPixmap pixmap(":/MainUi/pic/cry.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
    else {
        //����״̬δ֪
        ui->label_ServerStatus->setText(u8"����״̬:δ֪");
        QPixmap pixmap(":/MainUi/pic/dalian.png");
        pixmap = pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_ServerInfo->setPixmap(pixmap);
    }
}

void MainUi::Init()
{
    UpdateServerStatus();
}
