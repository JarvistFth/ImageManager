#include "brightvaluedialog.h"
#include "ui_brightvaluedialog.h"

brightValueDialog::brightValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::brightValueDialog)
{
    ui->setupUi(this);

    brightBox = ui->spinBox;
    brightLabel = ui->label;
    brightSlider = ui->horizontalSlider;
    brightBox->setMaximum(255);
    brightBox->setMinimum(0);
    brightSlider->setMaximum(255);
    brightSlider->setMinimum(0);
    brightSlider->setValue(80);
    brightBox->setValue(80);
    contractBox = ui->spinBox_2;
    contractlabel = ui->label_2;
    contractSlider = ui->horizontalSlider_2;
    contractBox->setMaximum(400);
    contractBox->setMinimum(0);
    contractSlider->setMaximum(400);
    contractSlider->setMinimum(0);
    contractSlider->setValue(80);
    contractBox->setValue(80);
    connect(contractBox,SIGNAL(valueChanged(int)),contractSlider,SLOT(setValue(int)));
    connect(contractSlider,SIGNAL(valueChanged(int)),contractBox,SLOT(setValue(int)));
    //connect(contractBox,SIGNAL(valueChanged(int)),this,SLOT())
    connect(brightBox,SIGNAL(valueChanged(int)),brightSlider,SLOT(setValue(int)));
    connect(brightSlider,SIGNAL(valueChanged(int)),brightBox,SLOT(setValue(int)));
    connect(brightSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangeNow()));
    connect(contractSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangeNow()));


}

brightValueDialog::~brightValueDialog()
{
    delete ui;
}

void brightValueDialog::valueChangeNow(){
    emit brightPreview();
}


int brightValueDialog::getBright()
{
    return brightSlider->value();
}

int brightValueDialog::getContract()
{
    return contractSlider->value();
}



void brightValueDialog::on_pushButton_clicked()
{
    emit brightValueChanged();
    this->close();
}


void brightValueDialog::on_pushButton_2_clicked()
{
    emit brightNoChanged();
    this->close();
}
