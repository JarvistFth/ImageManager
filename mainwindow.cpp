#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MenuCreate();
    imageShowWidget = new QWidget(this);
    setCentralWidget(imageShowWidget);
    mainLayout = new QVBoxLayout();
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene,this);

    functionStack = new QStackedWidget();
    //initwidget();
    twoValueDialog = new TwoValueDialog(this);
    imageMosaicWindow = new imageMosaic(this);
    windDialog = new WindDialog(this);
    blurDialog = new BlurDialog(this);
    gaussianBlurDialog = new GaussianBlurDialog(this);
    medianBlurDialog = new MedianBlurDialog(this);
    bilateralBlurDialog = new BilateralBlurDialog(this);


    //imageLabel = new QLabel();
    imageShowWidget->setLayout(mainLayout);
    mainLayout->addWidget(view);
    //mainLayout->addWidget(imageLabel);


    connect(twoValueDialog,SIGNAL(preview()),this,SLOT(showTwoValuePreview()));
    connect(twoValueDialog,SIGNAL(valueChanged()),this,SLOT(showTwoValueImage()));
    connect(twoValueDialog,SIGNAL(noChanged()),this,SLOT(returnOriginImage()));
    connect(windDialog,SIGNAL(windPreview()),this,SLOT(ShowWindowEffectPreview()));
    connect(windDialog,SIGNAL(windNoChanged()),this,SLOT(returnOriginImage()));
    connect(windDialog,SIGNAL(windValueChanged()),this,SLOT(ShowWindowEffect()));
    connect(blurDialog,SIGNAL(BlurPreview()),this,SLOT(ShowSimpleBlurEffect()));
    connect(blurDialog,SIGNAL(BlurValueChanged()),this,SLOT(ShowSimpleBlurEffect()));
    connect(blurDialog,SIGNAL(BlurnoChanged()),this,SLOT(returnOriginImage()));
    connect(gaussianBlurDialog,SIGNAL(GaussianBlurPreview()),this,SLOT(ShowGaussianBlurEffect()));
    connect(gaussianBlurDialog,SIGNAL(GaussianBlurValueChanged()),this,SLOT(ShowGaussianBlurEffect()));
    connect(gaussianBlurDialog,SIGNAL(GaussianBlurnoChanged()),this,SLOT(returnOriginImage()));
    connect(medianBlurDialog,SIGNAL(MedianBlurPreview()),this,SLOT(ShowMedianBlurEffect()));
    connect(medianBlurDialog,SIGNAL(MedianBlurValueChanged()),this,SLOT(ShowMedianBlurEffect()));
    connect(medianBlurDialog,SIGNAL(MedianBlurnoChanged()),this,SLOT(returnOriginImage()));
    connect(bilateralBlurDialog,SIGNAL(BilateralBlurPreview()),this,SLOT(ShowBilateralBlurEffect()));
    connect(bilateralBlurDialog,SIGNAL(BilateralBlurValuenoChanged()),this,SLOT(returnOriginImage()));



}

MainWindow::~MainWindow()
{
    delete ui;
}


