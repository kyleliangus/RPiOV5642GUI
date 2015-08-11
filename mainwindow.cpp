#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileName = "";

    /* minimal setup */

    ui->digitalGainBox->hide();
    ui->lensCorrectionRadio->hide();
    ui->deNoiseRadio->hide();
    ui->evenOddRemovingRadio->hide();
    ui->colorInterpolationRadio->hide();
    ui->blackLevelCalibrationRadio->hide();
    ui->vapControlRegisterRadio->hide();

    ui->autoWhiteBalanceButton->setEnabled(false);
    ui->detectPixelCancellationButton->setEnabled(false);
    ui->rawGammaButton->setEnabled(false);
    ui->yuvGammaButton->setEnabled(false);

    /* minimal setup */

    // setup ui
    ui->tabWidget->setCurrentIndex(0);
    showBoxes(0);

    // connect everything
    connect(ui->digitalGainOffRadio, SIGNAL(toggled(bool)),
            this, SLOT( digitalGainOffRadioToggle(bool) ) );
    connect(ui->manualModeAGCRadio, SIGNAL(toggled(bool)),
            this, SLOT(automaticControlAGCRadioToggle(bool)) );
    connect(ui->manualModeAECRadio, SIGNAL(toggled(bool)),
            this, SLOT(automaticControlAECRadioToggle(bool)) );

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(showBoxes(int)) );

    connect(ui->saveButton, SIGNAL(clicked(bool)),
            this, SLOT( saveParameters() ) );
    connect(ui->loadButton, SIGNAL(clicked(bool)),
            this, SLOT( obtainSavedParameters() ) );

    connect(ui->takePictureButton, SIGNAL(clicked(bool)),
            this, SLOT( takePicture() ) );
    connect(ui->previewPictureButton, SIGNAL(clicked(bool)),
            this, SLOT( previewPicture() ) );

    // set opened menus to false
    ispOpened = false;

}
// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

/* new Menus */
void MainWindow::on_ispButton_clicked()
{
    ispMenu = new isp(fileName);
    ispMenu->setAttribute( Qt::WA_DeleteOnClose );
    ispMenu->show();
    ispOpened = true;

    if( ispMenu->exec() )
    {
        appendOptions( ispMenu->getISPParameters() );
    }

}

void MainWindow::on_detectPixelCancellationButton_clicked()
{
    pixelCancellationMenu = new pixelCancellation;
    pixelCancellationMenu->setAttribute( Qt::WA_DeleteOnClose );
    pixelCancellationMenu->show();
}

void MainWindow::on_autoWhiteBalanceButton_clicked()
{
    awbMenu = new awb();
    awbMenu->setAttribute( Qt::WA_DeleteOnClose );
    awbMenu->show();
}

void MainWindow::on_rawGammaButton_clicked()
{
    rawgammaMenu = new rawgamma();
    rawgammaMenu->setAttribute( Qt::WA_DeleteOnClose );
    rawgammaMenu->show();
}

void MainWindow::on_yuvGammaButton_clicked()
{
    yuvgammaMenu = new yuvgamma();
    yuvgammaMenu->setAttribute( Qt::WA_DeleteOnClose );
    yuvgammaMenu->show();
}

/* Ui implementation */

void MainWindow::digitalGainOffRadioToggle(bool on)
{
    if( on )
    {
        ui->digitalGainLabel->setEnabled(false);
        ui->digitalGainSpin->setEnabled(false);
    }
    else
    {
        ui->digitalGainLabel->setEnabled(true);
        ui->digitalGainSpin->setEnabled(true);
    }
}

void MainWindow::automaticControlAECRadioToggle(bool on)
{
    if( on )
    {
        ui->automaticControlAECSlider->setEnabled(true);
        ui->automaticControlAECSpin->setEnabled(true);
        ui->automaticControlAECLabel->setEnabled(true);
        ui->automaticControlVTSLabel->setEnabled(true);
        ui->automaticControlVTSSlider->setEnabled(true);
        ui->automaticControlVTSSpin->setEnabled(true);
    }
    else
    {
        ui->automaticControlAECSlider->setEnabled(false);
        ui->automaticControlAECSpin->setEnabled(false);
        ui->automaticControlAECLabel->setEnabled(false);
        ui->automaticControlVTSLabel->setEnabled(false);
        ui->automaticControlVTSSlider->setEnabled(false);
        ui->automaticControlVTSSpin->setEnabled(false);
    }
}

