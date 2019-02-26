#include "widgetleftinput.h"
#include "ui_widgetleftinput.h"

#include <QImage>
#include <QPixmap>
using namespace std;
using namespace cv;
WidgetLeftInput::WidgetLeftInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetLeftInput)
{
    ui->setupUi(this);

}

WidgetLeftInput::~WidgetLeftInput()
{
    delete ui;
}

void WidgetLeftInput::showImage(cv::Mat img1)
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

//          ui->labelInput->setAlignment(Qt::AlignCenter);
//          ui->pictureLabel->setPixmap(m_outPixmap.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void WidgetLeftInput::showStartImage(std::vector<std::string> _startImages)
{
//    int nimages = (int)_startImages.size()/2;
//    for(int i = 0; i < nimages; i++ )
//    {
//        for(int k = 0; k < 2; k++ )
//        {
//            const string& filename = _startImages[i*2+k];

//            Mat img_input = imread(filename, 0);

//            if(k==0){
//                imgL = cimg;
//                emit signalForInputLeft(img_input);
//                emit signalForOutput(imgL);
//            } else {
//                imgR = cimg;
//                emit signalForInputRight(img_input);
//                emit signalForOutputRight(imgR);
//                emit signalForTestDepthMap(imgL, imgR);
//            }


//        }
//        char c = (char)waitKey();
//        if( c == 27 || c == 'q' || c == 'Q' )
//            break;
//    }
}

void WidgetLeftInput::resizeEvent(QResizeEvent *event)
{
    if(event)
    {
        if(!(ui->labelInput->text()=="Image not found."))
            showImage(m_img1);
    }
}
