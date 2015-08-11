#ifndef PIXELCANCELLATION_H
#define PIXELCANCELLATION_H

#include <QDialog>

namespace Ui {
class pixelCancellation;
}

class pixelCancellation : public QDialog
{
    Q_OBJECT

public:
    explicit pixelCancellation(QWidget *parent = 0);
    ~pixelCancellation();

private:
    Ui::pixelCancellation *ui;
};

#endif // PIXELCANCELLATION_H
