#ifndef GAUSSIANBLURDIALOG_H
#define GAUSSIANBLURDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class GaussianBlurDialog;
}

class GaussianBlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianBlurDialog(QWidget *parent = 0);
    ~GaussianBlurDialog();
    int returnValue();


private:
    Ui::GaussianBlurDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *valueBox;
    QSlider *valueSlider;

private slots:
    void valueChangedNow();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void GaussianBlurValueChanged();
    void GaussianBlurPreview();
    void GaussianBlurnoChanged();
};

#endif // GAUSSIANBLURDIALOG_H
