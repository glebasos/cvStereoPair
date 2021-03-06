#include "widgetcalibration.h"
#include "ui_widgetcalibration.h"
#include <QDebug>
using namespace cv;
using namespace std;

WidgetCalibration::WidgetCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCalibration)
{
    ui->setupUi(this);
    //connect(ui->b_calibration,&QPushButton::clicked,this,&WidgetCalibration::stereoCalibration);

    m_boardSize.width = 9;
    m_boardSize.height = 6;
}

WidgetCalibration::~WidgetCalibration()
{
    delete ui;
}

void WidgetCalibration::stereoCalibration()
{
    if( m_imagelist.size() % 2 != 0 )
    {
        m_str = "- Error: the image list contains odd (non-even) number of elements";
        emit sendStrToStatus(m_str);
        return;
    }

    const int maxScale = 2;
    // ARRAY AND VECTOR STORAGE:

    vector<vector<Point2f> > imagePoints[2];
    vector<vector<Point3f> > objectPoints;
    Size imageSize;

    int i, j, k, nimages = (int)m_imagelist.size()/2;

    imagePoints[0].resize(nimages);
    imagePoints[1].resize(nimages);
    vector<string> goodImageList;

    for( i = j = 0; i < nimages; i++ )
    {

        for( k = 0; k < 2; k++ )
        {
            const string& filename = m_imagelist[i*2+k];

            Mat img = imread(filename, 0);

            //emit signalForInputLeft(img);

            emit signalForInputLeft(img);
            emit signalForInputRight(img);


            if(img.empty())
                break;

            if( imageSize == Size() )
                imageSize = img.size();
            else if( img.size() != imageSize )
            {

                m_str = "- The image " + QString::fromStdString(filename) + " has the size different from the first image size. Skipping the pair";
                emit sendStrToStatus(m_str);
                break;
            }
            bool found = false;
            vector<Point2f>& corners = imagePoints[k][j];
            for( int scale = 1; scale <= maxScale; scale++ )
            {
                Mat timg;
                if( scale == 1 )
                    timg = img;
                else
                    cv::resize(img, timg, Size(), scale, scale, INTER_LINEAR_EXACT);
                found = findChessboardCorners(timg, m_boardSize, corners,
                                              CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
                if( found )
                {
                    if( scale > 1 )
                    {
                        Mat cornersMat(corners);
                        cornersMat *= 1./scale;
                    }
                    break;
                }

            }
            if( m_displayCorners )
            {
                //cout << filename << endl;    ранее было использовано, пока не удалять
                Mat cimg, cimg1;
                cvtColor(img, cimg, COLOR_GRAY2BGR);
                drawChessboardCorners(cimg, m_boardSize, corners, found);
                double sf = 640./MAX(img.rows, img.cols);
                cv::resize(cimg, cimg1, Size(), sf, sf, INTER_LINEAR_EXACT);
                imshow("corners", cimg1);
                char c = (char)waitKey(500);
                if( c == 27 || c == 'q' || c == 'Q' ) //Allow ESC to quit
                    exit(-1);
            }
            else {
                //putchar('.');
            }
            if( !found )
                break;
            cornerSubPix(img, corners, Size(11,11), Size(-1,-1),
                         TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,
                                      30, 0.01));
        }
        if( k == 2 )
        {
            goodImageList.push_back(m_imagelist[i*2]);
            goodImageList.push_back(m_imagelist[i*2+1]);
            j++;
        }
    }

    m_str = "- " + QString::number(j) + " pairs have been successfully detected.";
    emit sendStrToStatus(m_str);
    //cout << j << " pairs have been successfully detected.\n";
    nimages = j;
    if( nimages < 2 )
    {
        m_str = "- Error: too little pairs to run the calibration";
        emit sendStrToStatus(m_str);
        return;
    }

    imagePoints[0].resize(nimages);
    imagePoints[1].resize(nimages);
    objectPoints.resize(nimages);

    for( i = 0; i < nimages; i++ )
    {
        for( j = 0; j < m_boardSize.height; j++ )
            for( k = 0; k < m_boardSize.width; k++ )
                objectPoints[i].push_back(Point3f(k*m_squareSize, j*m_squareSize, 0));
    }

    m_str = "- Running stereo calibration ...";
    emit sendStrToStatus(m_str);

    Mat cameraMatrix[2], distCoeffs[2];

    cameraMatrix[0] = initCameraMatrix2D(objectPoints,imagePoints[0],imageSize,0);

    cameraMatrix[1] = initCameraMatrix2D(objectPoints,imagePoints[1],imageSize,0);

    Mat R, T, E, F;

    int64 t = getTickCount();
    double rms = stereoCalibrate(objectPoints, imagePoints[0], imagePoints[1],
            cameraMatrix[0], distCoeffs[0],
            cameraMatrix[1], distCoeffs[1],
            imageSize, R, T, E, F,
            CALIB_FIX_ASPECT_RATIO +
            CALIB_ZERO_TANGENT_DIST +
            CALIB_USE_INTRINSIC_GUESS +
            CALIB_SAME_FOCAL_LENGTH +
            CALIB_RATIONAL_MODEL +
            CALIB_FIX_K3 + CALIB_FIX_K4 + CALIB_FIX_K5,
            TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 100, 1e-5) );

    t = getTickCount() - t;
    //printf("Time elapsed for calibrate: %fms\n", t*1000/getTickFrequency());

    m_str = "- Time elapsed for calibrate: " + QString::number(t*1000/getTickFrequency()) + "ms";
    emit sendStrToStatus(m_str);

    //cout << "done with RMS error=" << rms << endl;

    m_str = "- done with RMS error=" + QString::number(rms);
    emit sendStrToStatus(m_str);

    // CALIBRATION QUALITY CHECK
    // because the output fundamental matrix implicitly
    // includes all the output information,
    // we can check the quality of calibration using the
    // epipolar geometry constraint: m2^t*F*m1=0
    double err = 0;
    int npoints = 0;
    vector<Vec3f> lines[2];
    for( i = 0; i < nimages; i++ )
    {
        int npt = (int)imagePoints[0][i].size();
        Mat imgpt[2];
        for( k = 0; k < 2; k++ )
        {
            imgpt[k] = Mat(imagePoints[k][i]);
            undistortPoints(imgpt[k], imgpt[k], cameraMatrix[k], distCoeffs[k], Mat(), cameraMatrix[k]);
            computeCorrespondEpilines(imgpt[k], k+1, F, lines[k]);
        }
        for( j = 0; j < npt; j++ )
        {
            double errij = fabs(imagePoints[0][i][j].x*lines[1][j][0] +
                    imagePoints[0][i][j].y*lines[1][j][1] + lines[1][j][2]) +
                    fabs(imagePoints[1][i][j].x*lines[0][j][0] +
                    imagePoints[1][i][j].y*lines[0][j][1] + lines[0][j][2]);
            err += errij;
        }
        npoints += npt;
    }

    double temp_number = err/npoints;
    m_str = "- average epipolar err = " + QString::number(temp_number);
    emit sendStrToStatus(m_str);
    //cout << "average epipolar err = " <<  err/npoints << endl;

    // save intrinsic parameters
    FileStorage fs("intrinsics.yml", FileStorage::WRITE);
    if( fs.isOpened() )
    {
        fs << "M1" << cameraMatrix[0] << "D1" << distCoeffs[0] <<
              "M2" << cameraMatrix[1] << "D2" << distCoeffs[1];
        fs.release();
    }
    else {
        m_str = "- Error: can not save the intrinsic parameters";
        emit sendStrToStatus(m_str);
        //cout << "Error: can not save the intrinsic parameters\n";
    }
    Mat R1, R2, P1, P2, Q;
    Rect validRoi[2];

    stereoRectify(cameraMatrix[0], distCoeffs[0],
            cameraMatrix[1], distCoeffs[1],
            imageSize, R, T, R1, R2, P1, P2, Q,
            CALIB_ZERO_DISPARITY, 1, imageSize, &validRoi[0], &validRoi[1]);

    fs.open("extrinsics.yml", FileStorage::WRITE);
    if( fs.isOpened() )
    {
        fs << "R" << R << "T" << T << "R1" << R1 << "R2" << R2 << "P1" << P1 << "P2" << P2 << "Q" << Q;
        fs.release();
    }
    else {
        m_str = "- Error: can not save the extrinsic parameters";
        emit sendStrToStatus(m_str);
        //cout << "Error: can not save the extrinsic parameters\n";
    }

    // OpenCV can handle left-right
    // or up-down camera arrangements
    bool isVerticalStereo = fabs(P2.at<double>(1, 3)) > fabs(P2.at<double>(0, 3));

    // COMPUTE AND DISPLAY RECTIFICATION
    if( !m_showRectified )
        return;

    Mat rmap[2][2];
    // IF BY CALIBRATED (BOUGUET'S METHOD)
    if( m_useCalibrated )
    {
        // we already computed everything
        //cout << "BOUGUET" << endl;
    }
    // OR ELSE HARTLEY'S METHOD
    else
        // use intrinsic parameters of each camera, but
        // compute the rectification transformation directly
        // from the fundamental matrix
    {
        //cout << "HARTLEY" << endl;
        vector<Point2f> allimgpt[2];
        for( k = 0; k < 2; k++ )
        {
            for( i = 0; i < nimages; i++ )
                std::copy(imagePoints[k][i].begin(), imagePoints[k][i].end(), back_inserter(allimgpt[k]));
        }
        F = findFundamentalMat(Mat(allimgpt[0]), Mat(allimgpt[1]), FM_8POINT, 0, 0);
        Mat H1, H2;
        stereoRectifyUncalibrated(Mat(allimgpt[0]), Mat(allimgpt[1]), F, imageSize, H1, H2, 3);

        R1 = cameraMatrix[0].inv()*H1*cameraMatrix[0];
        R2 = cameraMatrix[1].inv()*H2*cameraMatrix[1];
        P1 = cameraMatrix[0];
        P2 = cameraMatrix[1];
    }

    //Precompute maps for cv::remap()
    initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
    initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

    Mat canvas;
    double sf;
    int w, h;
    if( !isVerticalStereo )
    {
        sf = 600./MAX(imageSize.width, imageSize.height);
        w = cvRound(imageSize.width*sf);
        h = cvRound(imageSize.height*sf);
        canvas.create(h, w*2, CV_8UC3);
    }
    else
    {
        sf = 300./MAX(imageSize.width, imageSize.height);
        w = cvRound(imageSize.width*sf);
        h = cvRound(imageSize.height*sf);
        canvas.create(h*2, w, CV_8UC3);
    }
    Mat imgR, imgL;
    for( i = 0; i < nimages; i++ )
    {
        for( k = 0; k < 2; k++ )
        {
            const string& filename = m_imagelist[i*2+k];

            Mat img_input = imread(filename, 0);


            Mat img = imread(goodImageList[i*2+k], 0), rimg, cimg;
            remap(img, rimg, rmap[k][0], rmap[k][1], INTER_LINEAR);
            cvtColor(rimg, cimg, COLOR_GRAY2BGR);
            Mat canvasPart = !isVerticalStereo ? canvas(Rect(w*k, 0, w, h)) : canvas(Rect(0, h*k, w, h));
            cv::resize(cimg, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
            if(k==0){
                imgL = cimg;
                emit signalForInputLeft(img_input);
                emit signalForOutput(imgL);
            } else {
                imgR = cimg;
                emit signalForInputRight(img_input);
                emit signalForOutputRight(imgR);
                emit signalForTestDepthMap(imgL, imgR);


            }

            if( m_useCalibrated )
            {
                Rect vroi(cvRound(validRoi[k].x*sf), cvRound(validRoi[k].y*sf),
                          cvRound(validRoi[k].width*sf), cvRound(validRoi[k].height*sf));
                rectangle(canvasPart, vroi, Scalar(0,0,255), 3, 8);
            }
        }

        if( !isVerticalStereo )
            for( j = 0; j < canvas.rows; j += 16 )
                line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);
        else
            for( j = 0; j < canvas.cols; j += 16 )
                line(canvas, Point(j, 0), Point(j, canvas.rows), Scalar(0, 255, 0), 1, 8);
        imshow("rectified", canvas);
        char c = (char)waitKey();
        if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }
}

