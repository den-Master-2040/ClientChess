#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "clientglobal.h"
MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->label_5->setVisible(false);
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

void MainMenu::setNullGroup(bool state)
{
     ui->label_5->setVisible(state);
}

void MainMenu::on_bt_create_group_clicked()//кнопка создать группу
{
    REF_CLIENT.setGroupMenu();
}

void MainMenu::on_bt_connect_group_clicked()//кнопка подключиться
{
    REF_CLIENT.getNetworkObj()->SendToServer("GG");
    //REF_CLIENT.setGroupsMenu();
}

void MainMenu::on_bt_exit_clicked()//кнопка выход
{
    exit(0);
}

void MainMenu::on_bt_profile_clicked()//кнопка профиль
{
    REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getFormUser());
}

void MainMenu::on_bt_mm_clicked() //кнопка быстрая игра
{
    REF_CLIENT.getNetworkObj()->SendToServer("FG");//fast game
    //REF_CLIENT.setGroupMenu();
    //REF_CLIENT.getGroupMenu()->setCurrentIndex_(1);
}
