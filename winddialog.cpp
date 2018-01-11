#include "winddialog.h"
#include "ui_winddialog.h"

WindDialog::WindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Wind Effect");
    okButton = new QPushButton();
    okButton = ui->okButton;
    cancelButton = new QPushButton();
    cancelButton = ui->cancelButton;
    windBox1 = new QSpinBox();
    windBox2 = new QSpinBox();
    windBox1 = ui->windbox1;
    windBox2 = ui->windbox2;
    windSlider1 = new QSlider();
    windSlider2 = new QSlider();
    windSlider1 = ui->windslider1;
    windSlider2 = ui->windslider2;
    windBox1->setMaximum(100);
    windBox1->setMinimum(1);
    windBox2->setMaximum(100);
    windBox2->setMinimum(1);
    windSlider1->setMaximum(100);
    windSlider1->setMinimum(1);
    windSlider2->setMaximum(100);
    windSlider2->setMinimum(1);


    connect(windBox1,SIGNAL(valueChanged(int)),windSlider1,SLOT(setValue(int)));
    connect(windSlider1,SIGNAL(valueChanged(int)),windBox1,SLOT(setValue(int)));
    connect(windBox2,SIGNAL(valueChanged(int)),windSlider2,SLOT(setValue(int)));
    connect(windSlider2,SIGNAL(valueChanged(int)),windBox2,SLOT(setValue(int)));
    connect(windSlider1,SIGNAL(valueChanged(int)),this,SLOT(valueChangeNow()));
    connect(windSlider2,SIGNAL(valueChanged(int)),this,SLOT(valueChangeNow()));

}

WindDialog::~WindDialog()
{
    delete ui;
}


void WindDialog::valueChangeNow()
{
    emit windPreview();
}

void WindDialog::on_okButton_clicked()
{
    emit windValueChanged();
    this->close();
}

void WindDialog::on_cancelButton_clicked()
{
    emit windNoChanged();
    this->close();
}

int WindDialog::returnValue1()
{
    return windSlider1->value();
}

int WindDialog::returnValue2()
{
    return windSlider2->value();
}
