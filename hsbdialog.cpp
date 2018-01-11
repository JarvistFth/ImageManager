#include "hsbdialog.h"
#include "ui_hsbdialog.h"

HSBDialog::HSBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HSBDialog)
{
    ui->setupUi(this);
    sl1 = ui->horizontalSlider;
    sl2 = ui->horizontalSlider_2;
    sl3 = ui->horizontalSlider_3;
    sb1 = ui->spinBox;
    sb2 = ui->spinBox_2;
    sb3 = ui->spinBox_3;
    ok = ui->pushButton;
    cancel = ui->pushButton_2;
    sl1->setMaximum(360);
    sl1->setMinimum(0);
    sl2->setMaximum(200);
    sl2->setMinimum(0);
    sl3->setMaximum(200);
    sl3->setMinimum(0);
    sb1->setMaximum(360);
    sb1->setMinimum(0);
    sb2->setMaximum(200);
    sb2->setMinimum(0);
    sb3->setMaximum(200);
    sb3->setMinimum(0);
    sl1->setValue(0);
    sl2->setValue(0);
    sl3->setValue(0);
    sb1->setValue(0);
    sb2->setValue(0);
    sb3->setValue(0);
    connect(sl1,SIGNAL(valueChanged(int)),sb1,SLOT(setValue(int)));
    connect(sb1,SIGNAL(valueChanged(int)),sl1,SLOT(setValue(int)));
    connect(sl2,SIGNAL(valueChanged(int)),sb2,SLOT(setValue(int)));
    connect(sb2,SIGNAL(valueChanged(int)),sl2,SLOT(setValue(int)));
    connect(sl3,SIGNAL(valueChanged(int)),sb3,SLOT(setValue(int)));
    connect(sb3,SIGNAL(valueChanged(int)),sl3,SLOT(setValue(int)));
    connect(sl1,SIGNAL(valueChanged(int)),sb1,SLOT(setValue(int)));
    connect(sl1,SIGNAL(valueChanged(int)),this,SLOT(ValueChangedNow()));
    connect(sl2,SIGNAL(valueChanged(int)),this,SLOT(ValueChangedNow()));
    connect(sl3,SIGNAL(valueChanged(int)),this,SLOT(ValueChangedNow()));
}

HSBDialog::~HSBDialog()
{
    delete ui;
}

void HSBDialog::on_pushButton_clicked()
{
    emit ValueChanged();
    this->close();
}

void HSBDialog::on_pushButton_2_clicked()
{
    emit ValueNoChanged();
    this->close();
}

void HSBDialog::ValueChangedNow(){
    emit Preview();
}

int HSBDialog::getB(){
    return sl3->value();
}

int HSBDialog::getH(){
    return sl1->value();
}

int HSBDialog::getS(){
    return sl2->value();
}
