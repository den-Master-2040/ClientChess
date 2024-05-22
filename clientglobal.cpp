#include "clientglobal.h"
#include "qdebug.h"
ClientGlobal::ClientGlobal(QObject *parent) : QObject(parent)
{
    qDebug() << "constructor ClientGlobal!" << i++;
}

MainWindow *ClientGlobal::getMainWindow()
{
    ClientGlobal & instanse  = getInstance();
    if(instanse.mainwindow != nullptr)
    {
        return instanse.mainwindow;
    }
    else
    {
        instanse.createMainWindow();
        return instanse.mainwindow;
    }
}

MainWindow *ClientGlobal::createMainWindow()
{
    mainwindow = new MainWindow();
    return mainwindow;
}

MainMenu *ClientGlobal::createMainmenu()
{
    mainmenu = new MainMenu();
    return mainmenu;
}

Form_group *ClientGlobal::createGroup()
{
    group = new Form_group();
    return group;
}

network_object *ClientGlobal::createNetworkObj()
{
    network_obj = new network_object();
    return network_obj;
}

form_groups *ClientGlobal::createGroups()
{
    groups = new form_groups();
    return groups;
}

MainMenu* ClientGlobal::getMainmenu()
{
    ClientGlobal & instanse  = getInstance();
    if(instanse.mainmenu != nullptr)
    {
        return instanse.mainmenu;
    }
    else
    {
        instanse.createMainmenu();
        return instanse.mainmenu;
    }
}

Form_group *ClientGlobal::getGroupMenu()
{
    ClientGlobal & instanse  = getInstance();
    if(instanse.group != nullptr)
    {
        return instanse.group;
    }
    else
    {
        instanse.createGroup();
        return instanse.group;
    }
}

network_object *ClientGlobal::getNetworkObj()
{
    ClientGlobal & instanse  = getInstance();
    if(instanse.network_obj != nullptr)
    {

        return instanse.network_obj;
    }
    else
    {
        qDebug() << "return" ;
        instanse.createNetworkObj();
        return instanse.network_obj;
    }
}

form_groups *ClientGlobal::getGroupsMenu()
{
    ClientGlobal &instanse  = getInstance();
    if(instanse.groups != nullptr)
    {
        return instanse.groups;
    }
    else
    {
        instanse.createGroups();
        return instanse.groups;
    }
}

ClientGlobal &ClientGlobal::getInstance()
{
    static std::unique_ptr<ClientGlobal> instanse (new ClientGlobal());
    if(instanse != nullptr)
    {
        qDebug() << "return instance";
        return *instanse;
    }
}

void ClientGlobal::initialization()
{
    if(group ==nullptr)
        createGroup();
    if(mainmenu ==nullptr)
        createMainmenu();
    if(mainmenu ==nullptr)
        createMainWindow();
    if(network_obj ==nullptr)
        createNetworkObj();
    if(groups == nullptr)
        createGroups();
}

void ClientGlobal::setMainMenu()
{
    if(mainwindow!=nullptr && mainmenu != nullptr)
        mainwindow->setCurrentWidget_(mainmenu);
    else
    {
        mainwindow = getMainWindow();
        mainmenu = getMainmenu();
        mainwindow->setCurrentWidget_(mainmenu);
    }
}

void ClientGlobal::setGroupMenu()
{
    if(mainwindow!=nullptr && group !=nullptr)
        mainwindow->setCurrentWidget_(group);
    else
    {
        mainwindow = getMainWindow();
        group = getGroupMenu();
        mainwindow->setCurrentWidget_(group);
    }
}

void ClientGlobal::setGroupsMenu()
{
    if(mainwindow!=nullptr && groups !=nullptr)
        mainwindow->setCurrentWidget_(groups);
    else
    {
        mainwindow = getMainWindow();
        groups = getGroupsMenu();
        mainwindow->setCurrentWidget_(groups);
    }
}

void ClientGlobal::joinGroup()
{
    mainwindow->setCurrentWidget_(group);
    group->join();
}

void ClientGlobal::createGroup_()
{
    mainwindow->setCurrentWidget_(group);
    group->createGroup();
}
