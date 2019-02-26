#ifndef WINDOWDEPTHMAP2_H
#define WINDOWDEPTHMAP2_H

#include <QWidget>
#include<QBoxLayout>
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<QLabel>
namespace Ui {
class windowdepthmap2;
}

class windowdepthmap2 : public QWidget
{
    Q_OBJECT

public:
    QLabel* m_outputImageLable = nullptr;
    explicit windowdepthmap2(QWidget *parent = nullptr);
    ~windowdepthmap2();
    void resizeEvent(QResizeEvent *event);

signals:
   void Number(int n);

public slots:
   void OpenWindow();
   void OpenPicture(cv::Mat a);

private slots:
   void on_horizontalSlider_actionTriggered(int action);

private:
    Ui::windowdepthmap2 *ui;
    cv::Mat m_img1;
};

#endif // WINDOWDEPTHMAP2_H
