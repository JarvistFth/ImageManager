#include "bilateralblurdialog.h"
#include "ui_bilateralblurdialog.h"

BilateralBlurDialog::BilateralBlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilateralBlurDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Bilateral Blur");
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

BilateralBlurDialog::~BilateralBlurDialog()
{
    delete ui;
}

int BilateralBlurDialog::returnValue()
{
    return valueSlider->value();
}

void BilateralBlurDialog::valueChangedNow()
{
    emit BilateralBlurPreview();
}

void BilateralBlurDialog::on_okButton_clicked()
{
    emit BilateralBlurValueChanged();
    this->close();
}

void BilateralBlurDialog::on_cancelButton_clicked()
{
    emit BilateralBlurnoChanged();
    this->close();
}
