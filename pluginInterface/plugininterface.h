#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H
#include <QtPlugin>

class PluginInterface
{
public:
    PluginInterface(){}
    virtual ~PluginInterface(){}
    virtual const QString& pluginName() const = 0;
    virtual QWidget* showSettingsWidgetCalibration() = 0;
//    virtual QWidget* showSettingsWidgetPAN() = 0;
//    virtual QWidget* showSettingsWidgetProcessing() = 0;
//    virtual QWidget* showSettingsWidgetSave() = 0;
//    virtual QWidget* showSettingsWidgetStart() = 0;
};

QT_BEGIN_NAMESPACE

#define PluginInterface_iid "PrepareDeepLearning.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE


#endif // PLUGININTERFACE_H