//创建导航菜单
void MainWindow::MenuCreate()
{
    //文件菜单
    FileMenu = ui->menuBar->addMenu(tr("File(&F)"));
    OpenFileAction = FileMenu->addAction(tr("Open(&O)"));
    SaveFileAction = FileMenu->addAction(tr("Save(&S)"));
    FileMenu->addSeparator();
    QuitAction = FileMenu->addAction(tr("Quit(&Q)"));
    img = new QImage();
    EnlargeAction = new QAction();
    EnlargeAction->setIcon(QIcon(":/new/prefix1/image/large.png"));
    ShrinkAction = new QAction();
    ShrinkAction->setIcon(QIcon(":/new/prefix1/image/small.png"));
    ui->mainToolBar->addAction(EnlargeAction);
    ui->mainToolBar->addAction(ShrinkAction);
    QMatrix matrix;

    //图像菜单
    ImageMenu = ui->menuBar->addMenu(tr("Image(&I)"));
    ImageModeMenu = new QMenu(tr("Mode"));
    ImageMenu->addMenu(ImageModeMenu);
    GreyImageAction = ImageModeMenu->addAction(tr("GreyImage(&G)"));
    RGBImageAction = ImageModeMenu->addAction(tr("RGBImage"));
    HSVImageAction = ImageModeMenu->addAction(tr("HSVImage"));
    TwoValueAction = ImageModeMenu->addAction(tr("TwoValueImage"));

    //调整菜单
    ImageAdjustMenu = new QMenu(tr("Adjust"));
    ImageMenu->addMenu(ImageAdjustMenu);
    BrightAction = ImageAdjustMenu->addAction(tr("Brightness&Contract"));
    HSBAction  = ImageAdjustMenu->addAction(tr("HSB Adjust"));

    //图像处理菜单
    ImageProcess = ui->menuBar->addMenu(tr("ImageProcess"));
    ImageMosaic = ImageProcess->addAction("ImageMosaic");

    //滤镜菜单
    FilterMenu = ui->menuBar->addMenu(tr("Filter"));
    OilPaintingAction  = FilterMenu->addAction(tr("Oil Painting"));
    ReliefAction = FilterMenu->addAction(tr("Relief Painting"));
    CarvingAction = FilterMenu->addAction(tr("Carving Painting"));
    ColorTransformationMenu = new QMenu(tr("Color Transform"));
    FilterMenu->addMenu(ColorTransformationMenu);
    color1 = ColorTransformationMenu->addAction(tr("AUTUMN"));
    color2 = ColorTransformationMenu->addAction(tr("BONE"));
    color3 = ColorTransformationMenu->addAction(tr("JET"));
    color4 = ColorTransformationMenu->addAction(tr("WINTER"));
    color5 = ColorTransformationMenu->addAction(tr("RAINBOW"));
    color6 = ColorTransformationMenu->addAction(tr("OCEAN"));
    color7 = ColorTransformationMenu->addAction(tr("SUMMER"));
    color8 = ColorTransformationMenu->addAction(tr("SPRING"));
    color9 = ColorTransformationMenu->addAction(tr("COOL"));
    color10 = ColorTransformationMenu->addAction(tr("HSV"));
    color11 = ColorTransformationMenu->addAction(tr("PINK"));
    color12 = ColorTransformationMenu->addAction(tr("HOT"));
    oldcolor = ColorTransformationMenu->addAction(tr("OLD_COLOR"));
    lightColor = ColorTransformationMenu->addAction(tr("LIGHT"));
    whiteAverage = ColorTransformationMenu->addAction(tr("WhiteAverage"));
    hot = ColorTransformationMenu->addAction(tr("HOT"));
    cold = ColorTransformationMenu->addAction(tr("COLD"));
    suMiao = ColorTransformationMenu->addAction(tr("sumiao"));

    windAction = FilterMenu->addAction(tr("wind"));
    blurMenu = new QMenu(tr("Blur"));
    FilterMenu->addMenu(blurMenu);
    blurAction = blurMenu->addAction(tr("Simple Blur"));
    GaussianAction = blurMenu->addAction(tr("Gaussian Blur"));
    MedianAction = blurMenu->addAction(tr("Median Blur"));
    BilateralAction = blurMenu->addAction(tr("Bilateral Blur"));

    //噪声菜单
    noiseMenu = ui->menuBar->addMenu(tr("Noise"));
    addGaussianNoiseAction = noiseMenu->addAction(tr("Gaussian Noise"));
    addSaltNoiseAction = noiseMenu->addAction(tr("Salt Noise"));
    addPepperNoiseAction = noiseMenu->addAction(tr("Pepper Noise"));
    removeNoiseAction = noiseMenu->addAction(tr("Remove Noise"));

    connect(OpenFileAction,SIGNAL(triggered(bool)),this,SLOT(OpenImage()));
    connect(EnlargeAction,SIGNAL(triggered(bool)),this,SLOT(ImageInZoom()));
    connect(ShrinkAction,SIGNAL(triggered(bool)),this,SLOT(ImageReduce()));
    connect(SaveFileAction,SIGNAL(triggered(bool)),this,SLOT(SaveImage()));
    connect(GreyImageAction,SIGNAL(triggered(bool)),this,SLOT(ShowGreyImage()));
    connect(RGBImageAction,SIGNAL(triggered(bool)),this,SLOT(showRGBImage()));
    connect(HSVImageAction,SIGNAL(triggered(bool)),this,SLOT(showHSVImage()));
    connect(TwoValueAction,SIGNAL(triggered(bool)),this,SLOT(OpenTwoValueImageWindow()));
    connect(BrightAction,SIGNAL(triggered(bool)),this,SLOT(OpenBrightAdjustWindow()));
    connect(HSBAction,SIGNAL(triggered(bool)),this,SLOT(openHSBDialog()));
    connect(ImageMosaic,SIGNAL(triggered(bool)),this,SLOT(OpenImageMosaicWindow()));
    connect(OilPaintingAction,SIGNAL(triggered(bool)),this,SLOT(ShowOilPainting()));
    connect(CarvingAction,SIGNAL(triggered(bool)),this,SLOT(ShowCarvingPainting()));
    connect(color1,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform1()));
    connect(color2,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform2()));
    connect(color3,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform3()));
    connect(color4,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform4()));
    connect(color5,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform5()));
    connect(color6,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform6()));
    connect(color7,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform7()));
    connect(color8,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform8()));
    connect(color9,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform9()));
    connect(color10,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform10()));
    connect(color11,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform11()));
    connect(color12,SIGNAL(triggered(bool)),this,SLOT(ShowColorTransform12()));
    connect(ReliefAction,SIGNAL(triggered(bool)),this,SLOT(ShowReliefPainting()));
    connect(windAction,SIGNAL(triggered(bool)),this,SLOT(OpenWindEffectWindow()));
    connect(blurAction,SIGNAL(triggered(bool)),this,SLOT(OpenBlurWindow()));
    connect(GaussianAction,SIGNAL(triggered(bool)),this,SLOT(OpenGaussianBlurWindow()));
    connect(MedianAction,SIGNAL(triggered(bool)),this,SLOT(OpenMedianBlurWindow()));
    connect(BilateralAction,SIGNAL(triggered(bool)),this,SLOT(OpenBilateralBlurWindow()));
    connect(oldcolor,SIGNAL(triggered(bool)),this,SLOT(oldphoto()));
    connect(hot,SIGNAL(triggered(bool)),this,SLOT(hotphoto()));
    connect(cold,SIGNAL(triggered(bool)),this,SLOT(coldphoto()));
    connect(whiteAverage,SIGNAL(triggered(bool)),this,SLOT(whiteAve()));
    connect(lightColor,SIGNAL(triggered(bool)),this,SLOT(light()));
    connect(suMiao,SIGNAL(triggered(bool)),this,SLOT(sumiao()));
    connect(addSaltNoiseAction,SIGNAL(triggered(bool)),this,SLOT(addSaltNoiseEffect()));
    connect(addPepperNoiseAction,SIGNAL(triggered(bool)),this,SLOT(addPepperNoiseEffect()));
    connect(addGaussianNoiseAction,SIGNAL(triggered(bool)),this,SLOT(addGaussNoiseEffect()));
    connect(removeNoiseAction,SIGNAL(triggered(bool)),this,SLOT(returnOriginImage()));





}


