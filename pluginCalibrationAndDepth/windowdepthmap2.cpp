#include "windowdepthmap2.h"
#include "ui_windowdepthmap2.h"

windowdepthmap2::windowdepthmap2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowdepthmap2)
{
    ui->setupUi(this);
    m_outputImageLable = ui->outVideoImage_DepthMap;
    connect(ui->spinBox, SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)) );
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)) );
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)),ui->horizontalSlider_2,SLOT(setValue(int)) );
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),ui->spinBox_2,SLOT(setValue(int)) );

}
void windowdepthmap2::on_horizontalSlider_actionTriggered(int action)
{
   emit Number(action);
}
windowdepthmap2::~windowdepthmap2()
{
    delete ui;
}

void windowdepthmap2::OpenWindow()
{
    this->show();
}

void windowdepthmap2::OpenPicture(cv::Mat _image)
{
    m_img1 = _image;
    QImage m_testImage;
    if(_image.channels()== 3){
        m_testImage = QImage(_image.data,_image.cols,_image.rows,static_cast<int>(_image.step),QImage::Format_RGB888);
    }
    else{
        m_testImage = QImage(_image.data, _image.cols,_image.rows, static_cast<int>(_image.step),QImage::Format_Indexed8);
    }
    if (!m_testImage.isNull()){
        m_outputImageLable->setAlignment(Qt::AlignCenter);
        m_outputImageLable->setPixmap(QPixmap::fromImage(m_testImage).scaled(m_outputImageLable->size(),
                                                                             Qt::IgnoreAspectRatio, Qt::FastTransformation));
    }
}

void windowdepthmap2::resizeEvent(QResizeEvent *event)
{
    if(event)
    {
        if(!(ui->outVideoImage_DepthMap->text()=="Image not found."))
            OpenPicture(m_img1);
    }
}
