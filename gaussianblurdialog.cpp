#include "gaussianblurdialog.h"
#include "ui_gaussianblurdialog.h"

GaussianBlurDialog::GaussianBlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianBlurDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Gaussian Blur");
    okButton = new QPushButton();
    okButton = ui->okButton;
    cancelButton = new QPushButton();
    cancelButton = ui->cancelButton;
    valueBox = new QSpinBox();
    valueBox = ui->BlurBox;
    valueSlider = new QSlider();
    valueSlider = ui->BlurSlider;
    valueBox->setValue(0);
    valueSlider->setValue(0);
    valueBox->setMaximum(49);
    valueBox->setMinimum(1);
    valueSlider->setMaximum(49);
    valueSlider->setMinimum(1);
    valueSlider->setSingleStep(2);


    connect(valueBox,SIGNAL(valueChanged(int)),valueSlider,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),valueBox,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangedNow()));
}

GaussianBlurDialog::~GaussianBlurDialog()
{
    delete ui;
}

int GaussianBlurDialog::returnValue()
{
    return valueSlider->value();
}


void GaussianBlurDialog::valueChangedNow()
{
    if(valueSlider->value() % 2 == 1)
       emit GaussianBlurPreview();
}

void GaussianBlurDialog::on_okButton_clicked()
{
    if(valueSlider->value() % 2 == 1)
    {
        emit GaussianBlurValueChanged();
        this->close();
    }
}

void GaussianBlurDialog::on_cancelButton_clicked()
{
    emit GaussianBlurnoChanged();
    this->close();
}
