#include "cad_interface.h"
#include "widgetcalibration.h"
#include "widgetdepthmap.h"
#include "widgetfilemodecalibration.h"
#include "widgetcalibrationmode.h"
#include "windowdepthmap.h"
#include "widgetcheckboardinformation.h"
#include "widgetstatus.h"
#include "widgetleftinput.h"
#include "widgetleftoutput.h"
#include "widgetrightoutput.h"


QString CAD_Interface::m_pluginName = "pluginCalibrationAndDepth";

CAD_Interface::CAD_Interface(QObject *parent) :
    QObject(parent)
{
    m_widgetCalibration = new WidgetCalibration();
    m_widgetDepthMap = new WidgetDepthMap();
    m_widgetFilemodeCalibration = new WidgetFilemodeCalibration();
    m_widgetCalibrationMode = new WidgetCalibrationMode;
    m_WindowDepthMap=new WindowDepthMap();
    m_widgetCheckboardInformation = new WidgetCheckboardInformation();
    m_widgetStatus = new WidgetStatus();
    m_widgetLeftInput = new WidgetLeftInput();
    m_widgetLeftOutput = new WidgetLeftOutput();
    m_widgetRightOutput = new WidgetRightOutput();

    connect(m_widgetCalibration,&WidgetCalibration::sendStrToStatus,m_widgetStatus,&WidgetStatus::getText);//добавление нового оповещения в статус
    connect(m_WindowDepthMap,&WindowDepthMap::Number,m_widgetDepthMap,&WidgetDepthMap::depthMapOptions);//сигнал с слайдера windowdepthmap
    //тут будут connect между виджетами
    connect(m_widgetFilemodeCalibration,&WidgetFilemodeCalibration::sendVectorString,m_widgetCalibration,&WidgetCalibration::getImagelist); // отправка изображений на обработку
    connect(m_widgetCalibration,&WidgetCalibration::signalForTestDepthMap,m_widgetDepthMap,&WidgetDepthMap::depthMapping); //test
    connect(m_widgetCalibration,&WidgetCalibration::signalForInputLeft,m_widgetLeftInput,&WidgetLeftInput::showImage);
    connect(m_widgetCalibration,&WidgetCalibration::signalForOutput,m_widgetLeftOutput,&WidgetLeftOutput::showImage);
    connect(m_widgetCalibration,&WidgetCalibration::signalForOutputRight,m_widgetRightOutput,&WidgetRightOutput::showImage);
}

CAD_Interface::~CAD_Interface()
{
    delete m_widgetCalibration;
    delete m_widgetDepthMap;
    delete m_widgetFilemodeCalibration;
    delete m_widgetCalibrationMode;
    delete m_WindowDepthMap;
    delete m_widgetCheckboardInformation;
    delete m_widgetStatus;
    delete m_widgetLeftInput;
    delete m_widgetLeftOutput;
    delete m_widgetRightOutput;
}

const QString &CAD_Interface::pluginName() const
{
    return m_pluginName;
}

QWidget *CAD_Interface::showSettingsWidgetCalibration()
{
    return m_widgetCalibration;
}

QWidget *CAD_Interface::showSettingsWidgetCalibrationMode()
{
    return m_widgetCalibrationMode;
}

QWidget *CAD_Interface::showSettingsWidgetFilemodeCalibration()
{
    return m_widgetFilemodeCalibration;
}

QWidget *CAD_Interface::showSettingsWidgetDepthMap()
{
    return m_widgetDepthMap;
}

QWidget *CAD_Interface::showSettingsWidgetCheckboardInformation()
{
    return m_widgetCheckboardInformation;
}

QWidget *CAD_Interface::showSettingsWidgetStatus()
{
    return m_widgetStatus;
}

QWidget *CAD_Interface::showLeftInputImage()
{
    return m_widgetLeftInput;
}

QWidget *CAD_Interface::showLeftOutputImage()
{
    return m_widgetLeftOutput;
}

QWidget *CAD_Interface::showRightOutputImage()
{
    return m_widgetRightOutput;
}
