#ifndef YUVGAMMA_H
#define YUVGAMMA_H

#include <QDialog>

namespace Ui {
class yuvgamma;
}

class yuvgamma : public QDialog
{
    Q_OBJECT

public:
    explicit yuvgamma(QWidget *parent = 0);
    ~yuvgamma();

private:
    Ui::yuvgamma *ui;
};

#endif // YUVGAMMA_H
