#include "imagemosaic.h"
#include "ui_imagemosaic.h"

imageMosaic::imageMosaic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::imageMosaic)
{
    ui->setupUi(this);
    centerWidget = new QWidget();
    setCentralWidget(centerWidget);
    widgetLayout = new QHBoxLayout();
    picture1 = new QLabel;
    picture2 = new QLabel;
    widgetLayout->addWidget(picture1);
    widgetLayout->addWidget(picture2);
    centerWidget->setLayout(widgetLayout);
    openFileAction = new QAction(tr("Open File"));
    Menu = ui->menubar->addMenu("File");
    Menu->addAction(openFileAction);
    image1 = new QImage();
    image2 = new QImage();

    connect(openFileAction,SIGNAL(triggered(bool)),this,SLOT(OpenFile()));
}

imageMosaic::~imageMosaic()
{
    delete ui;
}


void imageMosaic::OpenFile()
{
    if(count<2)
    {
    QString filename;
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
    }
    else
    {
        Mat rgb1;
        Mat rgb2;
        if(count == 0)
        {
            img1 = cv::imread(filename.toLatin1().data());
            if(img1.channels() == 3)
            {
               //cvtMatBGR2QImageRGB
               cvtColor(img1,rgb1,CV_BGR2RGB);
               *image1 = cvMat2QImage(img1);
            }
            else
            {
                *image1 = cvMat2QImage(img1);

            }
            picture1->setPixmap(QPixmap::fromImage(*image1));
            count++;
        }
        else if(count == 1)
        {
            img2 = cv::imread(filename.toLatin1().data());
            if(img2.channels() == 3)
            {
               //cvtMatBGR2QImageRGB
               cvtColor(img2,rgb2,CV_BGR2RGB);
               *image2 = cvMat2QImage(img2);
            }
            else
            {
                *image2 = cvMat2QImage(img2);

            }
            picture2->setPixmap(QPixmap::fromImage(*image2));
            count++;
        }


     }
    }
    else
        {
        return;
    }
}

//Mat转换为QImage
QImage imageMosaic::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
/*
void imageMosaic::imageMosaicStart()
{
    //灰度图转换
    Mat image1, image2;
    cvtColor(img1, image1, CV_RGB2GRAY);
    cvtColor(img2, image2, CV_RGB2GRAY);

    //提取特征点
    SurfFeatureDetector surfDetector(2000);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准
    vector<KeyPoint> keyPoint1, keyPoint2;
    surfDetector.detect(image1, keyPoint1);
    surfDetector.detect(image2, keyPoint2);

    //特征点描述，为下边的特征点匹配做准备
    SurfDescriptorExtractor SurfDescriptor;
    Mat imageDesc1, imageDesc2;
    SurfDescriptor.compute(image1, keyPoint1, imageDesc1);
    SurfDescriptor.compute(image2, keyPoint2, imageDesc2);

    FlannBasedMatcher matcher;
    vector<vector<DMatch> > matchePoints;
    vector<DMatch> GoodMatchePoints;

    vector<Mat> train_desc(1, imageDesc1);
    matcher.add(train_desc);
    matcher.train();

    matcher.knnMatch(imageDesc2, matchePoints, 2);
    qDebug << "total match points: " << matchePoints.size();

    // Lowe's algorithm,获取优秀匹配点
    for (int i = 0; i < matchePoints.size(); i++)
    {
       if (matchePoints[i][0].distance < 0.6 * matchePoints[i][1].distance)
       {
          GoodMatchePoints.push_back(matchePoints[i][0]);
       }
    }

    Mat first_match;
    drawMatches(image02, keyPoint2, image01, keyPoint1, GoodMatchePoints, first_match);
    imshow("first_match ", first_match);
    waitKey();
    return 0;

}*/
