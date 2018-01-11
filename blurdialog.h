#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class BlurDialog;
}

class BlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlurDialog(QWidget *parent = 0);
    ~BlurDialog();
    int returnValue();


private:
    Ui::BlurDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *valueBox;
    QSlider *valueSlider;

private slots:
    void valueChangedNow();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void BlurValueChanged();
    void BlurPreview();
    void BlurnoChanged();
};

#endif // BLURDIALOG_H