void WidgetCalibration::getImagelist(const std::vector<string>& _imagelist)
{
    m_imagelist = _imagelist;
}

void WidgetCalibration::getBoardSize(Size _boardSize)
{
    m_boardSize = _boardSize;
}

void WidgetCalibration::getSquareSize(float _squareSize)
{
    // доделать
}

void WidgetCalibration::on_b_Undistortion_clicked()
{
    // продумать и доделать
}

void WidgetCalibration::on_cb_displayCorners_stateChanged(int arg1)
{
    if(arg1==2){
        m_displayCorners = true;
        m_str = "- display corners: on";
        emit sendStrToStatus(m_str);
    } else {
        m_displayCorners = false;
        m_str = "- display corners: off";
        emit sendStrToStatus(m_str);
    }
}

void WidgetCalibration::on_rb_Bouguet_clicked()
{
    m_useCalibrated = true;
    m_str = "- Bouget: on";
    emit sendStrToStatus(m_str);
}

void WidgetCalibration::on_rb_Hartley_clicked()
{
    m_useCalibrated = false;
    m_str = "- Hartley: on";
    emit sendStrToStatus(m_str);
}

void WidgetCalibration::on_b_calibration_clicked()
{
    emit startCalibration(m_imagelist, m_boardSize, m_squareSize, m_displayCorners, m_useCalibrated, m_showRectified);
}
