#include "widgetrightinput.h"
#include "ui_widgetrightinput.h"

#include <QImage>
#include <QPixmap>

WidgetRightInput::WidgetRightInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRightInput)
{
    ui->setupUi(this);
}

WidgetRightInput::~WidgetRightInput()
{
    delete ui;
}

void WidgetRightInput::showImage(cv::Mat img1)
{
    m_img1 = img1;
    QImage leftInput;
    QPixmap leftPixmap;
    //QImage leftInput = QImage(img1.data,img1.cols,img1.rows,static_cast<int>(img1.step),QImage::Format_RGB888);
    if(img1.channels() == 3) {
            leftInput = QImage(img1.data,img1.cols,img1.rows,static_cast<int>(img1.step),QImage::Format_RGB888);
        } else {
            leftInput = QImage(img1.data, img1.cols,img1.rows, static_cast<int>(img1.step),QImage::Format_Indexed8);
        }
    if (!leftInput.isNull()) {
        leftPixmap = QPixmap::fromImage(leftInput);
        ui->labelInput->setAlignment(Qt::AlignCenter);
        ui->labelInput->setPixmap(leftPixmap.scaled(ui->labelInput->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
       }
}

void WidgetRightInput::resizeEvent(QResizeEvent *event)
{
    if(event)
    {
        if(!(ui->labelInput->text()=="Image not found."))
            showImage(m_img1);
    }
}
