#include "form_settings.h"
#include "ui_form_settings.h"
#include <QColor>
#include <QColorDialog>
#include "clientglobal.h"
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

void Form_settings::on_pushButton_clicked()
{
    REF_CLIENT.getFormGame()->whiteMap = QColorDialog::getColor();
}

void Form_settings::on_pushButton_2_clicked()
{
    REF_CLIENT.getFormGame()->blackMap = QColorDialog::getColor();
}

void Form_settings::on_pushButton_3_clicked()
{
    REF_CLIENT.setMainMenu();
}
