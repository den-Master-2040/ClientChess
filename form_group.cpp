#include "form_group.h"
#include "ui_form_group.h"
#include "clientglobal.h"
Form_group::Form_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_group)
{
    ui->setupUi(this);
}

Form_group::~Form_group()
{
    delete ui;
}

void Form_group::join()
{
    ui->stackedWidgetGroup->setCurrentIndex(1);
}

void Form_group::createGroup()
{
    ui->stackedWidgetGroup->setCurrentIndex(1);
    ui->label_2->setText(ui->lineEdit->text());
}

void Form_group::on_pushButton_2_clicked()
{
    REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getMainmenu());
}

void Form_group::on_pushButton_4_clicked()
{
    REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getMainmenu());
}

void Form_group::on_pb_create_group_clicked()
{
    REF_CLIENT.getNetworkObj()->SendToServer("C " + ui->lineEdit->text() + " " + (ui->lineEdit_2->text().size() > 0 ? ui->lineEdit_2->text() : " "));
}
