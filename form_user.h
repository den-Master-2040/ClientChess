#ifndef FORM_USER_H
#define FORM_USER_H

#include <QWidget>

namespace Ui {
class Form_user;
}

class Form_user : public QWidget
{
    Q_OBJECT

public:
    explicit Form_user(QWidget *parent = nullptr);
    ~Form_user();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

private:
    Ui::Form_user *ui;
};

#endif // FORM_USER_H
