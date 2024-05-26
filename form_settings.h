#ifndef FORM_SETTINGS_H
#define FORM_SETTINGS_H

#include <QWidget>

namespace Ui {
class Form_settings;
}

class Form_settings : public QWidget
{
    Q_OBJECT

public:
    explicit Form_settings(QWidget *parent = nullptr);
    ~Form_settings();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Form_settings *ui;
};

#endif // FORM_SETTINGS_H
