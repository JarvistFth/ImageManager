#ifndef BRIGHTVALUEDIALOG_H
#define BRIGHTVALUEDIALOG_H

#include <QDialog>
#include<QHBoxLayout>
#include<QSpinBox>
#include<QSlider>
#include<QLabel>
#include<QAbstractButton>
#include<QPushButton>

namespace Ui {
class brightValueDialog;
}

class brightValueDialog : public QDialog
{
    Q_OBJECT

signals:

    void brightValueChanged();
    void brightPreview();
    void brightNoChanged();

public:
    explicit brightValueDialog(QWidget *parent = 0);
    int getBright();
    int getContract();

    ~brightValueDialog();

public slots:
     void valueChangeNow();

private slots:
     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

private:
    Ui::brightValueDialog *ui;
    QSpinBox *brightBox;
    QSlider *brightSlider;
    QLabel *brightLabel;
    QSpinBox *contractBox;
    QSlider *contractSlider;
    QLabel *contractlabel;
};

#endif // BRIGHTVALUEDIALOG_H
