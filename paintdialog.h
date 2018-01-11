#ifndef PAINTDIALOG_H
#define PAINTDIALOG_H

#include <QDialog>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QSlider>
#include<QLabel>
#include<QAbstractButton>
#include<QPushButton>


namespace Ui {
class paintDialog;
}

class paintDialog : public QDialog
{
    Q_OBJECT
signals:
    void senddata();

public:
    explicit paintDialog(QWidget *parent = 0);
    int getBrushSize();
    int getCoarseness();
    ~paintDialog();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_2_valueChanged(int arg1);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::paintDialog *ui;
    QLabel *label1;
    QLabel *label2;
    QSpinBox *box1;
    QSpinBox *box2;
    QSlider *slider1;
    QSlider *slider2;
};

#endif // PAINTDIALOG_H
