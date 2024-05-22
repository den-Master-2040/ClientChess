#include "form_groups.h"
#include "ui_form_groups.h"
#include "clientglobal.h"


form_groups::form_groups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form_groups)
{
    ui->setupUi(this);
}

form_groups::~form_groups()
{
    delete ui;
}

void form_groups::setDataGroup(QVector<group> &groups)
{

    if(groups.size() == 0)
    {
        //ui->label_5->setVisible(true);
        return;
    }


    ui->scrollAreaWidgetContents_2->repaint();
    for(int i = 0; i < groups.size(); i++)
    {
        //ui->label_5->setVisible(false);
        QLabel *name_group;
        name_group = new QLabel(ui->scrollAreaWidgetContents_2);
        name_group->setObjectName(QString::fromUtf8("label_5")+QString::number(i));
        name_group->setText(groups.at(i).name);
        name_group->setMinimumSize(QSize(200,21));

        ui->gridLayout_3->addWidget(name_group, i+1, 0, 1, 1);

        QLabel *size_player;
        size_player = new QLabel(ui->scrollAreaWidgetContents_2);
        size_player->setObjectName(QString::fromUtf8("label_5")+QString::number(i));
        size_player->setText("1/2");
        size_player->setMinimumSize(QSize(100,21));

        ui->gridLayout_3->addWidget(size_player, i+1, 1, 1, 1);

        QLabel *id;
        id = new QLabel(ui->scrollAreaWidgetContents_2);
        id->setObjectName(QString::fromUtf8("label_5")+QString::number(i));
        id->setText(QString::number(groups.at(i).id));
        id->setMinimumSize(QSize(100,21));

        ui->gridLayout_3->addWidget(id, i+1, 2, 1, 1);

        QPushButton *pb;
        pb = new QPushButton(ui->scrollAreaWidgetContents_2);
        pb->setObjectName(QString::fromUtf8("pushButton_2")+QString::number(i));
        pb->setText("Войти");
        pb->setStyleSheet("QPushButton{\n\nbackground-color:qlineargradient(spread:pad, "
                          "x1:0.494, y1:0.846136, x2:0.494382, y2:1, stop:0 rgba(69, 69, 69, "
                          "255), stop:1 rgba(149, 149, 149, 255));\ncolor:white;\nborder-radius:"
                          " 2px;\n}\nQPushButton::pressed{\n\nbackground-color:qlineargradient(spread:pad,"
                          " x1:0.426, y1:0.800682, x2:0.427, y2:1, stop:0 rgba(37, 37, 37, 255), stop:"
                          "1 rgba(87, 87, 87, 255));\ncolor:white;;\nborder-radius: 2px;\n};\n");

        ui->gridLayout_3->addWidget(pb, i+1, 3, 1, 1);

        connect(pb, &QPushButton::clicked,[this,i,name_group,size_player,id,pb, groups](){
            //fcg->nameSecondUser = network_obj->groups.at(i).name_first_user;//пихаем логин первого юзера из сети
            //fcg->nameFirstUser = network_obj->login;//пихаем свой логин
            //fcg->nextPage();
            //on_bt_create_group_clicked();
            REF_CLIENT.setGroupMenu();
            REF_CLIENT.joinGroup();
            REF_CLIENT.getNetworkObj()->SendToServer("OKC " + QString::number(groups.at(i).id)); //get gpoup

            //delete name_group;
            //delete size_player;
            //delete id;
            //delete pb;
            qDebug() << "Delete!";
        });

        connect(ui->pushButton_4, &QPushButton::clicked, [name_group,size_player,id,pb](){
            //delete name_group;
            //delete size_player;
            //delete id;
            //delete pb;
            qDebug() << "Delete!";
        });

    }
}
