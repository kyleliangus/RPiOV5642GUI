#ifndef AWB_H
#define AWB_H

#include <QDialog>

namespace Ui {
class awb;
}

class awb : public QDialog
{
    Q_OBJECT

public:
    explicit awb(QWidget *parent = 0);
    ~awb();

private:
    Ui::awb *ui;
};

#endif // AWB_H
