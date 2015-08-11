#include "isp.h"
#include "ui_isp.h"

isp::isp(std::string offeredFileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::isp)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 15pt;");
    savedFileName = offeredFileName;

    // prepare ui
    ispGroupBoxes[0] = ui->control00Box;
    ispGroupBoxes[1] = ui->control01Box;
    ispGroupBoxes[2] = ui->control02Box;
    ispGroupBoxes[3] = ui->control03Box;
    ispGroupBoxes[4] = ui->control05Box;
    ispGroupBoxes[5] = ui->horizontalSubsampleModeBox;
    ispGroupBoxes[6] = ui->rgbDitherControlBox;
    ispGroupBoxes[7] = ui->formatControlBox;
    showGroupBox(0);
    formatControlCheck( false );

    ui->tabWidget->setCurrentIndex(0);
    ui->horizontalSubsampleDefaultWarningLabel->hide();


    // connect
    connect( ui->formatControlCheck, SIGNAL(toggled(bool)),
             this, SLOT(formatControlCheck(bool)) );
    connect( ui->tabWidget, SIGNAL(currentChanged(int)),
             this, SLOT(showGroupBox(int)) );


}

isp::~isp()
{
    delete ui;
}

// SLOTS
void isp::formatControlCheck(bool on)
{
    if( on )
    {
        ui->formatControlFrame->setEnabled(true);
    }
    else
    {
        ui->formatControlFrame->setEnabled(false);
    }
}

void isp::showGroupBox(int n)
{
    for( int i = 0; i<8; i++ )
    {
        ispGroupBoxes[i]->hide();
    }
    ispGroupBoxes[n]->show();
    // include label bool
    if( n == 5 )
    {
        if( !ui->horizontalSubsamplingRadio->isChecked() )
        {
            ui->horizontalSubsampleOffWarningLabel->show();
            ui->horizontalSubsampleModeBox->setEnabled(false);
        }
    }
    else
    {
        ui->horizontalSubsampleOffWarningLabel->hide();
        ui->horizontalSubsampleModeBox->setEnabled(true);
    }
}

