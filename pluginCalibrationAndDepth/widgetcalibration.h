#ifndef WIDGETCALIBRATION_H
#define WIDGETCALIBRATION_H

#include <QWidget>

#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

namespace Ui {
class WidgetCalibration;
}

class WidgetCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCalibration(QWidget *parent = nullptr);
    ~WidgetCalibration();

public slots:
    void stereoCalibration();
    void getImagelist(const std::vector<std::string>& _imagelist);
    void getBoardSize(cv::Size _boardSize);
    void getSquareSize(float _squareSize);

signals:
    void sendStrToStatus(QString str);
    void signalForTestDepthMap(cv::Mat& img1, cv::Mat& img2);
    void signalForOutput(cv::Mat img1);
    void signalForOutputRight(cv::Mat img1);
    void signalForInputLeft(cv::Mat img1);
    void signalForInputRight(cv::Mat img1);


private slots:
    void on_b_Undistortion_clicked();
    void on_cb_displayCorners_stateChanged(int arg1);
    void on_rb_Bouguet_clicked();
    void on_rb_Hartley_clicked();

private:
    Ui::WidgetCalibration *ui;
    bool m_displayCorners = false;
    bool m_useCalibrated = true;
    bool m_showRectified = true;
    cv::Size m_boardSize;
    float m_squareSize; // поставить на 1.0f для нормальной работы
    std::vector<std::string> m_imagelist;
    QString m_str;
};

#endif // WIDGETCALIBRATION_H
