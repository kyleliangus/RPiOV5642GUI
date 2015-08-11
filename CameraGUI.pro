#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T16:09:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    isp.cpp \
    awb.cpp \
    yuvgamma.cpp \
    rawgamma.cpp \
    pixelcancellation.cpp \
    parameter.cpp \
    previewimage.cpp

HEADERS  += mainwindow.h \
    isp.h \
    awb.h \
    yuvgamma.h \
    rawgamma.h \
    pixelcancellation.h \
    parameter.h \
    model.h \
    ov5642_regs.h \
    previewimage.h \
    operations.h

FORMS    += mainwindow.ui \
    isp.ui \
    awb.ui \
    yuvgamma.ui \
    rawgamma.ui \
    pixelcancellation.ui \
    previewimage.ui

