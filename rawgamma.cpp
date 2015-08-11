#include "rawgamma.h"
#include "ui_rawgamma.h"

rawgamma::rawgamma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rawgamma)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 15pt;");
}

rawgamma::~rawgamma()
{
    delete ui;
}
