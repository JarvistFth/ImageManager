#include "paintdialog.h"
#include "ui_paintdialog.h"

paintDialog::paintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paintDialog)
{
    ui->setupUi(this);
    label1 = ui->label;
    label2 = ui->label_2;
    box1=ui->spinBox;
    box2=ui->spinBox_2;
    slider1=ui->horizontalSlider;
    slider2=ui->horizontalSlider_2;
    box1->setMaximum(8);
    box1->setMinimum(1);
    slider1->setMaximum(8);
    slider1->setMinimum(1);
    box2->setMaximum(255);
    box2->setMinimum(0);
    slider2->setMaximum(255);
    slider2->setMinimum(0);
    connect(box1,SIGNAL(valueChanged(int)),slider1,SLOT(setValue(int)));
    connect(slider1,SIGNAL(valueChanged(int)),box1,SLOT(setValue(int)));


    connect(box2,SIGNAL(valueChanged(int)),slider2,SLOT(setValue(int)));
    connect(slider2,SIGNAL(valueChanged(int)),box2,SLOT(setValue(int)));

}

paintDialog::~paintDialog()
{
    delete ui;
}


int paintDialog::getBrushSize()
{
    return slider1->value();
}

int paintDialog::getCoarseness()
{
    return slider2->value();
}
void paintDialog::on_spinBox_valueChanged(int arg1)
{
    emit senddata();
}

void paintDialog::on_horizontalSlider_valueChanged(int value)
{
    emit senddata();

}

void paintDialog::on_spinBox_2_valueChanged(int arg1)
{
    emit senddata();

}

void paintDialog::on_horizontalSlider_2_valueChanged(int value)
{
    emit senddata();
}