void MainWindow::initWidget()
{
   twoValueWidget = new QWidget();

}

//打开图片
void MainWindow::OpenImage()
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
        Mat rgb;
        cv_img = cv::imread(filename.toLatin1().data());
        Mat origin = cv_img;
        now_mat = cv_img;
        if(cv_img.channels() == 3)
        {
           //cvtMatBGR2QImageRGB
           cvtColor(cv_img,rgb,CV_BGR2RGB);
           *img = cvMat2QImage(origin);
           //*img=QImage((const unsigned char*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
        }
        else
        {
            *img = cvMat2QImage(origin);

        }
        pre_mat = now_mat;
        imageItem = new QGraphicsPixmapItem();
        imageItem->setPixmap(QPixmap::fromImage(*img));
        scene->addItem(imageItem);
     }
}


//放大图片
void MainWindow::ImageInZoom()
{
    QPixmap *pix = new QPixmap(":/new/prefix1/image/large20.png");
    QCursor *my = new QCursor(*pix);
    setCursor(*my);
    imageShowWidget->setFocus();
    ButtonId = 1;
}


//缩小图片
void MainWindow::ImageReduce()
{
    QCursor *my = new QCursor(QPixmap(":/new/prefix1/image/small20.png"));
    setCursor(*my);
    imageShowWidget->setFocus();
    ButtonId = 2;
}

void MainWindow::SaveImage()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        if(! ( img->save(filename) ) ) //保存图像
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }
}


void MainWindow::goToLastStep()
{
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(pre_mat);
    *img = *new_Image;

    showImageView();
}

//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect *paintRegion =  new QRect(9,66,view->width()+9,66+view->height());
    qDebug()<<"view pos is x="<<view->x()<<"*****y="<<view->y();
    qDebug()<<"view size is x="<<view->width()<<"*****y="<<view->height();
    qDebug()<<"mouse pos is x="<<event->pos().x()<<"*****y="<<event->pos().y();
    switch(ButtonId)
    {
    case 1:

        if(paintRegion->contains(event->pos()))
        {
           view->scale(1.5, 1.5);
           view->centerOn(event->pos().x()-9,event->pos().y()-66);
           view->show();
           /*
           matrix.scale(1.41,1.41);
           *img = img->transformed(matrix);
           imageLabel->setPixmap(QPixmap::fromImage(*img));
           */
        }

        break;
    case 2:
        view->scale(0.71, 0.71);
        view->centerOn(event->pos());
        view->show();
        /*
        matrix.scale(0.71,0.71);
        *img = img->transformed(matrix);
        imageLabel->setPixmap(QPixmap::fromImage(*img));
        */
        break;
    default:
        if(event->button() == Qt::RightButton)
        {
            initMenu();
        }
        break;

    }

}


QImage MainWindow::GreyModeImage()
{
    pre_mat = now_mat;
    QImage *new_Image = new QImage();
    Mat origin = cv_img;
    if(cv_img.channels() == 3)
    {
       cvtColor(cv_img,now_mat,COLOR_BGR2GRAY);
       *new_Image = cvMat2QImage(now_mat);
    }
    else
    {
       *new_Image = cvMat2QImage(origin);
    }


    return *new_Image;
}

void MainWindow::ShowGreyImage()
{
    pre_mat = now_mat;
    QImage *newImage = new QImage();
    *newImage = GreyModeImage();
    *img = *newImage;
    scene->removeItem(imageItem);
    imageItem = new QGraphicsPixmapItem();
    imageItem->setPixmap(QPixmap::fromImage(*img));
    scene->addItem(imageItem);
    view->show();
}


void MainWindow::showHSVImage()
{
    pre_mat = now_mat;
    QImage *new_Image = new QImage();
    cvtColor(now_mat,now_mat,COLOR_BGR2HSV);
    *new_Image = cvMat2QImage(now_mat);
    *img = *new_Image;
    showImageView();
}

void MainWindow::showRGBImage()
{
    pre_mat = now_mat;
    QImage *new_Image = new QImage();
    cvtColor(now_mat,now_mat,COLOR_HSV2BGR);
    *new_Image = cvMat2QImage(now_mat);
    *img = *new_Image;

    showImageView();
}

void MainWindow::showTwoValuePreview()
{
    Mat mat = now_mat;
    Mat new_mat;
    QImage *new_Image = new QImage();
    int nY20_thresh = twoValueDialog->returnValue();
    qDebug()<<"preview value  is "<<nY20_thresh;
    threshold(mat, new_mat, nY20_thresh, 255, THRESH_BINARY);
    *new_Image = cvMat2QImage(new_mat);
    *img = *new_Image;
    showImageView();
}

void MainWindow::showTwoValueImage()
{
    pre_mat = now_mat;
    QImage *new_Image = new QImage();
    int nY20_thresh = twoValueDialog->returnValue();
    qDebug()<<"value  is "<<nY20_thresh;
    threshold(now_mat, now_mat, nY20_thresh, 255, THRESH_BINARY);
    *new_Image = cvMat2QImage(now_mat);
    *img = *new_Image;
    showImageView();
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta();
    if(numDegrees > 0)
    {
        view->scale(1.5, 1.5);
        view->centerOn(event->pos().x()-9,event->pos().y()-66);
        view->show();
    }
    if(numDegrees < 0)
    {
        view->scale(0.71, 0.71);
        view->centerOn(event->pos());
        view->show();
    }
}

void MainWindow::clearImage()
{
    scene->removeItem(imageItem);
    imageItem = new QGraphicsPixmapItem();
    view->show();
}

