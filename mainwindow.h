#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QSettings>

#include "awb.h"
#include "isp.h"
#include "pixelcancellation.h"
#include "yuvgamma.h"
#include "rawgamma.h"
#include "parameter.h"
#include "model.h"
#include "previewimage.h"

#include "sys/stat.h"
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void appendOptions( std::vector<Parameter> );
    std::vector<Parameter> getUserParameter()
    {
        return parameters;
    }

private slots:
    //New Window slot
    void on_ispButton_clicked();
    void on_detectPixelCancellationButton_clicked();
    void on_autoWhiteBalanceButton_clicked();
    void on_rawGammaButton_clicked();
    void on_yuvGammaButton_clicked();

    //Ui Slots
    void digitalGainOffRadioToggle(bool);
    void automaticControlAECRadioToggle(bool);
    void automaticControlAGCRadioToggle(bool);

    void showBoxes(int);
    void saveParameters();
    void obtainOptionsSelectedMainWindow();
    bool fileExists( std::string );
    std::string obtainSavedFileName();
    void obtainSavedParameters();

    void saveHFile();
    void saveNoExtFile();

    void saveMainWindowUIOptions(std::string);
    void loadMainWindowUIOptions(std::string);

    std::string decToBinaryString( int );

    void takePicture();
    void previewPicture();

private:
    Ui::MainWindow *ui;
    awb *awbMenu;
    isp *ispMenu;
    pixelCancellation *pixelCancellationMenu;
    rawgamma *rawgammaMenu;
    yuvgamma *yuvgammaMenu;
    PreviewImage *previewImageMenu;
    // store values
    //int yuvgammaValues [30];
    //int rawgammaValues [30];
    std::vector<Parameter> parameters;

    std::string fileName;

    bool ispOpened;

};

#endif // MAINWINDOW_H
