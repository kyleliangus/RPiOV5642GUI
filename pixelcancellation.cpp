#include "pixelcancellation.h"
#include "ui_pixelcancellation.h"

pixelCancellation::pixelCancellation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pixelCancellation)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 15pt;");
}

pixelCancellation::~pixelCancellation()
{
    delete ui;
}
