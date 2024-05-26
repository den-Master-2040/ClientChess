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

private:
    Ui::Form_settings *ui;
};

#endif // FORM_SETTINGS_H