void MainWindow::initMenu()
{
    MouseRightClickMenu = new QMenu();
    clearImageAction = MouseRightClickMenu->addAction(tr("clear image"));
    backAction = MouseRightClickMenu->addAction(tr("last step"));
    initAction = MouseRightClickMenu->addAction(tr("init image"));
    connect(clearImageAction,SIGNAL(triggered(bool)),this,SLOT(clearImage()));
    connect(backAction,SIGNAL(triggered(bool)),this,SLOT(goToLastStep()));
    connect(initAction,SIGNAL(triggered(bool)),this,SLOT(returnOriginImage()));
}

//触发右键菜单事件
void MainWindow::contextMenuEvent(QContextMenuEvent *e)
{
    MouseRightClickMenu->exec(QCursor::pos());
}

//Mat转换为QImage
QImage MainWindow::cvMat2QImage(const cv::Mat& mat)
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


//QImage转换为Mat
cv::Mat MainWindow::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}
\

void MainWindow::showImageView()
{
    scene->removeItem(imageItem);
    imageItem = new QGraphicsPixmapItem();
    imageItem->setPixmap(QPixmap::fromImage(*img));
    scene->addItem(imageItem);
    view->show();
}

QImage MainWindow::ConvertToQImage(IplImage *iplImg)
{
QImage img;
int nChannel=iplImg->nChannels;
if(nChannel==3)
{
cvConvertImage(iplImg,iplImg,CV_CVTIMG_SWAP_RB);
img = QImage((const unsigned char*)iplImg->imageData,iplImg->width,iplImg->height,QImage::Format_RGB888);
}
else if(nChannel==4||nChannel==1)
{
img = QImage((const unsigned char*)iplImg->imageData,iplImg->width,iplImg->height,QImage::Format_ARGB32);
}
return img;
}

void MainWindow::OpenBrightAdjustWindow()
{
    brightDialog = new brightValueDialog(this);
   brightDialog->show();
   connect(brightDialog,SIGNAL(brightNoChanged()),this,SLOT(returnOriginImage()));
   connect(brightDialog,SIGNAL(brightPreview()),this,SLOT(ShowBrightAdjustEffect()));
   connect(brightDialog,SIGNAL(brightValueChanged()),this,SLOT(showBrightAdjustEffectOk()));
}


void MainWindow::showBrightAdjustEffectOk(){
    int brightness,contract;
    Mat outimg;
    outimg = Mat::zeros(cv_img.size(),cv_img.type());
    brightness = brightDialog->getBright();
    contract = brightDialog->getContract();
    for(int y=0;y<cv_img.rows;y++)
    {
        for(int x=0;x<cv_img.cols;x++)
        {
            for(int c=0;c<3;c++)
            {
                outimg.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((cv_img.at<Vec3b>(y,x)[c])*contract*0.01 +
                                            (2*brightness-255));
            }
        }
    }

    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outimg);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowBrightAdjustEffect(){
    int brightness,contract;
    Mat outimg;
    outimg = Mat::zeros(cv_img.size(),cv_img.type());
    brightness = brightDialog->getBright();
    contract = brightDialog->getContract();
    for(int y=0;y<cv_img.rows;y++)
    {
        for(int x=0;x<cv_img.cols;x++)
        {
            for(int c=0;c<3;c++)
            {
                outimg.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((cv_img.at<Vec3b>(y,x)[c])*contract*0.01 +
                                            (2*brightness-255));
            }
        }
    }

    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outimg);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowOilPainting()
{
    int brushSize = 2;
    int coarseness = 128;
    Mat outimg;
    outimg = Mat::zeros(cv_img.size(),cv_img.type());

    Mat gray;
    cvtColor(cv_img,gray,COLOR_BGR2GRAY);

    if (brushSize < 1)
        brushSize = 1;
    if (brushSize > 8)
        brushSize = 8;

    if (coarseness < 1)
        coarseness = 1;
    if (coarseness > 255)
        coarseness = 255;

     int width  = cv_img.cols;
     int height = cv_img.rows;

     int lenArray = coarseness + 1;
     int* CountIntensity = new int[lenArray];
     uint* RedAverage    = new uint[lenArray];
     uint* GreenAverage  = new uint[lenArray];
     uint* BlueAverage   = new uint[lenArray];


    for(int y=0;y<height;y++)
    {
        int top = y-brushSize;
        int bot = y+brushSize + 1;
        if(top<0)
            top=0;
        if(bot>=height)
            bot = height-1;
        for(int x=0;x<cv_img.cols;x++)
        {
           int left = x-brushSize;
           int right = x+brushSize + 1;
           if(left<0)
               left=0;
           if(right >= width)
               right = width-1;

           for(int i = 0;i <lenArray;i++)
                {
                 CountIntensity[i] = 0;
                 RedAverage[i] = 0;
                 GreenAverage[i] = 0;
                 BlueAverage[i] = 0;
                }
           for(int j = top;j<bot;j++)
               {
                for(int i = left;i<right;i++)
                {
                    uchar intensity = static_cast<uchar>(coarseness*gray.at<uchar>(j,i)/255.0);
                     CountIntensity[intensity]++;
                     RedAverage[intensity]  += cv_img.at<Vec3b>(j,i)[2];
                     GreenAverage[intensity]+= cv_img.at<Vec3b>(j,i)[1];
                     BlueAverage[intensity] += cv_img.at<Vec3b>(j,i)[0];
                }
               }
           uchar chosenIntensity = 0;
                      int maxInstance = CountIntensity[0];
                      for(int i=1;i<lenArray;i++)
                      {
                          if(CountIntensity[i]>maxInstance)
                          {
                              chosenIntensity = (uchar)i;
                              maxInstance = CountIntensity[i];
                          }
                      }

                      outimg.at<Vec3b>(y,x)[2] = static_cast<uchar>(RedAverage[chosenIntensity] / static_cast<float>(maxInstance));
                      outimg.at<Vec3b>(y,x)[1] = static_cast<uchar>(GreenAverage[chosenIntensity] /  static_cast<float>(maxInstance));
                      outimg.at<Vec3b>(y,x)[0] = static_cast<uchar>(BlueAverage[chosenIntensity] /  static_cast<float>(maxInstance));
                  }

        }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outimg);
    *img = *new_Image;
    showImageView();
}

