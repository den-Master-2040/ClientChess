#include "form_game.h"
#include "ui_form_game.h"
#include "clientglobal.h"

Form_game::Form_game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    //ui->graphicsView->resize(510,510);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0,0,480,480); // Устанавливаем размер сцены
}

Form_game::~Form_game()
{
    delete ui;
}

void Form_game::setPlayerMap()
{
    chessMap.clear();
    int color_counter = 0;
    for(int i = 0; i < 8; i++)
    {
        color_counter++;
        for(int j = 0; j < 8; j++)
        {
            MoveItem *item = new MoveItem(&m_chess);        // Создаём графический элемента
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

    color_counter = 0;

    int chess_Engine_maps[8][8] = {
        {2, 3, 4, 5, 6, 4, 3, 2},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {7, 7, 7, 7, 7, 7, 7, 7},
        {8, 9,10,11,12,10, 9, 8}
    };

    for(int i = 0; i < 8; i++)
    {
        color_counter++;
        for(int j = 0; j < 8; j++)
        {
            //на всякий случай подчишаем карту нашего движка
            m_chess.chess_Engine_map[i][j] = chess_Engine_maps[i][j];
        }
    }


    for(int i = 0; i < 8; i++)
    {
        color_counter++;
        for(int j = 0; j < 8; j++)
        {
            int num_figure = m_chess.chess_Engine_map[j][i];

            /*int chess_Engine_map[8][8] = {
                {2, 3, 4, 5, 6, 4, 3, 2},
                {1, 1, 1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {7, 7, 7, 7, 7, 7, 7, 7},
                {8, 9,10,11,12,10, 9, 8}
            };*/

            if(num_figure) //если поле 0, то там нет фигуры, условие не будет выполнено
            {
                MoveItem *chess = new MoveItem(&m_chess);
                chess->beMove=true;
                chess->name = QString::number(num_figure);
                chess->setPos(SIZECELL*i,SIZECELL*j);
                //chess->scene = scene;
                scene->addItem(chess);   // Добавляем элемент на графическую сцену

                chessMap.push_back(chess);
                chess->oldcol = j;
                chess->oldrow = i;
                chess->col = i;
                chess->row = j;
                chess->number = chessMap.size() - 1;

            }
        }
    }
    qDebug() << "sizeChessMap" << chessMap.size();

}

bool Form_game::getIsMyHod() const
{
    return isMyHod;
}

void Form_game::setIsMyHod(bool value)
{
    isMyHod = value;
    if(value)
    {
        ui->label->setText("Ваш ход");
    }
    else
    {
        ui->label->setText("Ожидайте\nход противника");
    }
}

void Form_game::setWinLos(QString value)
{
    ui->label->setText(value);
}

void Form_game::appendStoreHods(QString hode)
{
    numHod++;
    ui->textBrowser->append(QString::number(numHod) + " : " + hode);
}

void Form_game::clearMap()
{
    qDebug() << "clear!";
    for(int i = 0; i < chessMap.size(); i++)
    {

        qDebug() << "i = " << i;
        scene->removeItem(scene->itemAt(QPoint(chessMap.at(i)->row*SIZECELL,chessMap.at(i)->col*SIZECELL),QTransform()));

    }
    chessMap.clear();
    numHod = 0;
    ui->textBrowser->clear();

}

void Form_game::startPlay()
{
    t_timehod = new QTimer();
    t_numbertimer = new QTimer();
    connect(t_timehod, &QTimer::timeout, [](){

    });

    t_timehod->start(timehod);
}

void Form_game::moveItem_(int numberItem, int x, int y)
{
    setIsMyHod(true);
    MoveItem * item = chessMap.at(numberItem);
    item->setPos_(x,y);

}

void Form_game::setNameTeame(QString name)
{
    ui->label_2->setText(name);
}

void Form_game::on_pushButton_clicked() //выход
{
    clearMap();
    REF_CLIENT.getGroupMenu()->setCurrentIndex_(0);
    REF_CLIENT.setMainMenu();
    REF_CLIENT.getNetworkObj()->SendToServer("DG");
}
