#include "mainwindow.h"

#include <QApplication>

#include "clientglobal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //lientGlobal *client = new ClientGlobal();
    //client->initialization();
    REF_CLIENT.initialization();

    REF_CLIENT.getUserData()->setName("tester123");
    MainWindow *w = REF_CLIENT.getMainWindow();
    w->show();
    REF_CLIENT.setMainMenu();

    return a.exec();
}
