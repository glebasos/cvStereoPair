#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType< cv::Mat >("cv::Mat");
    //qRegisterMetaType<cv::Mat>("cv::Mat&");

    qRegisterMetaType< std::vector<std::string> >("std::vector<std::string>");
    qRegisterMetaType< cv::Size >("cv::Size");
    MainWindow w;
    w.show();


    return a.exec();
}
