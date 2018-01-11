#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QtGui>
#include <QTextCodec>
#include <QCursor>
#include <QMatrix>
#include <QPoint>
#include <QMouseEvent>
#include <QRect>
#include <QDebug>
#include <QLabel>
#include <QMatrix>
#include <QRgb>
#include <QWheelEvent>
#include <QGraphicsPixmapItem>
#include<opencv2/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv/cv.hpp>
#include<opencv2/opencv.hpp>
#include <QContextMenuEvent>
#include <QTextCodec>
#include <QStackedWidget>
#include <QLabel>
#include "twovaluedialog.h"
#include "imagemosaic.h"
#include "winddialog.h"
#include "blurdialog.h"
#include "gaussianblurdialog.h"
#include "bilateralblurdialog.h"
#include "medianblurdialog.h"
#include<brightvaluedialog.h>
#include<vector>
#include<HSL.hpp>
#include<hsbdialog.h>

using namespace cv;
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initMenu();
    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(QImage image);
    QImage ConvertToQImage(IplImage *iplImg);
    HSL hsl;
    void showImageView();
    void initWidget();
    QImage *IplImageToQImage(const IplImage *img1);//IplImage类型转QImage
    IplImage *QImageToIplImage(const QImage * qImage);

private:
    Ui::MainWindow *ui;
    QMenu *FileMenu;
    QMenu *ImageMenu;
    QMenu *ImageModeMenu;
    QMenu *ImageAdjustMenu;
    QMatrix matrix;
    QGraphicsPixmapItem *imageItem;

    //图像菜单action
    QAction *GreyImageAction;
    QAction *RGBImageAction;
    QAction *HSVImageAction;
    QAction *TwoValueAction;
    QAction *BrightAction;
    QAction *HSBAction;

    //文件菜单action
    QAction *OpenFileAction;
    QAction *SaveFileAction;
    QAction *QuitAction;
    QAction *EnlargeAction;
    QAction *ShrinkAction;

    QWidget *imageShowWidget;
    QVBoxLayout *mainLayout;
    QImage *img;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPoint *mousePos;

    //右键菜单
    QAction *clearImageAction;
    QMenu *MouseRightClickMenu;
    QAction *backAction;
    QAction *initAction;

    //图像处理菜单
    QMenu *ImageProcess;
    QAction *ImageMosaic;

    //滤镜菜单
    QMenu *FilterMenu;
    QAction *OilPaintingAction;
    QAction *ReliefAction;
    QAction *CarvingAction;

    QMenu *ColorTransformationMenu;
    QAction *color1;
    QAction *color2;
    QAction *color3;
    QAction *color4;
    QAction *color5;
    QAction *color6;
    QAction *color7;
    QAction *color8;
    QAction *color9;
    QAction *color10;
    QAction *color11;
    QAction *color12;
    QAction *windAction;
    QAction *oldcolor;
    QAction *lightColor;
    QAction *hot;
    QAction *cold;
    QAction *suMiao;
    QAction *whiteAverage;


    QMenu *blurMenu;
    QAction *blurAction;
    QAction *GaussianAction;
    QAction *MedianAction;
    QAction *BilateralAction;


    //噪声菜单
    QMenu *noiseMenu;
    QAction *addGaussianNoiseAction;
    QAction *addSaltNoiseAction;
    QAction *addPepperNoiseAction;
    QAction *removeNoiseAction;

    QStackedWidget *functionStack;

    QWidget *twoValueWidget;
    QLabel *value_label;

    Mat cv_img; //原图
    Mat now_mat;//当前图像结果
    Mat pre_mat;//上一步结果

    QLabel *imageLabel;
    int ButtonId = -1;
    const int EnlargeBtn = 0;
    const int ShrinkBtn = 1;

    TwoValueDialog *twoValueDialog;
    imageMosaic *imageMosaicWindow;
    WindDialog *windDialog;
    BlurDialog *blurDialog;
    GaussianBlurDialog *gaussianBlurDialog;
    MedianBlurDialog *medianBlurDialog;
    BilateralBlurDialog *bilateralBlurDialog;
    brightValueDialog *brightDialog;
    HSBDialog *hsbDialog;


    void MenuCreate();//创建导航菜单
    QImage GreyModeImage();//改为灰度图像
    void DisplayImage();//显示图片


protected:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);


private slots:
    void OpenImage();//打开图片
    void ImageInZoom();//图片放大
    void ImageReduce();//图片缩小
    void SaveImage();//保存图片
    void ShowGreyImage();//显示灰度图
    void clearImage();//清除图像
    void goToLastStep();//返回上一步
    void showHSVImage();//显示HSV图像
    void showRGBImage();//显示RGB图像
    void showTwoValueImage();//显示二值图像
    void showTwoValuePreview();//二值图像预览
    void OpenBrightAdjustWindow();//打开亮度调节窗
    void OpenTwoValueImageWindow();//打开二值化图片调节框
    void returnOriginImage();//取消图片变化
    void OpenImageMosaicWindow();//打开图像拼合窗口
    void ShowOilPainting();//油画滤镜
    void ShowReliefPainting();//浮雕滤镜
    void ShowCarvingPainting();//雕刻滤镜
    void ShowColorTransform1();//颜色变换
    void ShowColorTransform2();//颜色变换
    void ShowColorTransform3();//颜色变换
    void ShowColorTransform4();//颜色变换
    void ShowColorTransform5();//颜色变换
    void ShowColorTransform6();//颜色变换
    void ShowColorTransform7();//颜色变换
    void ShowColorTransform8();//颜色变换
    void ShowColorTransform9();//颜色变换
    void ShowColorTransform10();//颜色变换
    void ShowColorTransform11();//颜色变换
    void ShowColorTransform12();//颜色变换
    void ShowWindowEffect();//滤镜风效果
    void ShowWindowEffectPreview();//滤镜风效果预览
    void OpenWindEffectWindow();//打开风效果滤镜窗口
    void OpenBlurWindow();//打开模糊滤镜窗口
    void OpenGaussianBlurWindow();//高斯模糊窗口
    void OpenMedianBlurWindow();//中值模糊窗口
    void OpenBilateralBlurWindow();//双边模糊窗口
    void ShowSimpleBlurEffect();//简单模糊预览
    void ShowGaussianBlurEffect();//高斯模糊预览
    void ShowMedianBlurEffect();//中值模糊预览
    void ShowBilateralBlurEffect();//双边模糊预览
    void ShowSimpleBlurEffectOk();//简单模糊预览
    void ShowGaussianBlurEffectOk();//高斯模糊
    void ShowMedianBlurEffectOk();//中值模糊
    void ShowBilateralBlurEffectOk();//双边模糊
    void ShowBrightAdjustEffect();//亮度对比度
    void showBrightAdjustEffectOk();//
    void addSaltNoiseEffect();//盐噪声
    void addPepperNoiseEffect();//椒噪声
    void addGaussNoiseEffect();//高斯噪声

    void oldphoto();//怀旧滤镜
    void hotphoto();//炽热
    void coldphoto();//冰冻

    void light();//灯光
    void sumiao();//素描
    void whiteAve();//自动白平衡

    void openHSBDialog();
    void showHSBPreview();
    void showHSBResult();



signals:



};

#endif // MAINWINDOW_H