void MainWindow::OpenTwoValueImageWindow()
{
    twoValueDialog->show();
}

void MainWindow::returnOriginImage()
{
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(now_mat);
    *img = *new_Image;
    showImageView();
}


void MainWindow::OpenImageMosaicWindow()
{
    imageMosaicWindow->show();
}




//雕刻效果
void MainWindow::ShowCarvingPainting()
{
    pre_mat = now_mat;
    Mat img0(now_mat.size(),CV_8UC3);
    Mat img1(now_mat.size(),CV_8UC3);
    for (int y=1; y<now_mat.rows-1; y++)
    {
       uchar *p0 = now_mat.ptr<uchar>(y);
       uchar *p1 = now_mat.ptr<uchar>(y+1);

       uchar *q0 = img0.ptr<uchar>(y);
       uchar *q1 = img1.ptr<uchar>(y);
       for (int x=1; x<now_mat.cols-1; x++)
       {
          for (int i=0; i<3; i++)
          {
              int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
              if (tmp0<0)
                 q0[3*x+i]=0;
              else if(tmp0>255)
                 q0[3*x+i]=255;
              else
                 q0[3*x+i]=tmp0;

              int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
                 if (tmp1<0)
                    q1[3*x+i]=0;
                 else if(tmp1>255)
                    q1[3*x+i]=255;
                 else
                    q1[3*x+i]=tmp1;
           }
        }
     }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(img1);
    *img = *new_Image;
    showImageView();
}

//浮雕效果
void MainWindow::ShowReliefPainting()
{
    pre_mat = now_mat;
    Mat img0(now_mat.size(),CV_8UC3);
    Mat img1(now_mat.size(),CV_8UC3);
    for (int y=1; y<now_mat.rows-1; y++)
    {
       uchar *p0 = now_mat.ptr<uchar>(y);
       uchar *p1 = now_mat.ptr<uchar>(y+1);

       uchar *q0 = img0.ptr<uchar>(y);
       uchar *q1 = img1.ptr<uchar>(y);
       for (int x=1; x<now_mat.cols-1; x++)
       {
          for (int i=0; i<3; i++)
          {
              int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
              if (tmp0<0)
                 q0[3*x+i]=0;
              else if(tmp0>255)
                 q0[3*x+i]=255;
              else
                 q0[3*x+i]=tmp0;

              int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
                 if (tmp1<0)
                    q1[3*x+i]=0;
                 else if(tmp1>255)
                    q1[3*x+i]=255;
                 else
                    q1[3*x+i]=tmp1;
           }
        }
     }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(img0);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform1()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[0]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform2()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[1]);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowColorTransform3()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[2]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform4()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[3]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform5()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[4]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform6()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[5]);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowColorTransform7()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[6]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform8()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[7]);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowColorTransform9()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[8]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform10()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[9]);
    *img = *new_Image;
    showImageView();
}