void MainWindow::automaticControlAGCRadioToggle(bool on)
{
    if( on )
    {
        ui->automaticControlAGCSlider->setEnabled(true);
        ui->automaticControlAGCSpin->setEnabled(true);
        ui->automaticControlAECLabel->setEnabled(true);
    }
    else
    {
        ui->automaticControlAGCSlider->setEnabled(false);
        ui->automaticControlAGCSpin->setEnabled(false);
        ui->automaticControlAGCLabel->setEnabled(false);
    }
}

void MainWindow::showBoxes( int n )
{
    if( n == 1 )
    {
        ui->automaticControlBox->show();
        ui->manualModeAECAGCControlBox->show();
        ui->binningBox->hide();
        ui->generalBox->hide();
    }
    else
    {
        ui->automaticControlBox->hide();
        ui->manualModeAECAGCControlBox->hide();
        ui->binningBox->show();
        ui->generalBox->show();
    }
}

// save everything
void MainWindow::saveParameters()
{
    // obtain radio properties
    obtainOptionsSelectedMainWindow();

    // check if other menus have been included yet
    if( ispOpened == false )
    {
        ispMenu = new isp( fileName );
        appendOptions( ispMenu->getISPParameters() );
        delete ispMenu;
    }

    if( parameters.size() == 0 )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Unnecessary save. All options are default!");
        messageBox.setFixedSize(500,200);
    }
    else // write to file
    {
        // check # of configuration
        std::stringstream pFileName;
        int degree = 1;
        pFileName << "configuration" << degree << ".xml";

        while( fileExists( pFileName.str() ) )
        {
            degree++;
            pFileName.str("");
            pFileName << "configuration" << degree << ".xml";
        }

        fileName = pFileName.str();

        // save to file
        std::ofstream myfile;
        myfile.open( fileName.c_str() );
        for( unsigned int i = 0; i < parameters.size(); i++ )
        {
            myfile << parameters.at(i).toString() << "\n";
        }
        myfile.close();

        // save options
        saveMainWindowUIOptions( fileName.substr(0,fileName.length()-3) + "ini" );


        // inform user
        QMessageBox messageBox;
        std::string message = "Configurations have been saved to " + fileName;
        messageBox.information( 0, "Saved", message.c_str() );
    }
}

