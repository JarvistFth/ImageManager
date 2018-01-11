#include "brightdialog.h"
#include "ui_brightdialog.h"
#include<opencv2/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv/cv.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    brightBox = ui->spinBox;
    brightLabel = ui->label;
    brightSlider = ui->horizontalSlider;
    brightBox->setMaximum(255);
    brightBox->setMinimum(0);
    brightSlider->setMaximum(255);
    brightSlider->setMinimum(0);
    connect(brightBox,SIGNAL(valueChanged(int)),brightSlider,SLOT(setValue(int)));
    connect(brightSlider,SIGNAL(valueChanged(int)),brightBox,SLOT(setValue(int)));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    int brightness;
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        brightness = brightSlider->value();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {

    }
}
