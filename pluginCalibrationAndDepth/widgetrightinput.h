#ifndef WIDGETRIGHTINPUT_H
#define WIDGETRIGHTINPUT_H

#include <QWidget>

#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace Ui {
class WidgetRightInput;
}

class WidgetRightInput : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRightInput(QWidget *parent = nullptr);
    ~WidgetRightInput();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::WidgetRightInput *ui;
    cv::Mat m_img1;

public slots:
    void showImage(cv::Mat img1);
};

#endif // WIDGETRIGHTINPUT_H
