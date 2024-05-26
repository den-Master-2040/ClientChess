#ifndef CLIENTGLOBAL_H
#define CLIENTGLOBAL_H


#include <QObject>

//структура групп, если понадобиться их перемещать
struct group{
    int id = -1;
    QString name = "";
    QString name_first_user = "";
};

#include "mainmenu.h"
#include "mainwindow.h"
#include "form_group.h"
#include "network_object.h"
#include "form_groups.h"
#include "userdata.h"
#include "form_game.h"
#include "form_user.h"

//Данный класс управляет всеми объектами клиента.
//Здесь можно получить доступ к любому объекту из любого объекта.
//Создается один раз, уникален на всю программу, как и все объекты, созданные здесь.
class ClientGlobal : public QObject
{
    Q_OBJECT
public:
    explicit ClientGlobal(QObject *parent = nullptr);
    static ClientGlobal &getInstance();

    void initialization ();

    MainWindow     * getMainWindow ();
    MainMenu       * getMainmenu   ();
    Form_group     * getGroupMenu  ();
    network_object * getNetworkObj ();
    form_groups    * getGroupsMenu ();
    UserData       * getUserData   ();
    Form_game      * getFormGame   ();
    Form_user      * getFormUser   ();

    void setMainMenu    ();
    void setGroupMenu   ();
    void setGroupsMenu  ();
    void joinGroup      ();
    void createGroup_   ();

private:

    MainWindow     * createMainWindow ();
    MainMenu       * createMainmenu   ();
    Form_group     * createGroup      ();
    network_object * createNetworkObj ();
    form_groups    * createGroups     ();
    UserData       * createUserData   ();
    Form_game      * createFormGame   ();
    Form_user      * createFormUser   ();

    //объекты форм - единственные в своем роде, копий не может и не должно быть!
    MainWindow     * mainwindow  = nullptr;
    MainMenu       * mainmenu    = nullptr;
    Form_group     * group       = nullptr;
    form_groups    * groups      = nullptr;
    Form_game      * game        = nullptr;
    Form_user      * form_user   = nullptr;

    //объект работы с сетью
    network_object * network_obj = nullptr;

    //объект пользовательских данных
    UserData       * userdata    = nullptr;

signals:

};

#define REF_CLIENT (ClientGlobal::getInstance())
#endif // CLIENTGLOBAL_H
