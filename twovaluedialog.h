#ifndef TWOVALUEDIALOG_H
#define TWOVALUEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>

namespace Ui {
class TwoValueDialog;
}

class TwoValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TwoValueDialog(QWidget *parent = 0);
    ~TwoValueDialog();
    int returnValue();

private:
    Ui::TwoValueDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *valueBox;
    QSlider *valueSlider;



private slots:
    void on_okButton_clicked();
    void on_cancleButton_clicked();
    void valueChangedNow();

signals:
    void valueChanged();
    void preview();
    void noChanged();



};

#endif // TWOVALUEDIALOG_H
