#ifndef IMAGEMOSAIC_H
#define IMAGEMOSAIC_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>
#include<opencv2/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv/cv.hpp>
#include<opencv2/opencv.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>






using namespace cv;

namespace Ui {
class imageMosaic;
}

class imageMosaic : public QMainWindow
{
    Q_OBJECT

public:
    explicit imageMosaic(QWidget *parent = 0);
    ~imageMosaic();
    QImage cvMat2QImage(const cv::Mat& mat);
    void imageMosaicStart();


private:
    Ui::imageMosaic *ui;
    QWidget *centerWidget;
    QLabel *picture1;
    QLabel *picture2;
    QHBoxLayout *widgetLayout;
    QAction *openFileAction;
    QMenu *Menu;


    Mat img1;
    Mat img2;

    QImage *image1;
    QImage *image2;

    int count = 0;//记录当前已导入的图片数量

private slots:
     void OpenFile();
};

#endif // IMAGEMOSAIC_H
