#include "twovaluedialog.h"
#include "ui_twovaluedialog.h"

TwoValueDialog::TwoValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TwoValueDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Two Value Image");
    okButton = new QPushButton();
    okButton = ui->okButton;
    cancelButton = new QPushButton();
    cancelButton = ui->cancleButton;
    valueBox = new QSpinBox();
    valueBox = ui->value_Box;
    valueSlider = new QSlider();
    valueSlider = ui->value_slider;
    valueBox->setMaximum(255);
    valueBox->setMinimum(0);
    valueSlider->setMaximum(255);
    valueSlider->setMinimum(0);

    connect(valueBox,SIGNAL(valueChanged(int)),valueSlider,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),valueBox,SLOT(setValue(int)));
    connect(valueSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChangedNow()));

}

TwoValueDialog::~TwoValueDialog()
{
    delete ui;
}

void TwoValueDialog::on_okButton_clicked()
{
    emit valueChanged();
    this->close();
}

void TwoValueDialog::on_cancleButton_clicked()
{
    emit noChanged();
    this->close();
}


int TwoValueDialog::returnValue()
{
    int a = valueSlider->value();
    return a;
}

void TwoValueDialog::valueChangedNow()
{
    emit preview();
}