void MainWindow::ShowColorTransform11()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[10]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowColorTransform12()
{
    pre_mat = now_mat;
    int width = now_mat.cols;
    int heigh = now_mat.rows;
    Mat gray;
    Mat imgColor[12];
    Mat display(heigh*3,width*4,CV_8UC3);

    cvtColor(now_mat,gray,CV_BGR2GRAY);
    for(int i=0; i<12; i++)
    {
      applyColorMap(gray,imgColor[i],i);
      int x=i%4;
      int y=i/4;
      Mat displayROI = display(Rect(x*width,y*heigh,width,heigh));
      cv::resize(imgColor[i],displayROI,displayROI.size());
    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(imgColor[11]);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowWindowEffectPreview()
{
    //int num=10;//   num：风线密度
    //int num1=20;//  num1：风线长度
    int num = windDialog->returnValue1();
    int num1 = windDialog->returnValue2();
    qDebug()<<"value is "<<num;
    Mat *new_mat = new Mat;
    *new_mat = now_mat;
    Mat src = *new_mat;
    Mat src1u[3];
    split(src,src1u);

    int width=src.cols;
    int heigh=src.rows;
    Mat img1;
    src.copyTo(img1);

    Point center(width/2,heigh/2);

    RNG rng;

    for (int y=0; y<heigh; y++)
    {

       uchar *imgP  = img1.ptr<uchar>(y);

       for (int i=0;i<num;i++)      //  num：风线密度
       {
           int newX=rng.uniform(i*width/num,(i+1)*width/num);
           int newY = y;

           if(newX<0)newX=0;
           if(newX>width-1)newX=width-1;

           uchar tmp0 = src1u[0].at<uchar>(newY,newX);
           uchar tmp1 = src1u[1].at<uchar>(newY,newX);
           uchar tmp2 = src1u[2].at<uchar>(newY,newX);

           for (int j=0; j<num1; j++)   //num1：风线长度
           {
               int tmpX=newX-j;//减：风向左；加：风向右

               if(tmpX<0)tmpX=0;
               if(tmpX>width-1)tmpX=width-1;

               imgP[tmpX*3]=tmp0;
               imgP[tmpX*3+1]=tmp1;
               imgP[tmpX*3+2]=tmp2;
           }
       }

    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(img1);
    *img = *new_Image;
    showImageView();
}


void MainWindow::ShowWindowEffect()
{
    //int num=10;//   num：风线密度
    //int num1=20;//  num1：风线长度
    int num = windDialog->returnValue1();
    int num1 = windDialog->returnValue2();
    qDebug()<<"value is "<<num;
    Mat src = now_mat;
    Mat src1u[3];
    split(src,src1u);

    int width=src.cols;
    int heigh=src.rows;
    Mat img1;
    src.copyTo(img1);

    Point center(width/2,heigh/2);

    RNG rng;

    for (int y=0; y<heigh; y++)
    {

       uchar *imgP  = img1.ptr<uchar>(y);

       for (int i=0;i<num;i++)      //  num：风线密度
       {
           int newX=rng.uniform(i*width/num,(i+1)*width/num);
           int newY = y;

           if(newX<0)newX=0;
           if(newX>width-1)newX=width-1;

           uchar tmp0 = src1u[0].at<uchar>(newY,newX);
           uchar tmp1 = src1u[1].at<uchar>(newY,newX);
           uchar tmp2 = src1u[2].at<uchar>(newY,newX);

           for (int j=0; j<num1; j++)   //num1：风线长度
           {
               int tmpX=newX-j;//减：风向左；加：风向右

               if(tmpX<0)tmpX=0;
               if(tmpX>width-1)tmpX=width-1;

               imgP[tmpX*3]=tmp0;
               imgP[tmpX*3+1]=tmp1;
               imgP[tmpX*3+2]=tmp2;
           }
       }

    }
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(img1);
    *img = *new_Image;
    showImageView();

}



void MainWindow::OpenWindEffectWindow()
{
    windDialog->show();
}


void MainWindow::OpenBlurWindow()
{
    blurDialog->show();
}

//双边模糊
void MainWindow::ShowBilateralBlurEffect()
{
    int value = bilateralBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    QImage *new_Image1 = new QImage();
    *new_Image1 = cvMat2QImage(now_mat);
    img_src = QImageToIplImage(new_Image1);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_BILATERAL,3,3,11,11);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}


//高斯模糊
void MainWindow::ShowGaussianBlurEffect()
{
    int value = gaussianBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    QImage *new_Image1 = new QImage();
    *new_Image1 = cvMat2QImage(now_mat);
    img_src = QImageToIplImage(new_Image1);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_GAUSSIAN,value,value,0,0);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}

//中值模糊
void MainWindow::ShowMedianBlurEffect()
{
    int value = medianBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    QImage *new_Image1 = new QImage();
    *new_Image1 = cvMat2QImage(now_mat);
    img_src = QImageToIplImage(new_Image1);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_MEDIAN,value,value,0,0);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}


//简单模糊
void MainWindow::ShowSimpleBlurEffect()
{
    int value = blurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    QImage *new_Image1 = new QImage();
    *new_Image1 = cvMat2QImage(now_mat);
    img_src = QImageToIplImage(new_Image1);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_BLUR,value,value,0,0);
    Mat outMat;
    //outMat = Mat(out_mat->rows,out_mat->cols,out_mat->type,out_mat->data.fl);
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}


QImage* MainWindow::IplImageToQImage(const IplImage *img1)
{
    QImage *qmg;
    if(img1->nChannels == 1)
    {
        IplImage *img_gray = cvCreateImage(cvGetSize(img1),8,1);
        cvCvtColor(img1,img_gray,CV_BGR2GRAY);
        qmg = new QImage((unsigned char*)img1->imageData,img1->width,img1->height,img1->widthStep,QImage::Format_Indexed8);
        return qmg;
    }
    else if(img1->nChannels == 3)
    {
        IplImage *img2 = cvCreateImage(cvGetSize(img1),8,1);
        cvCvtColor(img1,img2,CV_BGR2RGB);
        qmg = new QImage((unsigned char*)img2->imageData,img2->width,img2->height,img2->widthStep,QImage::Format_RGB888);
        return qmg;
    }
    else
    {
        qDebug() << "ERROR: IPLIMAGE could not be converted to QImage.";
        return new QImage();
    }
}


IplImage* MainWindow::QImageToIplImage(const QImage *qImage)
{
    int width = qImage->width();
    int height = qImage->height();
    CvSize Size;
    Size.height = height;
    Size.width = width;
    IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
    for (int y = 0; y < height; ++y)
    {
       for (int x = 0; x < width; ++x)
       {
           QRgb rgb = qImage->pixel(x, y);
           CV_IMAGE_ELEM( IplImageBuffer, uchar, y, x*3+0 ) = qBlue(rgb);
           CV_IMAGE_ELEM( IplImageBuffer, uchar, y, x*3+1 ) = qGreen(rgb);
           CV_IMAGE_ELEM( IplImageBuffer, uchar, y, x*3+2 ) = qRed(rgb);
       }
     }
     return IplImageBuffer;
}

void MainWindow::OpenBilateralBlurWindow()
{
    bilateralBlurDialog->show();
}

void MainWindow::OpenMedianBlurWindow()
{
    medianBlurDialog->show();
}

void MainWindow::OpenGaussianBlurWindow()
{
    gaussianBlurDialog->show();
}

//双边模糊
void MainWindow::ShowBilateralBlurEffectOk()
{
    int value = bilateralBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    img_src = QImageToIplImage(img);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_BILATERAL,3,3,11,11);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}


//高斯模糊
void MainWindow::ShowGaussianBlurEffectOk()
{
    int value = gaussianBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    img_src = QImageToIplImage(img);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_GAUSSIAN,value,value,0,0);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}

//中值模糊
void MainWindow::ShowMedianBlurEffectOk()
{
    int value = medianBlurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    img_src = QImageToIplImage(img);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_MEDIAN,value,value,0,0);
    Mat outMat;
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}


