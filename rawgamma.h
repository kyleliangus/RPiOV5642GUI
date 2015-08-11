#ifndef RAWGAMMA_H
#define RAWGAMMA_H

#include <QDialog>

namespace Ui {
class rawgamma;
}

class rawgamma : public QDialog
{
    Q_OBJECT

public:
    explicit rawgamma(QWidget *parent = 0);
    ~rawgamma();

private:
    Ui::rawgamma *ui;
};

#endif // RAWGAMMA_H
