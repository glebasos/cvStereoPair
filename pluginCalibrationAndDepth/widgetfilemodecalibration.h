#ifndef WIDGETFILEMODECALIBRATION_H
#define WIDGETFILEMODECALIBRATION_H

#include <QWidget>
#include <QDir>
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace Ui {
class WidgetFilemodeCalibration;
}

class WidgetFilemodeCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFilemodeCalibration(QWidget *parent = nullptr);
    ~WidgetFilemodeCalibration();

signals:
    void sendVectorString(std::vector<std::string>);
    void sendVectorToStartLeft(cv::Mat);
    void sendVectorToStartRight(cv::Mat);

private slots:
    void on_b_selectDirectory_released();

    void on_b_selectFiles_released();

private:
    Ui::WidgetFilemodeCalibration *ui;

    QString m_path;
    QStringList m_filesSorted; //left - right; l - r;...
    QStringList m_files;
    std::vector<std::string> m_pairs;
};

#endif // WIDGETFILEMODECALIBRATION_H
