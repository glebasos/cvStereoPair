#include "calibrationprocess.h"
#include <QDebug>

CalibrationProcess::CalibrationProcess(QObject *parent) : QObject(parent)
{
    this->moveToThread(&m_thread);
    m_thread.start();

}

CalibrationProcess::~CalibrationProcess()
{
    m_thread.quit();
    m_thread.wait();
}

