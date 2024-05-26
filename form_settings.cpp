#include "form_settings.h"
#include "ui_form_settings.h"

Form_settings::Form_settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_settings)
{
    ui->setupUi(this);
}

Form_settings::~Form_settings()
{
    delete ui;
}
