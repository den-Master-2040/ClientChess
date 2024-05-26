#include "form_user.h"
#include "ui_form_user.h"
#include "clientglobal.h"

Form_user::Form_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_user)
{
    ui->setupUi(this);
    ui->lineEdit->setText(REF_CLIENT.getUserData()->getName());
    ui->lineEdit_2->setText(REF_CLIENT.getUserData()->getPasword());
}

Form_user::~Form_user()
{
    delete ui;
}

void Form_user::on_pushButton_clicked()
{
    REF_CLIENT.setMainMenu();
}

void Form_user::on_lineEdit_editingFinished()
{
    REF_CLIENT.getUserData()->setName(ui->lineEdit->text());
}

void Form_user::on_lineEdit_2_editingFinished()
{
    REF_CLIENT.getUserData()->setPasword(ui->lineEdit_2->text());
}
