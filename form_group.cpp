#include "form_group.h"
#include "ui_form_group.h"
#include "clientglobal.h"
#include <QTime>
#include <QKeyEvent>
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

    ui->label_3->setText(REF_CLIENT.getUserData()->getName());
    ui->stackedWidgetGroup->setCurrentIndex(1);
}

void Form_group::createGroup()
{
    ui->stackedWidgetGroup->setCurrentIndex(1);
    ui->label_3->setText(REF_CLIENT.getUserData()->getName());
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_2->setText(ui->lineEdit->text());
}

void Form_group::connectUser(QString name)
{
    ui->label_3->setText(REF_CLIENT.getUserData()->getName());
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(false);
    ui->label_5->setText(name);
    nameAnotherPlayer = name;
    ui->pushButton_3->setText("Начать");
}

void Form_group::messageAnothetUser(QString msg)
{
    ui->textBrowser->append('[' + QTime::currentTime().toString("HH:mm:ss") + "] " + nameAnotherPlayer + " : " + msg);
}

void Form_group::disconnectAnother()
{
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_3->setText(REF_CLIENT.getUserData()->getName());
    ui->pushButton_3->setText("Ожидание\nигроков");
    nameAnotherPlayer = "";
}

void Form_group::setCurrentIndex_(int i)
{
    ui->stackedWidgetGroup->setCurrentIndex(i);
}

void Form_group::setNameGroup(QString name)
{
    ui->label_2->setText(name);
}

void Form_group::on_pushButton_2_clicked()
{
    REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getMainmenu());
}

void Form_group::on_pushButton_4_clicked()
{
    //exit from group
    REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getMainmenu());
    REF_CLIENT.getNetworkObj()->SendToServer("DG");
    ui->stackedWidgetGroup->setCurrentIndex(0);
}

void Form_group::on_pb_create_group_clicked()
{
    REF_CLIENT.getNetworkObj()->SendToServer("C " + ui->lineEdit->text() + " " + (ui->lineEdit_2->text().size() > 0 ? ui->lineEdit_2->text() : " "));
}

void Form_group::on_pushButton_clicked()
{
    REF_CLIENT.getNetworkObj()->SendToServer('T' + ui->lineEdit_3->text());
    ui->textBrowser->append('[' + QTime::currentTime().toString("HH:mm:ss") + "] " + REF_CLIENT.getUserData()->getName() + " : " + ui->lineEdit_3->text());
    ui->lineEdit_3->clear();
}

void Form_group::on_pushButton_3_clicked()
{
    if(nameAnotherPlayer == "") return;
    ui->stackedWidgetGroup->setCurrentIndex(0);
    REF_CLIENT.getNetworkObj()->SendToServer("GO");//когда сервер пришлём нам тоже GO мы начнём игру

}

void Form_group::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == 16777220) on_pushButton_clicked();
}
