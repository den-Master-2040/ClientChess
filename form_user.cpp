#include "form_user.h"
#include "ui_form_user.h"
#include "clientglobal.h"

Form_user::Form_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_user)
{
    ui->setupUi(this);
}

Form_user::~Form_user()
{
    delete ui;
}

void Form_user::on_pushButton_clicked()
{
    REF_CLIENT.setMainMenu();
}
