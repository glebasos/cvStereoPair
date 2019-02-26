#ifndef WIDGETLEFTINPUT_H
#define WIDGETLEFTINPUT_H

#include <QWidget>

#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace Ui {
class WidgetLeftInput;
}

class WidgetLeftInput : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetLeftInput(QWidget *parent = nullptr);
    ~WidgetLeftInput();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::WidgetLeftInput *ui;
    cv::Mat m_img1;

public slots:
    void showImage(cv::Mat img1);
    void showStartImage(std::vector<std::string>);
};

#endif // WIDGETLEFTINPUT_H
