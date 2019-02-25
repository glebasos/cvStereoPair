#ifndef WIDGETLEFTOUTPUT_H
#define WIDGETLEFTOUTPUT_H

#include <QWidget>

#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace Ui {
class WidgetLeftOutput;
}

class WidgetLeftOutput : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetLeftOutput(QWidget *parent = nullptr);
    ~WidgetLeftOutput();

private:
    Ui::WidgetLeftOutput *ui;

public slots:
    void showImage(cv::Mat img1);
};

#endif // WIDGETLEFTOUTPUT_H
