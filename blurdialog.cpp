#include "blurdialog.h"
#include "ui_blurdialog.h"

BlurDialog::BlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlurDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple Blur");
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
    valueBox->setMaximum(50);
    valueBox->setMinimum(1);
    valueSlider->setMaximum(50);
    valueSlider->setMinimum(1);
    
    connect(valueBox,SIGNAL(valueChanged(int)),valueSlider,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),valueBox,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangedNow()));
}

BlurDialog::~BlurDialog()
{
    delete ui;
}


void BlurDialog::valueChangedNow()
{
    emit BlurPreview();
}

void BlurDialog::on_okButton_clicked()
{
    emit BlurValueChanged();
    this->close();
}


void BlurDialog::on_cancelButton_clicked()
{
    emit BlurnoChanged();
    this->close();
}

int BlurDialog::returnValue()
{
    return valueSlider->value();
}