//简单模糊
void MainWindow::ShowSimpleBlurEffectOk()
{
    int value = blurDialog->returnValue();
    IplImage* img_src = 0;
    IplImage* img_dst = 0;
    img_src = QImageToIplImage(img);
    img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);
    cvSmooth(img_src,img_dst,CV_BLUR,value,value,0,0);
    Mat outMat;
    //outMat = Mat(out_mat->rows,out_mat->cols,out_mat->type,out_mat->data.fl);
    outMat = cv::cvarrToMat(img_dst,true);
    QImage *new_Image = new QImage();
    *new_Image = cvMat2QImage(outMat);
    *img = *new_Image;
    showImageView();
}

void MainWindow::oldphoto(){
    Mat outimg;
    outimg = Mat(cv_img.size(),CV_8UC3);
    for(int y=0;y<cv_img.rows;y++)
    {
        uchar *P0 = cv_img.ptr<uchar>(y);
        uchar *P1 = outimg.ptr<uchar>(y);
        for(int x=0;x<cv_img.cols;x++)
        {
            float B=P0[3*x];
                        float G=P0[3*x+1];
                        float R=P0[3*x+2];
                        float newB=0.272*R+0.534*G+0.131*B;
                        float newG=0.349*R+0.686*G+0.168*B;
                        float newR=0.393*R+0.769*G+0.189*B;
                        if(newB<0)newB=0;
                        if(newB>255)newB=255;
                        if(newG<0)newG=0;
                        if(newG>255)newG=255;
                        if(newR<0)newR=0;
                        if(newR>255)newR=255;
                        P1[3*x] = (uchar)newB;
                        P1[3*x+1] = (uchar)newG;
                        P1[3*x+2] = (uchar)newR;
        }
    }
    QImage *new_Img = new QImage();
    *new_Img = cvMat2QImage(outimg);
    *img = *new_Img;
    showImageView();
}

