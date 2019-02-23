#ifndef CAD_INTERFACE_H
#define CAD_INTERFACE_H

#include <QObject>
#include "../pluginInterface/plugininterface.h"
#include <opencv2/core.hpp>

class WidgetCalibration;
class WidgetDepthMap;

class CAD_Interface : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "pluginCalibrationAndDepth.json")
    Q_INTERFACES(PluginInterface)

public:
    CAD_Interface(QObject *parent = nullptr);
    ~CAD_Interface();
    virtual const QString& pluginName() const;
    virtual QWidget* showSettingsWidgetCalibration();

signals:

public slots:

private:
    WidgetCalibration* m_widgetCalibration = nullptr;
    WidgetDepthMap* m_widgetDepthMap = nullptr;
    static QString m_pluginName;
};

#endif // CAD_INTERFACE_H
