#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../pluginInterface/plugininterface.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    m_inputCamera1 = ui->outVideoImage_inputCamera1;
//    m_inputCamera2 = ui->outVideoImage_inputCamera2;
//    m_outputCamera1 = ui->outVideoImage_outputCamera1;
//    m_outputCamera2 = ui->outVideoImage_outputCamera2;

    QDir pluginsDir(qApp->applicationDirPath());
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if (plugin) {
            m_interface = qobject_cast<PluginInterface *>(plugin);
            if (m_interface){
                qDebug()<<m_interface->pluginName();

            }
        }
    }

    QVBoxLayout* vbox_calibControl = new QVBoxLayout();
    QVBoxLayout* vbox_filemodeCalib = new QVBoxLayout();
    QVBoxLayout* vbox_selectCalibMode = new QVBoxLayout();
    QVBoxLayout* vbox_depthMap = new QVBoxLayout();
    QVBoxLayout* vbox_checkboardInfo = new QVBoxLayout();
    QVBoxLayout* vbox_status = new QVBoxLayout();
    QVBoxLayout* vbox_leftInput = new QVBoxLayout();
    QVBoxLayout* vbox_leftOutput = new QVBoxLayout();
    QVBoxLayout* vbox_rightOutput = new QVBoxLayout();
    QVBoxLayout* vbox_rightInput = new QVBoxLayout();

    if(m_interface){
        vbox_calibControl->addWidget(m_interface->showSettingsWidgetCalibration());
        vbox_filemodeCalib->addWidget(m_interface->showSettingsWidgetFilemodeCalibration());
        vbox_selectCalibMode->addWidget(m_interface->showSettingsWidgetCalibrationMode());
        vbox_depthMap->addWidget(m_interface->showSettingsWidgetDepthMap());
        vbox_checkboardInfo->addWidget(m_interface->showSettingsWidgetCheckboardInformation());             //блок для добавления виджетов
        vbox_status->addWidget(m_interface->showSettingsWidgetStatus());
        vbox_leftInput->addWidget(m_interface->showLeftInputImage());
        vbox_leftOutput->addWidget(m_interface->showLeftOutputImage());
        vbox_rightOutput->addWidget(m_interface->showRightOutputImage());
        vbox_rightInput->addWidget(m_interface->showRightInputImage());
//        myVBox->addWidget(m_interface->showSettingsWidgetStart());
    }
    ui->layout_calibControl->addLayout(vbox_calibControl);
    ui->layout_filemodeCalib->addLayout(vbox_filemodeCalib);
    ui->layout_selectCalibMode->addLayout(vbox_selectCalibMode);
    ui->layout_depthMap->addLayout(vbox_depthMap);
    ui->layout_checkboardInfo->addLayout(vbox_checkboardInfo);
    ui->layout_status->addLayout(vbox_status);
    ui->layout_leftInput->addLayout(vbox_leftInput);
    ui->layout_leftOutput->addLayout(vbox_leftOutput);
    ui->layout_rightOutput->addLayout(vbox_rightOutput);
    ui->layout_rightInput->addLayout(vbox_rightInput);

}

MainWindow::~MainWindow()
{
    if(m_interface)
        delete m_interface;
    delete ui;
}

