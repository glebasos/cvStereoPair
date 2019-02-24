#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T18:58:14
#
#-------------------------------------------------
include(../rep-buildproject.pri)
include(../rep-opencv.pri)
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
    widgetfilemodecalibration.cpp

HEADERS += \
    cad_interface.h \
    widgetcalibration.h \
    widgetdepthmap.h \
    widgetfilemodecalibration.h
DISTFILES += pluginCalibrationAndDepth.json 

FORMS += \
    widgetcalibration.ui \
    widgetdepthmap.ui \
    widgetfilemodecalibration.ui


