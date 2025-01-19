#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>


#include "ui_MainUi.h"
#include "tool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainUiClass; };
QT_END_NAMESPACE

class MainUi : public QMainWindow
{
    Q_OBJECT

public:
    MainUi(QWidget *parent = nullptr);
    ~MainUi();

    void RegClose();
    void BnServerClose();
    void BnServerOpen();
    void UpdateServerStatus();

private:
    Ui::MainUiClass *ui;
    void Init();
};