void isp::obtainOptionsSelectedISP()
{
    // ispParameters.clear();

    int v = 0;
    // ISP Control 00
    if( ui->lencCorrectionRadio->isChecked() )
    {
        v+=binToDecimal(7);
    }
    if( ui->yuvGammaRadio->isChecked() )
    {
        v+=binToDecimal(6);
    }
    if( ui->rawGammaRadio->isChecked() )
    {
        v+=binToDecimal(5);
    }
    if( ui->evenOddRadio->isChecked() )
    {
        v+=binToDecimal(4);
    }
    if( ui->denoiseRadio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    if( ui->blackPixelCancellationRadio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    if( ui->whitePixelCancellationRadio->isChecked() )
    {
        v+=binToDecimal(1);
    }
    if( ui->colorInterpolationRadio->isChecked() )
    {
        v+=binToDecimal(0);
    }
    createParameter(c01R, v, c01DV, ispParameters);

    // ISP Control 01
    if( ui->specialDigitalEffects->isChecked() )
    {
        v+=binToDecimal(7);
    }
    if( ui->uvAdjustRadio->isChecked() )
    {
        v+=binToDecimal(6);
    }
    if( ui->verticalScalingRadio->isChecked() )
    {
        v+=binToDecimal(5);
    }
    if( ui->horizontalScalingRadio->isChecked() )
    {
        v+=binToDecimal(4);
    }
    if( ui->lineStretchRadio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    if( ui->uvAverageRadio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    if( ui->colorMatrixRadio->isChecked() )
    {
        v+=binToDecimal(1);
    }
    if( ui->autoWhiteBalanceRadio->isChecked() )
    {
        v+=binToDecimal(0);
    }
    createParameter(c01R, v, c01DV, ispParameters);

    // ISP Control 02
    if( ui->thumbnailScalingRadio->isChecked() )
    {
        v+=binToDecimal(7);
    }
    if( ui->ditheringRadio->isChecked() )
    {
        v+=binToDecimal(4);
    }
    if( ui->yuvToRGBRadio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    if( ui->horizontalSubsamplingRadio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    createParameter(c02R, v, c02DV, ispParameters);

    // ISP Control 03
    if( ui->yuvToYCbCrRadio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    if( ui->yuv422Radio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    if( ui->drawWindowAFCRadio->isChecked() )
    {
        v+=binToDecimal(1);
    }
    createParameter(c03R, v, c03DV, ispParameters);

    // ISP Control 05
    if( ui->rawGamma1Radio->isChecked() )
    {
        v+=binToDecimal(7);
    }
    if( ui->rawGamma2Radio->isChecked() )
    {
        v+=binToDecimal(6);
    }
    if( ui->advancedAWBRadio->isChecked() )
    {
        v+=binToDecimal(4);
    }
    if( ui->lensCorrection1Radio->isChecked() )
    {
        v+=binToDecimal(3);
    }
    if( ui->lensCorrection2Radio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    createParameter(c05R, v, c05DV, ispParameters);

    // Horizon Subsample Mode
    if( ui->horizontalSubsamplingRadio->isChecked() )
    {
        if( ui->hsmBChannelCombo->currentIndex() == 1 )
        {
            v+=binToDecimal(7);
        }
        if( ui->hsmGbChannelCombo->currentIndex() == 1 )
        {
            v+=binToDecimal(5);
        }
        if( ui->hsmGrChannelCombo->currentIndex() == 1 )
        {
            v+=binToDecimal(3);
        }
        if( ui->hsmRChannelCombo->currentIndex() == 1 )
        {
            v+=binToDecimal(1);
        }
    }
    createParameter(hsmR, v, hsmDV, ispParameters);

    // RGB Dither
    if( ui->rChannelCombo->currentIndex() == 1 )
    {
        v+=binToDecimal(5);
    }
    else
    {
        v+=binToDecimal(4);
    }
    if( ui->gChannelCombo->currentIndex() == 1 )
    {
        v+=binToDecimal(3);
    }
    else
    {
        v+=binToDecimal(2);
    }
    if( ui->bChannelCombo->currentIndex() == 1 )
    {
        v+=binToDecimal(1);
    }
    else
    {
        v+=binToDecimal(0);
    }
    if( ui->rgbDitherControlSystemRadio->isChecked() )
    {
        v+=binToDecimal(6);
    }
    createParameter(rgbdcR, v, rgbdcDV, ispParameters);

    // Format Control
    if( ui->formatControlSwapYAndUVRadio->isChecked() )
    {
        v+=binToDecimal(5);
    }
    if( ui->formatControlISPRGBRadio->isChecked() )
    {
        v+=binToDecimal(0);
    }
    else if( ui->formatControlISPYUVRadio->isChecked() )
    {
        v+=binToDecimal(1);
    }
    else if( ui->formatControlISPRAWRadio->isChecked() )
    {
        v+=binToDecimal(1);
        v+=binToDecimal(0);
    }
    else if( ui->formatControlInternalCIFRAWRadio->isChecked() )
    {
        v+=binToDecimal(2);
    }
    else if( ui->formatControlExternalCIFRAWRadio ->isChecked() )
    {
        v+=binToDecimal(2);
        v+=binToDecimal(0);
    }
    else if( ui->formatControlExternalCIFYUVRadio->isChecked() )
    {
        v+=binToDecimal(2);
        v+=binToDecimal(1);
    }
    createParameter(fcR, v, fcDV, ispParameters);

}

void isp::saveISPUIOptions( std::string fileName )
{
    QSettings save( fileName.c_str(), QSettings::IniFormat );
    save.setValue( "lencCorrection", ui->lencCorrectionRadio->isChecked() );
    save.setValue( "yuvGamma", ui->yuvGammaRadio->isChecked() );
    save.setValue( "rawGamma", ui->rawGammaRadio->isChecked() );
    save.setValue( "evenOddRemoving", ui->evenOddRadio->isChecked() );
    save.setValue( "denoise", ui->denoiseRadio->isChecked() );
    save.setValue( "blackPixelCancellation", ui->blackPixelCancellationRadio->isChecked() );
    save.setValue( "whitePixelCancellation", ui->whitePixelCancellationRadio->isChecked() );
    save.setValue( "colorInterpolation", ui->colorInterpolationRadio->isChecked() );
    save.setValue( "specialDigitalEffects", ui->specialDigitalEffects->isChecked() );
    save.setValue( "uvAdjust", ui->uvAdjustRadio->isChecked() );
    save.setValue( "verticalScaling", ui->verticalScalingRadio->isChecked() );
    save.setValue( "horizontalScaling", ui->horizontalScalingRadio->isChecked() );
    save.setValue( "lineStretch", ui->lineStretchRadio->isChecked() );
    save.setValue( "uvAverage", ui->uvAverageRadio->isChecked() );
    save.setValue( "colorMatrix", ui->colorMatrixRadio->isChecked() );
    save.setValue( "autoWhiteBalance", ui->autoWhiteBalanceRadio->isChecked() );
    save.setValue( "thumbnailScaling", ui->thumbnailScalingRadio->isChecked() );
    save.setValue( "dithering", ui->ditheringRadio->isChecked() );
    save.setValue( "yuvToRGB", ui->yuvToRGBRadio->isChecked() );
    save.setValue( "horizontalSubsampling", ui->horizontalSubsamplingRadio->isChecked() );
    save.setValue( "yuvToYcbCr", ui->yuvToYCbCrRadio->isChecked() );
    save.setValue( "yuv422", ui->yuv422Radio->isChecked() );
    save.setValue( "drawWindow", ui->drawWindowAFCRadio->isChecked() );
    save.setValue( "rawGamma1", ui->rawGamma1Radio->isChecked() );
    save.setValue( "rawGamma2", ui->rawGamma2Radio->isChecked() );
    save.setValue( "advancedAWB", ui->advancedAWBRadio->isChecked() );
    save.setValue( "lensCorrection1", ui->lensCorrection1Radio->isChecked() );
    save.setValue( "lensCorrection2", ui->lensCorrection2Radio->isChecked() );
    save.setValue( "horizontalSubsampleBChannel", ui->hsmBChannelCombo->currentIndex() );
    save.setValue( "horizontalSubsampleGbChannel", ui->hsmGbChannelCombo->currentIndex() );
    save.setValue( "horizontalSubsampleGrChannel", ui->hsmGrChannelCombo->currentIndex() );
    save.setValue( "horizontalSubsampleRChannel", ui->hsmRChannelCombo->currentIndex() );
    save.setValue( "rgbDitherControlRegister", ui->rgbDitherControlRegisterRadio->isChecked() );
    save.setValue( "rgbDitherControlSystem", ui->rgbDitherControlSystemRadio->isChecked() );
    save.setValue( "rgbDitherControlRChannel", ui->rChannelCombo->currentIndex() );
    save.setValue( "rgbDitherChannelGChannel", ui->bChannelCombo->currentIndex() );
    save.setValue( "rgbDitherControlBChannel", ui->bChannelCombo->currentIndex() );
    save.setValue( "formatControl", ui->formatControlCheck->isChecked() );
    save.setValue( "swapYandUV", ui->formatControlSwapYAndUVRadio->isChecked() );
    save.setValue( "ispYUV2", ui->formatControlISPYUVRadio_2->isChecked() );
    save.setValue( "ispRGB", ui->formatControlISPRGBRadio->isChecked() );
    save.setValue( "ispYUV", ui->formatControlISPYUVRadio->isChecked() );
    save.setValue( "ispRAW", ui->formatControlISPRAWRadio->isChecked() );
    save.setValue( "interntalCIFRAW", ui->formatControlInternalCIFRAWRadio->isChecked() );
    save.setValue( "externalCIFRAW", ui->formatControlExternalCIFRAWRadio->isChecked() );
    save.setValue( "externalCIFYUV422bypass", ui->formatControlExternalCIFYUVRadio->isChecked() );


}

void isp::loadISPUIOptions( std::string fileName )
{
    QSettings settings( fileName.c_str(), QSettings::IniFormat );
}

// SPECIAL SLOT: Send data to MainWindow
std::vector<Parameter> isp::getISPParameters()
{
    saveISPMenuState();
    obtainOptionsSelectedISP();
    return ispParameters;
}
//

void isp::saveISPMenuState()
{
    if( savedFileName.length() == 0 )
    {
        saveISPUIOptions( "temporary" );

    }
    else
    {
        saveISPUIOptions( savedFileName.c_str() );
    }

}

void isp::loadISPMenuState()
{
    QSettings load( savedFileName.c_str(), QSettings::IniFormat );
    ui->lencCorrectionRadio->setChecked( load.value( "lencCorrection" ).toBool() );
    ui->yuvGammaRadio->setChecked( load.value( "yuvGamma" ).toBool() );
    ui->rawGammaRadio->setChecked( load.value( "rawGamma" ).toBool() );
    ui->evenOddRadio->setChecked( load.value( "evenOddRemoving" ).toBool() );
    ui->denoiseRadio->setChecked( load.value( "denoise" ).toBool() );
    ui->blackPixelCancellationRadio->setChecked( load.value( "blackPixelCancellation" ).toBool() );
    ui->whitePixelCancellationRadio->setChecked( load.value( "whitePixelCancellation" ).toBool() );
    ui->colorInterpolationRadio->setChecked(load.value( "colorInterpolation" ).toBool() );
    ui->specialDigitalEffects->setChecked( load.value( "specialDigitalEffects" ).toBool() );
    ui->uvAdjustRadio->setChecked( load.value( "uvAdjust" ).toBool() );
    ui->verticalScalingRadio->setChecked( load.value( "verticalScaling" ).toBool() );
    ui->horizontalScalingRadio->setChecked( load.value( "horizontalScaling" ).toBool() );
    ui->lineStretchRadio->setChecked( load.value( "lineStretch" ).toBool() );
    ui->uvAverageRadio->setChecked( load.value( "uvAverage" ).toBool() );
    ui->colorMatrixRadio->setChecked( load.value( "colorMatrix" ).toBool() );
    ui->autoWhiteBalanceRadio->setChecked( load.value( "autoWhiteBalance" ).toBool() );
    ui->thumbnailScalingRadio->setChecked( load.value( "thumbnailScaling" ).toBool() );
    ui->ditheringRadio->setChecked( load.value( "dithering" ).toBool() );
    ui->yuvToRGBRadio->setChecked( load.value( "yuvToRGB" ).toBool() );
    ui->horizontalSubsamplingRadio->setChecked( load.value( "horizontalSubsampling" ).toBool() );
    ui->yuvToYCbCrRadio->setChecked( load.value( "yuvToYcbCr" ).toBool() );
    ui->yuv422Radio->setChecked( load.value( "yuv422" ).toBool() );
    ui->drawWindowAFCRadio->setChecked( load.value( "drawWindow" ).toBool() );
    ui->rawGamma1Radio->setChecked( load.value( "rawGamma1" ).toBool() );
    ui->rawGamma2Radio->setChecked( load.value( "rawGamma2" ).toBool() );
    ui->advancedAWBRadio->setChecked( load.value( "advancedAWB" ).toBool() );
    ui->lensCorrection1Radio->setChecked( load.value( "lensCorrection1" ).toBool() );
    ui->lensCorrection2Radio->setChecked( load.value( "lensCorrection2" ).toBool() );
    ui->hsmBChannelCombo->setCurrentIndex( load.value( "horizontalSubsampleBChannel" ).toInt() );
    ui->hsmGbChannelCombo->setCurrentIndex( load.value( "horizontalSubsampleGbChannel" ).toInt() );
    ui->hsmGrChannelCombo->setCurrentIndex( load.value( "horizontalSubsampleGrChannel" ).toInt() );
    ui->hsmRChannelCombo->setCurrentIndex( load.value( "horizontalSubsampleRChannel" ).toInt() );
    ui->rgbDitherControlRegisterRadio->setChecked( load.value( "rgbDitherControlRegister" ).toBool() );
    ui->rgbDitherControlSystemRadio->setChecked( load.value( "rgbDitherControlSystem" ).toBool() );
    ui->rChannelCombo->setCurrentIndex( load.value( "rgbDitherControlRChannel" ).toInt() );
    ui->bChannelCombo->setCurrentIndex( load.value( "rgbDitherChannelGChannel" ).toInt() );
    ui->bChannelCombo->setCurrentIndex( load.value( "rgbDitherControlBChannel" ).toInt() );
    ui->formatControlCheck->setChecked( load.value( "formatControl" ).toBool() );
    ui->formatControlSwapYAndUVRadio->setChecked( load.value( "swapYandUV" ).toBool() );
    ui->formatControlISPYUVRadio_2->setChecked( load.value( "ispYUV2" ).toBool() );
    ui->formatControlISPRGBRadio->setChecked( load.value( "ispRGB" ).toBool() );
    ui->formatControlISPYUVRadio->setChecked( load.value( "ispYUV" ).toBool() );
    ui->formatControlISPRAWRadio->setChecked( load.value( "ispRAW" ).toBool() );
    ui->formatControlInternalCIFRAWRadio->setChecked( load.value( "interntalCIFRAW" ).toBool() );
    ui->formatControlExternalCIFRAWRadio->setChecked( load.value( "externalCIFRAW" ).toBool() );
    ui->formatControlExternalCIFYUVRadio->setChecked( load.value( "externalCIFYUV422bypass" ).toBool() );
}
