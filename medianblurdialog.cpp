#include "medianblurdialog.h"
#include "ui_medianblurdialog.h"

MedianBlurDialog::MedianBlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianBlurDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Median Blur");
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
    valueBox->setMinimum(0);
    valueSlider->setMaximum(50);
    valueSlider->setMinimum(0);

    connect(valueBox,SIGNAL(valueChanged(int)),valueSlider,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),valueBox,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangedNow()));
}


MedianBlurDialog::~MedianBlurDialog()
{
    delete ui;
}

int MedianBlurDialog::returnValue()
{
    return valueSlider->value();
}

void MedianBlurDialog::valueChangedNow()
{
    if(valueSlider->value() % 2 == 1)
        emit MedianBlurPreview();
}

void MedianBlurDialog::on_okButton_clicked()
{
    if(valueSlider->value() % 2 == 1)
    {
        emit MedianBlurValueChanged();
        this->close();
    }
}

void MedianBlurDialog::on_cancelButton_clicked()
{
    emit MedianBlurnoChanged();
    this->close();
}
