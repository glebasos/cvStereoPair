#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T18:58:14
#
#-------------------------------------------------
include(../../rep-buildproject.pri)
include(../../rep-opencv.pri)
QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pluginCalibrationAndDepth
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH +=../pluginInterface/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cad_interface.cpp \
    widgetcalibration.cpp \
    widgetdepthmap.cpp \
    widgetfilemodecalibration.cpp \
    widgetcalibrationmode.cpp \
    widgetcheckboardinformation.cpp \
    widgetstatus.cpp \
    windowdepthmap2.cpp \
    widgetleftinput.cpp \
    widgetleftoutput.cpp \
    widgetrightoutput.cpp \
    calibrationprocess.cpp \
    widgetrightinput.cpp

HEADERS += \
    cad_interface.h \
    widgetcalibration.h \
    widgetdepthmap.h \
    widgetfilemodecalibration.h \
    widgetcalibrationmode.h \
    widgetcheckboardinformation.h \
    widgetstatus.h \
    windowdepthmap2.h \
    widgetleftinput.h \
    widgetleftoutput.h \
    widgetrightoutput.h \
    calibrationprocess.h \
    widgetrightinput.h \

DISTFILES += pluginCalibrationAndDepth.json 

FORMS += \
    widgetcalibration.ui \
    widgetdepthmap.ui \
    widgetfilemodecalibration.ui \
    widgetcalibrationmode.ui \
    widgetcheckboardinformation.ui \
    widgetstatus.ui \
    windowdepthmap2.ui \
    widgetleftinput.ui \
    widgetleftoutput.ui \
    widgetrightoutput.ui \
    widgetrightinput.ui



