#include "previewimage.h"
#include "ui_previewimage.h"
//#include "operations.hpp"

PreviewImage::PreviewImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewImage)
{
    ui->setupUi(this);

    // find newest Image
    //std::string imageFileDir = "/home/pi/preview/";
    std::string imageFileDir = "C:\\Users\\Kyle\\Workspace\\Ozcan Research\\Raspberry Pi Camera GUI\\preview\\";
    std::string imageFileName;

    dir = opendir( imageFileDir.c_str() );



    if( dir == NULL )
    {
        ui->imageLabel->setText( "No image found!" );

    }
    else
    {
        dirp = readdir(dir);
        //imageFileName = std::string(dirp->d_name);
        imageFileName = "20150722124605";
        //while( imageFileName == "." || imageFileName == "..")
        {
        //    dirp = readdir(dir);
        }
        qDebug( (imageFileDir + "ov5642_preview.jpg").c_str() );
        //std::cout << ;
        QPixmap pix( (imageFileDir + imageFileName + ".jpg").c_str() );
        ui->imageLabel->setPixmap( pix );
        ui->imageLabel->setScaledContents(true);
        ui->imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        //ui->imageLabel->adjustSize();
    }


    //std::time_t last_write_time(imageFileName);

}

PreviewImage::~PreviewImage()
{
    delete ui;
    delete dir;
    delete dirp;
}