void MainWindow::hotphoto(){
     Mat outimg;
   outimg = Mat(cv_img.size(),CV_8UC3);
        int width=cv_img.cols;
        int heigh=cv_img.rows;
        for (int y=0;y<heigh;y++)
        {
            uchar* imgP=cv_img.ptr<uchar>(y);
            uchar* dstP=outimg.ptr<uchar>(y);
            for (int x=0;x<width;x++)
            {
                float b0=imgP[3*x];
                float g0=imgP[3*x+1];
                float r0=imgP[3*x+2];

                float b = b0*255/(g0+r0+1);
                float g = g0*255/(b0+r0+1);
                float r = r0*255/(g0+b0+1);

                r = (r>255 ? 255 : (r<0? 0 : r));
                g = (g>255 ? 255 : (g<0? 0 : g));
                b = (b>255 ? 255 : (b<0? 0 : b));

                dstP[3*x] = (uchar)b;
                dstP[3*x+1] = (uchar)g;
                dstP[3*x+2] = (uchar)r;
            }
        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(outimg);
        *img = *new_Img;
        showImageView();
}

void MainWindow::coldphoto(){
    Mat outimg;
    outimg = Mat(cv_img.size(),CV_8UC3);
        int width=cv_img.cols;
        int heigh=cv_img.rows;
        for (int y=0;y<heigh;y++)
        {
            uchar* imgP=cv_img.ptr<uchar>(y);
            uchar* dstP=outimg.ptr<uchar>(y);
            for (int x=0;x<width;x++)
            {
                float b0=imgP[3*x];
                float g0=imgP[3*x+1];
                float r0=imgP[3*x+2];

                float b = (b0-g0-r0)*3/2;
                float g = (g0-b0-r0)*3/2;
                float r = (r0-g0-b0)*3/2;

                r = (r>255 ? 255 : (r<0? -r : r));
                g = (g>255 ? 255 : (g<0? -g : g));
                b = (b>255 ? 255 : (b<0? -b : b));
                dstP[3*x] = (uchar)b;
                dstP[3*x+1] = (uchar)g;
                dstP[3*x+2] = (uchar)r;
            }
        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(outimg);
        *img = *new_Img;
        showImageView();
}

void MainWindow::sumiao(){
    Mat gray0,gray1;
        //去色
        cvtColor(cv_img,gray0,CV_BGR2GRAY);
        //反色
        addWeighted(gray0,-1,NULL,0,255,gray1);
        //高斯模糊,高斯核的Size与最后的效果有关
        GaussianBlur(gray1,gray1,Size(11,11),0);

        //融合：颜色减淡
        Mat outimg;
       outimg = Mat(cv_img.size(),CV_8UC1);
        for (int y=0; y<cv_img.rows; y++)
        {

            uchar* P0  = gray0.ptr<uchar>(y);
            uchar* P1  = gray1.ptr<uchar>(y);
            uchar* P  = outimg.ptr<uchar>(y);
            for (int x=0; x<cv_img.cols; x++)
            {
                int tmp0=P0[x];
                int tmp1=P1[x];
                P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
            }

        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(outimg);
        *img = *new_Img;
        showImageView();
}

void MainWindow::whiteAve(){
    vector<Mat> imageRGB;
    Mat outimg1;
     cv_img.copyTo(outimg1);
        //RGB三通道分离
        split(outimg1, imageRGB);

        //求原始图像的RGB分量的均值
        double R, G, B;
        B = mean(imageRGB[0])[0];
        G = mean(imageRGB[1])[0];
        R = mean(imageRGB[2])[0];

        //需要调整的RGB分量的增益
        double KR, KG, KB;
        KB = (R + G + B) / (3 * B);
        KG = (R + G + B) / (3 * G);
        KR = (R + G + B) / (3 * R);

        //调整RGB三个通道各自的值
        imageRGB[0] = imageRGB[0] * KB;
        imageRGB[1] = imageRGB[1] * KG;
        imageRGB[2] = imageRGB[2] * KR;

        //RGB三通道图像合并
        merge(imageRGB, outimg1);
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(outimg1);
        *img = *new_Img;
        showImageView();
}

void MainWindow::light(){
    int a=256,b=312,m=100,n=17;
    Mat outimg;
    for(int j=0;j<cv_img.rows;j++)
    {
        const uchar*current=cv_img.ptr<const uchar>(j);//当前行
                uchar *output=outimg.ptr<uchar>(j);
                for(int i=0;i<cv_img.cols;++i)
                {
                    for (int ch=0;ch<3;++ch)
                    {
                    uchar tmp;
                    if(sqrt((j-a)*(j-a)+(i-b)*(i-b))-b<0)
                    tmp=saturate_cast<uchar>(current[3*i+ch]+m*(1-(sqrt((j-a)*(j-a)+(i-b)*(i-b))+n)/b));
                    else  tmp=current[3*i+ch];
                    output[3*i+ch]=tmp;
                    }
                }
    }
    QImage *new_Img = new QImage();
    *new_Img = cvMat2QImage(outimg);
    *img = *new_Img;
    showImageView();

}

double generateGaussianNoise(double mu, double sigma)
{
    //定义小值
    const double epsilon = numeric_limits<double>::min();
    static double z0, z1;
    static bool flag = false;
    flag = !flag;
    //flag为假构造高斯随机变量X
    if (!flag)
        return z1 * sigma + mu;
    double u1, u2;
    //构造随机变量
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    } while (u1 <= epsilon);
    //flag为真构造高斯随机变量
    z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
    z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
    return z0*sigma + mu;
}

void MainWindow::addGaussNoiseEffect(){
    Mat dstImage = cv_img.clone();
        int channels = dstImage.channels();
        int rowsNumber = dstImage.rows;
        int colsNumber = dstImage.cols*channels;
        //判断图像的连续性
        if (dstImage.isContinuous())
        {
            colsNumber *= rowsNumber;
            rowsNumber = 1;
        }
        for (int i = 0; i < rowsNumber; i++)
        {
            for (int j = 0; j < colsNumber; j++)
            {
                //添加高斯噪声
                int val = dstImage.ptr<uchar>(i)[j] +
                    generateGaussianNoise(2, 0.8) * 32;
                if (val < 0)
                    val = 0;
                if (val>255)
                    val = 255;
                dstImage.ptr<uchar>(i)[j] = (uchar)val;
            }
        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(dstImage);
        *img = *new_Img;
        showImageView();
}

void MainWindow::addPepperNoiseEffect(){
    int n = 3000;
    Mat dstImage = cv_img.clone();
        for (int k = 0; k < n; k++)
        {
            //随机取值行列
            int i = rand() % dstImage.rows;
            int j = rand() % dstImage.cols;
            //图像通道判定
            if (dstImage.channels() == 1)
            {
                dstImage.at<uchar>(i, j) = 0;       //盐噪声
            }
            else
            {
                dstImage.at<Vec3b>(i, j)[0] = 0;
                dstImage.at<Vec3b>(i, j)[1] = 0;
                dstImage.at<Vec3b>(i, j)[2] = 0;
            }
        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(dstImage);
        *img = *new_Img;
        showImageView();
}

void MainWindow::addSaltNoiseEffect(){
    int n = 3000;
    Mat dstImage = cv_img.clone();
        for (int k = 0; k < n; k++)
        {
            //随机取值行列
            int i = rand() % dstImage.rows;
            int j = rand() % dstImage.cols;
            //图像通道判定
            if (dstImage.channels() == 1)
            {
                dstImage.at<uchar>(i, j) = 255;       //盐噪声
            }
            else
            {
                dstImage.at<Vec3b>(i, j)[0] = 255;
                dstImage.at<Vec3b>(i, j)[1] = 255;
                dstImage.at<Vec3b>(i, j)[2] = 255;
            }
        }
        QImage *new_Img = new QImage();
        *new_Img = cvMat2QImage(dstImage);
        *img = *new_Img;
        showImageView();
}

void MainWindow::openHSBDialog(){
    hsbDialog = new HSBDialog(this);
    connect(hsbDialog,SIGNAL(ValueNoChanged()),this,SLOT(returnOriginImage()));
    connect(hsbDialog,SIGNAL(ValueChanged()),this,SLOT(showHSBResult()));
    connect(hsbDialog,SIGNAL(Preview()),this,SLOT(showHSBPreview()));
    hsbDialog->show();
}

void MainWindow::showHSBPreview(){
    Mat dst;
    int hue = hsbDialog->getH();
    int saturation = hsbDialog->getS();
    int brightness = hsbDialog->getB();
    hsl.channels[0].hue = hue -180;
    hsl.channels[0].saturation = saturation - 100;
    hsl.channels[0].brightness = brightness -100;
    hsl.adjust(cv_img,dst);
    QImage *new_Img = new QImage();
    *new_Img = cvMat2QImage(dst);
    *img = *new_Img;
    showImageView();
}

void MainWindow::showHSBResult(){
    Mat dst;
    int hue = hsbDialog->getH();
    int saturation = hsbDialog->getS();
    int brightness = hsbDialog->getB();
    hsl.channels[0].hue = hue -180;
    hsl.channels[0].saturation = saturation - 100;
    hsl.channels[0].brightness = brightness -100;
    hsl.adjust(cv_img,dst);
    QImage *new_Img = new QImage();
    *new_Img = cvMat2QImage(dst);
    *img = *new_Img;
    showImageView();
}
