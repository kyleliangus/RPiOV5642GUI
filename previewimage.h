#ifndef PREVIEWIMAGE_H
#define PREVIEWIMAGE_H

#include <QDialog>

#include <string.h>
#include <dirent.h>

namespace Ui {
class PreviewImage;
}

class PreviewImage : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewImage(QWidget *parent = 0);
    ~PreviewImage();

private:
    Ui::PreviewImage *ui;
    DIR *dir;
    struct dirent *dirp;
};

#endif // PREVIEWIMAGE_H
