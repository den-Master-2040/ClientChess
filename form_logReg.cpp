#include "form_logReg.h"
#include "ui_form_logReg.h"
#include "clientglobal.h"


Form_logReg::Form_logReg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_loginRegistrate)
{
    ui->setupUi(this);

}

Form_logReg::~Form_logReg()
{
    delete ui;
}

void Form_logReg::on_pushButton_clicked()
{
    //кнопка войти
    QString login = ui->lineEdit->text();
    lastLog = login;
    QString password = ui->lineEdit_2->text();
    lastPass = password;
    REF_CLIENT.getNetworkObj()->SendToServer("Login, my login=" + login + " my token=" + password + " ");

}

void Form_logReg::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Form_logReg::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Form_logReg::viewFalseLogPass()
{
    ui->errorLabel->setText("Неверный логин\nили пароль");
}

void Form_logReg::succesfulLogin()
{
    REF_CLIENT.getUserData()->setName(lastLog);
    REF_CLIENT.getUserData()->setPasword(lastPass);

}

void Form_logReg::on_pushButton_2_clicked()
{
    QString login = ui->lineEdit_3->text();
    lastLog = login;
    QString password = ui->lineEdit_4->text();
    lastPass = password;
    REF_CLIENT.getNetworkObj()->SendToServer("REG " + login + " " + password);
}

void Form_logReg::on_pushButton_5_clicked()
{
    REF_CLIENT.getNetworkObj()->setipport(ui->lineEdit_5->text(), ui->lineEdit_6->text().toInt());
}

void Form_logReg::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Form_logReg::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
