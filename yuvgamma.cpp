#include "yuvgamma.h"
#include "ui_yuvgamma.h"

yuvgamma::yuvgamma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::yuvgamma)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 15pt;");

}

yuvgamma::~yuvgamma()
{
    delete ui;
}
