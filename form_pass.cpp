#include "form_pass.h"
#include "ui_form_pass.h"
#include "clientglobal.h"

Form_pass::Form_pass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_pass)
{
    ui->setupUi(this);
}

Form_pass::~Form_pass()
{
    delete ui;
}

void Form_pass::on_pushButtonsendpass_clicked()
{

    REF_CLIENT.getNetworkObj()->SendToServer("OKC " + QString::number(id) + " " + ui->lineEdit->text()); //get gpoup
}

void Form_pass::on_pushButton_clicked()
{
    REF_CLIENT.setMainMenu();
}
