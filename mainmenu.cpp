#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "clientglobal.h"
MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::setCountUsers(int count)
{
    ui->label_num_players->setText(QString::number(count));
}

void MainMenu::setConnections(bool state)
{
    if(state)
    {
        ui->label_6->setText("Подключено");
    }
    else
    {
        ui->label_6->setText("Нет подключения");
        ui->label_num_players->setText("Нет\nсвязи с сервером");
    }
}


void MainMenu::on_bt_create_group_clicked()
{
    REF_CLIENT.setGroupMenu();
}

void MainMenu::on_bt_connect_group_clicked()
{
    REF_CLIENT.getNetworkObj()->SendToServer("GG");
    //REF_CLIENT.setGroupsMenu();
}
