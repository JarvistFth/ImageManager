#ifndef BILATERALBLURDIALOG_H
#define BILATERALBLURDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class BilateralBlurDialog;
}

class BilateralBlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BilateralBlurDialog(QWidget *parent = 0);
    ~BilateralBlurDialog();
    int returnValue();

private slots:
    void valueChangedNow();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void BilateralBlurValueChanged();
    void BilateralBlurPreview();
    void BilateralBlurnoChanged();

private:
    Ui::BilateralBlurDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *valueBox;
    QSlider *valueSlider;
};

#endif // BILATERALBLURDIALOG_H
