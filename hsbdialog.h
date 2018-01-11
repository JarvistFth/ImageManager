#ifndef HSBDIALOG_H
#define HSBDIALOG_H

#include <QDialog>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QSlider>
#include<QLabel>
#include<QAbstractButton>
#include<QPushButton>

namespace Ui {
class HSBDialog;
}

class HSBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSBDialog(QWidget *parent = 0);
    int getH();
    int getS();
    int getB();
    ~HSBDialog();

signals:
    void ValueChanged();
    void Preview();
    void ValueNoChanged();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void ValueChangedNow();
private:
    Ui::HSBDialog *ui;
    QSlider *sl1;
    QSlider *sl2;
    QSlider *sl3;
    QSpinBox *sb1;
    QSpinBox *sb2;
    QSpinBox *sb3;
    QPushButton *ok;
    QPushButton *cancel;

};

#endif // HSBDIALOG_H
