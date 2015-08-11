#include "awb.h"
#include "ui_awb.h"

awb::awb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::awb)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 15pt;");
}

awb::~awb()
{
    delete ui;
}
