#ifndef BRIGHTDIALOG_H
#define BRIGHTDIALOG_H

#include <QDialog>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QSlider>
#include<QLabel>
#include <QAbstractButton>
#include <QPushButton>
#include <QMessageBox>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Dialog *ui;
    QSpinBox *brightBox;
    QSlider *brightSlider;
    QLabel *brightLabel;
};

#endif // BRIGHTDIALOG_H
