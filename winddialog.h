#ifndef WINDDIALOG_H
#define WINDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

namespace Ui {
class WindDialog;
}

class WindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WindDialog(QWidget *parent = 0);
    ~WindDialog();
    int returnValue1();
    int returnValue2();

private:
    Ui::WindDialog *ui;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *windBox1;
    QSpinBox *windBox2;
    QSlider *windSlider1;
    QSlider *windSlider2;

public slots:
    void valueChangeNow();
private slots:


    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void windValueChanged();
    void windPreview();
    void windNoChanged();

};

#endif // WINDDIALOG_H
