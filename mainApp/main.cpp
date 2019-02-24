#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType< cv::Mat >("cv::Mat");
    MainWindow w;
    w.show();


    return a.exec();
}
