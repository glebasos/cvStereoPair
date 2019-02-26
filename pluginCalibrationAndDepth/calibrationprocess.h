#ifndef CALIBRATIONPROCESS_H
#define CALIBRATIONPROCESS_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class CalibrationProcess : public QObject
{
    Q_OBJECT
public:
    explicit CalibrationProcess(QObject *parent = nullptr);
    ~CalibrationProcess();

signals:
    void sendStrToStatus(QString);
    void signalForTestDepthMap(cv::Mat img1, cv::Mat img2);
    void signalForOutput(cv::Mat img1);
    void signalForOutputRight(cv::Mat img1);
    void signalForInputLeft(cv::Mat img1);
    void signalForInputRight(cv::Mat img1);
public slots:
    void stereoCalibration(const std::vector<std::string>& imagelist, cv::Size boardSize, float squareSize,
                           bool displayCorners, bool useCalibrated, bool showRectified);

private:
    QThread m_thread;
    QMutex m_mutex;
    QString m_str;
};

#endif // CALIBRATIONPROCESS_H
