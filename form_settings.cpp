#include "form_settings.h"
#include "ui_form_settings.h"
#include <QColor>
#include <QColorDialog>
#include "clientglobal.h"
#include "moveitem.h"

Form_settings::Form_settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_settings)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    setPlayerMap();
}

Form_settings::~Form_settings()
{
    delete ui;
}

void Form_settings::on_pushButton_clicked()
{
    whiteMap = QColorDialog::getColor();
    REF_CLIENT.getFormGame()->whiteMap = whiteMap;
    clearMap();
    setPlayerMap();
}

void Form_settings::on_pushButton_2_clicked()
{
    blackMap = QColorDialog::getColor();
    REF_CLIENT.getFormGame()->blackMap = blackMap;
    clearMap();
    setPlayerMap();
}

void Form_settings::on_pushButton_3_clicked()
{
    REF_CLIENT.setMainMenu();
}

void Form_settings::setPlayerMap()
{
    chessMap.clear();
    int color_counter = 0;
    for(int i = 0; i < 8; i++)
    {
        color_counter++;
        for(int j = 0; j < 8; j++)
        {
            MoveItem *item = new MoveItem(nullptr);        // Создаём графический элемента
            item->setPos(SIZECELL*i,SIZECELL*j);
            item->beMove = false;

            if(color_counter % 2)
                item->color = whiteMap;
            else
                item->color = blackMap;

            scene->addItem(item);   // Добавляем элемент на графическую сцену
            chessMap.push_back(item);
            color_counter++;
        }
    }


    qDebug() << "sizeChessMap" << chessMap.size();

}

void Form_settings::clearMap()
{
    qDebug() << "clear!";
    for(int i = 0; i < chessMap.size(); i++)
        scene->removeItem(scene->itemAt(QPoint(chessMap.at(i)->row*SIZECELL,chessMap.at(i)->col*SIZECELL),QTransform()));
    chessMap.clear();
}

