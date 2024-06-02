#ifndef FORM_LOGINREGISTRATE_H
#define FORM_LOGINREGISTRATE_H

#include <QWidget>

namespace Ui {
class Form_loginRegistrate;
}

class Form_logReg : public QWidget
{
    Q_OBJECT

    QString lastLog, lastPass;

public:
    explicit Form_logReg(QWidget *parent = nullptr);
    ~Form_logReg();

    void viewFalseLogPass();
    void succesfulLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Form_loginRegistrate *ui;
};

#endif // FORM_LOGINREGISTRATE_H