void MainWindow::obtainOptionsSelectedMainWindow()
{
    // check binning
    int v = 0;
    if( ui->binningHorizontalRadio->isChecked() )
    {
        v+=binToDecimal(7);
    }
    if( ui->mirrorRadio->isChecked() ) // mirror Additional 1
    {
        v+=binToDecimal(5);
    }
    v += binToDecimal(4); // default
    createParameter(hBinR, v, hBinDV, parameters);

    if( ui->binningHorizontalRadio->isChecked() )
    {
        v+=binToDecimal(6);
    }
    v += vBinDV; // default
    createParameter(vBinR, v, vBinDV, parameters);

    // mirror and flip


    if( ui->mirrorRadio->isChecked() )
    {
        createParameter(mirrorAdditionalR2, v+=binToDecimal(5)+binToDecimal(4), 0xB4, parameters); // mirror Addiontal 2
        v+=binToDecimal(6);
    }
    if( ui->flipRadio->isChecked() )
    {
        v+=binToDecimal(5);
    }
    // compression
    if( ui->compressionRadio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    createParameter(mirrorVFlipR, v, mirrorVFlipDV, parameters);

    // nightmode
    if( ui->nightModeRadio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    v += binToDecimal(7);     // default value
    createParameter(nightModeR, v, nightModeDV, parameters);


    //createParameter(compressionR, v, compressionDV, parameters);

    // AEC/AGC
    if( ui->manualModeAECRadio->isChecked() )
    {
        v+=binToDecimal(2);
        v+=binToDecimal(0);
    }
    if( ui->manualModeAGCRadio->isChecked() )
    {
        v+=binToDecimal(1);
    }
    createParameter(aecAGCVTSControlR, v, manualAECAGCDV, parameters);

    if( ui->manualModeAECRadio->isChecked() ) // check sliders/spin AEC : first with AEC
    {
        int vts = round( ( ui->automaticControlVTSSpin->text().toInt() ) * 25.0 * 1000 / 1944 );
        int aec = round( ( ui->automaticControlAECSpin->text().toInt() ) * 25.0 * 1000 / 1944 );

        std::string bVTS = decToBinaryString( vts );
        std::string bAEC = decToBinaryString( aec );
        // split binary string
        int temp = 0;

        // first 4 aec
        for( int i = 0; i < 4; i++ )
        {
            if( bAEC.at(i) == '1' )
            {
                v += binToDecimal(4-i);
            }
        }
        createParameter( aeclR1, v, manualAECAGCDV, parameters  );

        // vts with aec
        for( int i = 4; i < 12; i++ )
        {
            if( bVTS.at(i-4) == '1' )
            {
                temp += binToDecimal(11-i);
            }
            if( bAEC.at(i) == '1' )
            {
                v += binToDecimal(11-i);
            }
        }
        createParameter( aeclR2, v, manualAECAGCDV, parameters );
        createParameter( vtsR1, temp, manualVTSR1DV, parameters );

        for( int i = 12; i < 16; i++ )
        {
            if( bVTS.at(i-4) == '1' )
            {
                temp += binToDecimal(19-i);
            }
            if( bAEC.at(i) == '1' )
            {
                v += binToDecimal(19-i);
            }
        }
        createParameter( aeclR3, v, manualAECAGCDV, parameters );

        // finish vts
        for( int i = 12; i < 16; i++ )
        {
            if( bVTS.at(i) == '1' )
            {
                temp += binToDecimal(15-i);
            }
        }
        createParameter( vtsR2, temp, manualVTSR2DV, parameters );

    }

    if( ui->manualModeAGCRadio->isChecked() ) // AGC
    {
        std::string bAGC = decToBinaryString( ui->automaticControlAGCSpin->text().toInt() );
        for( unsigned int i = 0; i < bAGC.length(); i++ )
        {
            if( bAGC.at(i) == '1' )
            {
                v += binToDecimal(16-i);
            }
        }
        createParameter( agcAECadjR2, v, manualAECAGCDV, parameters );
    }

}

std::string MainWindow::decToBinaryString( int n )
{
    std::string s = "";
    while( s.length() < 16 )
    {
        if( n%2 == 0 )
        {
            s = "0" + s;
        }
        else
        {
            s = "1" + s;
        }
        n /= 2;
    }
    return s;
}

// save MainWindoiw ui options
void MainWindow::saveMainWindowUIOptions( std::string saveFileName )
{
    QSettings settings( saveFileName.c_str(), QSettings::IniFormat );
    settings.setValue( "binningHorizontalRadio", ui->binningHorizontalRadio->isChecked() );
    settings.setValue( "binningVerticalRadio", ui->binningVerticalRadio->isChecked() );
    settings.setValue( "mirrorRadio", ui->mirrorRadio->isChecked() );
    settings.setValue( "flip Radio", ui->flipRadio->isChecked() );
    settings.setValue( "nightModeRadio", ui->nightModeRadio->isChecked() );
    settings.setValue( "compressionRadio", ui->compressionRadio->isChecked() );
    settings.setValue( "manualModeAECRadio", ui->manualModeAECRadio->isChecked() );
    settings.setValue( "manualModeAGCRadio", ui->manualModeAGCRadio->isChecked() );
    settings.setValue( "automaticControlAECSpin", ui->automaticControlAECSpin->text().toInt() );
    settings.setValue( "automaticControlAGCSpin", ui->automaticControlAGCSpin->text().toInt() );
}

void MainWindow::loadMainWindowUIOptions( std::string loadFileName )
{
    QSettings settings( loadFileName.c_str(), QSettings::IniFormat );
    ui->binningHorizontalRadio->setChecked( settings.value("binningHorizontalRadio").toBool() );
    ui->binningVerticalRadio->setChecked( settings.value("binningVerticalRadio").toBool() );
    ui->mirrorRadio->setChecked( settings.value("mirrorRadio").toBool() );
    ui->flipRadio->setChecked( settings.value("flipRadio").toBool() );
    ui->nightModeRadio->setChecked( settings.value("nightModeRadio").toBool() );
    ui->compressionRadio->setChecked( settings.value("compressionRadio").toBool() );
    ui->manualModeAECRadio->setChecked( settings.value("manualModeAECRadio").toBool() );
    ui->manualModeAGCRadio->setChecked( settings.value("manualModeAGCRadio").toBool() );
    ui->automaticControlAECSpin->setValue( settings.value("automaticControlAECSpin").toInt() );
    ui->automaticControlAGCSpin->setValue( settings.value("automaticControlAGCSpin").toInt() );
}

bool MainWindow::fileExists(std::string possibleFileName)
{
    std::ifstream infile(possibleFileName.c_str());
    return infile.good();
}


// SPECIAL SLOT: Accept data from submenu
void MainWindow::appendOptions( std::vector<Parameter> b )
{
    parameters.insert( parameters.end(), b.begin(), b.end() );
}
//

// Load File
std::string MainWindow::obtainSavedFileName()
{
    QString lFileName = QFileDialog::getOpenFileName(this, tr("Open Saved Configuration"),
                                                    "/home/", tr("Saved Configuration (*xml)"));
    return lFileName.toStdString();
}

void MainWindow::obtainSavedParameters()
{
    // parameters.clear();
    // continue
    std::string possibleFileName = obtainSavedFileName();

    std::ifstream myfile(possibleFileName.c_str());
    if (myfile.is_open())
    {
        // assign variable fileName
        fileName = possibleFileName;

        std::string line;
        std::string registry;
        std::string value;

        while ( getline(myfile,line) )
        {
            std::size_t commaPosition = line.find(',', 0);
            registry = line.substr(0, commaPosition);
            value = line.substr( commaPosition + 2, line.size() );
            int v = atoi(value.c_str());
            createParameter(registry, v, -1, parameters);
        }
        myfile.close();

        /* load GUI to match */
        // check if file exists
        std::string settingsFile = fileName.substr(0,fileName.length()-4) + "MainWindow" + ".ini";

        myfile.open( settingsFile.c_str() );
        if( myfile.is_open() )
        {
            loadMainWindowUIOptions( settingsFile );
        }
        else
        {
            QMessageBox missingMessageBox;
            std::string missingFile = "MainWindow Ui option file is missing.";
            missingMessageBox.information( 0, "Missing", missingFile.c_str() );
        }


        QMessageBox messageBox;
        std::string message = "Parameters have been loaded from " + fileName;
        messageBox.information( 0, "Loaded", message.c_str() );
    }
    else
    {
        QMessageBox messageBox;
        std::string message = "Parameter File not found or invalid save : " + fileName;
        messageBox.information( 0, "Failed Load", message.c_str() );
    }
}

// Create h file for camera
void MainWindow::saveHFile()
{
    std::stringstream parameterFileName;
    parameterFileName << "ov5642_parameters.h";

    // save to file
    std::ofstream myfile;
    myfile.open( parameterFileName.str().c_str() );
    myfile << "#ifndef OV5642_REGS_H\n#define OV5642_REGS_H\n#include \"PiCAM.h\"\n" <<
              "#define OV5642_CHIPID_HIGH 0x300a\n" << "#define OV5642_CHIPID_LOW 0x300b\n";
    myfile << "const struct sensor_reg ov5642_user_parameters[] PROGMEM=\n{\n";

    // ready parameter vector
    obtainOptionsSelectedMainWindow();

    for( unsigned int i = 0; i < parameters.size(); i++ )
    {
        myfile << "{" << parameters.at(i).toString() << "},\n";
    }
    myfile << "\n};\n#endif";
    myfile.close();

}

// Take Picture button pressed
void MainWindow::takePicture()
{
    saveHFile();

    std::system( "ov5642.exe" );
    // sent to camera
    /* implementation */
}

// Picture Preview button pressed
void MainWindow::previewPicture()
{
    saveHFile();
    // send to camera
    /* implementation */

    previewImageMenu = new PreviewImage();
    previewImageMenu->setAttribute( Qt::WA_DeleteOnClose );
    previewImageMenu->show();

}
