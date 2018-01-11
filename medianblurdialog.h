#ifndef MEDIANBLURDIALOG_H
#define MEDIANBLURDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class MedianBlurDialog;
}

class MedianBlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianBlurDialog(QWidget *parent = 0);
    ~MedianBlurDialog();
    int returnValue();

private:
    Ui::MedianBlurDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *valueBox;
    QSlider *valueSlider;

private slots:
    void valueChangedNow();


    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void MedianBlurValueChanged();
    void MedianBlurPreview();
    void MedianBlurnoChanged();
};

#endif // MEDIANBLURDIALOG_H
