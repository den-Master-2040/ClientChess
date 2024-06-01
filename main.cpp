#include "mainwindow.h"

#include <QApplication>

#include "clientglobal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    REF_CLIENT.initialization();

    MainWindow *w = REF_CLIENT.getMainWindow();
    w->show();

    REF_CLIENT.getUserData()->loginingAutherization();

    //REF_CLIENT.setMainMenu();

    return a.exec();
}
