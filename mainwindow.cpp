#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientglobal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//MainMenu *m = REF_CLIENT.getMainmenu();
void MainWindow::setCurrentWidget_(QWidget *w)
{
    formsStack.push(w);
    ui->stackedWidget->addWidget(w);//вроде бы копии он не добавляет, значит всё ок
    //qDebug()<< ui->stackedWidget->count();
    ui->stackedWidget->setCurrentWidget(w);
}
