#ifndef FORM_PASS_H
#define FORM_PASS_H

#include <QWidget>

namespace Ui {
class Form_pass;
}

class Form_pass : public QWidget
{
    Q_OBJECT

public:
    explicit Form_pass(QWidget *parent = nullptr);
    ~Form_pass();
    int id = 0;
private slots:
    void on_pushButtonsendpass_clicked();

    void on_pushButton_clicked();

private:
    Ui::Form_pass *ui;
};

#endif // FORM_PASS_H
