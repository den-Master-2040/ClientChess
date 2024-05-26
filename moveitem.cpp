#include "moveitem.h"
#include "clientglobal.h"

MoveItem::MoveItem(chess_Engine *m_chess, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->m_chess = m_chess;
}

MoveItem::~MoveItem()
{

}

QString convert(int oldcol, int oldrow, int col, int row)
{
    QString result = "";

    result = char(oldcol + 48 + '0') + QString::number(oldrow) + char(col + 48 + '0') + QString::number(row);
    return result;
}

void MoveItem::setPos_(int x, int y)
{//вражеский ход

    QVector<MoveItem*> chessMap = REF_CLIENT.getFormGame()->chessMap;
    for(int i = 50; i < chessMap.size(); i++)
    {
        qDebug()<< "setPos";
        qDebug() << "for= " << x << "y = "<< y << "i = "<< i<< "chessMap.at(i)->col = "<< chessMap.at(i)->col<< "chessMap.at(i)->row = "<< chessMap.at(i)->row;
        if(chessMap.at(i)->col  == x)
            if((chessMap.at(i)->row  == y) && chessMap.at(i)->beMove)
            {
                // удаляем элемент
                if(chessMap.at(i) != this)
                {
                    checkDeleteItem(i);
                    this->scene()->removeItem(chessMap.at(i));
                    chessMap.remove(i);
                    qDebug() << "QVector<MoveItem*> x = " << x*SIZECELL << "y = "<< y*SIZECELL;
                    break;
                }
            }
    }

    col = x;
    row = y;


    qDebug() << "col: "<< col;
    qDebug() << "row: "<< row;

    //x*=SIZECELL;
    //y*=SIZECELL;




    int firstClick = oldcol * 10 + oldrow; //место ОТКУДА ходим
    int secondClick = row * 10 + col;      //место, КУДА ходим

    qDebug() << "firstClick: "<< firstClick;
    qDebug() << "secondClick: "<< secondClick;
    if(m_chess->hod(firstClick,secondClick))
    {
        REF_CLIENT.getFormGame()->appendStoreHods(convert(oldrow, oldcol, col, row));
        this->setPos(x*SIZECELL, y*SIZECELL);
        oldcol = row;
        oldrow = col;
    }
}

bool MoveItem::validDeleteItem(int number)
{
    QString team = REF_CLIENT.getUserData()->getTeam();
    if(team == "white")
    {
        if(number > 0 && number < 7) return true;
        else return false;
    }
    else if(team == "black")
    {
        if(number > 6 && number < 13) return true;
        else return false;
    }
}

bool MoveItem::isValidTeam()
{
    QString team = REF_CLIENT.getUserData()->getTeam();
    int numFigure = name.toInt();

    if(team == "white" && (numFigure > 0 && numFigure < 7))
        return true;
    if(team == "black" && (numFigure > 6 && numFigure < 13))
        return true;
    return false;
}

void MoveItem::checkDeleteItem(int i)
{
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
    QVector<MoveItem*> chessMap = REF_CLIENT.getFormGame()->chessMap;

    qDebug() << "checkDeleteItem i = " << i;
    if(chessMap.at(i)->name.toInt() == 12)
    {
        REF_CLIENT.getFormGame()->setIsMyHod(false);
        if(REF_CLIENT.getUserData()->getTeam() == "black")
        {
            //это поражение, так как 12 - наш король
            qDebug() << "вы проиграли, мьсе";
            REF_CLIENT.getFormGame()->setWinLos("Вы проиграли");
        }
        else if(REF_CLIENT.getUserData()->getTeam() == "white")
        {
            //это победа потому что 12 - НЕ наш король
            qDebug() << "вы одержали победу, мьсе";
            REF_CLIENT.getFormGame()->setWinLos("Вы победили!");

        }
        endGame = true;
    }

    if(chessMap.at(i)->name.toInt() == 6)
    {
        REF_CLIENT.getFormGame()->setIsMyHod(false);
        if(REF_CLIENT.getUserData()->getTeam() == "black")
        {
            //это победа потому что 6 - НЕ наш король
            qDebug() << "вы одержали победу, мьсе";
            REF_CLIENT.getFormGame()->setWinLos("Вы победили!");
        }
        else if(REF_CLIENT.getUserData()->getTeam() == "white")
        {
            //это поражение, так как 6 - наш король
            qDebug() << "вы проиграли, мьсе";
            REF_CLIENT.getFormGame()->setWinLos("Вы проиграли");
        }
        endGame = true;

    }
}

QRectF MoveItem::boundingRect() const
{
    return QRectF (0,0,SIZECELL,SIZECELL);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if(!isValidTeam()) return;

    if(name == "")
    {
        painter->setPen(color);
        painter->setBrush(color);
        painter->setBackground(color);
    }
    else
    {
        QPixmap *map = new QPixmap(":/" +name+".png");
        *map = map->scaledToWidth(SIZECELL);
        *map = map->scaledToHeight(SIZECELL);
        painter->drawPixmap(0,0,*map);
    }


    painter->drawRect(0,0,SIZECELL,SIZECELL);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isValidTeam()) return;
    if(!REF_CLIENT.getFormGame()->isMyHod) return;
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    //qDebug() << "mouseMoveEvent";
    if(beMove)
        this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isValidTeam()) return;
    if(!REF_CLIENT.getFormGame()->isMyHod) return;


    qDebug() << "mousePressEvent";
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isValidTeam()) return;
    qDebug() << "mouseReleaseEvent";
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    if(beMove && REF_CLIENT.getFormGame()->isMyHod)
        setPosToCell();
    qDebug() << "mouseReleaseEvent id=" << number;

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void MoveItem::setPosToCell()
{
    QPointF pos = scenePos();

    int x = pos.x();
    int y = pos.y();

    qDebug() << "x: "<< x;
    qDebug() << "y: "<< y;

    x = x / SIZECELL;
    y = y / SIZECELL;

    if(x > 7 || x < 0 || y > 7 || y < 0) {
        qDebug() << "Out of range";
        returnToRange(x,y);
    }

    col = x;
    row = y;


    qDebug() << "col: "<< col;
    qDebug() << "row: "<< row;

    x*=SIZECELL;
    y*=SIZECELL;

    qDebug() << "xR: "<< x;
    qDebug() << "yR: "<< y;


    //здесь должны быть прверки

    pos.setX(x);
    pos.setY(y);

    int firstClick = oldcol * 10 + oldrow; //место ОТКУДА ходим
    int secondClick = row * 10 + col;      //место, КУДА ходим

    qDebug() << "firstClick: "<< firstClick;
    qDebug() << "secondClick: "<< secondClick;




    if(m_chess->hod(firstClick,secondClick))
    {

        //мы ходим и проверяем, если мы сходили на "что-то" то мы это удаляем
        QVector<MoveItem*> chessMap = REF_CLIENT.getFormGame()->chessMap;
        for(int i = 0; i < chessMap.size(); i++){
        qDebug() << "for= " << x << "y = "<< y << "i = "<< i<< "chessMap.at(i)->col = "<< chessMap.at(i)->col<< "chessMap.at(i)->row = "<< chessMap.at(i)->row;
            if(chessMap.at(i)->col *SIZECELL == x)
                if((chessMap.at(i)->row*SIZECELL  == y) && chessMap.at(i)->beMove)
                {

                    if(chessMap.at(i) != this && !validDeleteItem(chessMap.at(i)->name.toInt()) ){//isValid team -
                        checkDeleteItem(i);
                        this->scene()->removeItem(chessMap.at(i)); //удаляем элемент
                        qDebug() << "delete to "<< chessMap.at(i)->col << " " << chessMap.at(i)->row;
                        chessMap.remove(i);
                        break;
                    }
                }
        }
        REF_CLIENT.getFormGame()->appendStoreHods(convert(oldrow, oldcol, col, row));
        this->setPos(pos);
        if(!endGame)
            REF_CLIENT.getFormGame()->setIsMyHod(false);

        REF_CLIENT.getNetworkObj()->SendToServer("HOD" + QString::number(number)
                                                       + QString::number(col)
                                                       + QString::number(row));
        oldcol = row;
        oldrow = col;
    }
    else
       this->setPos(QPointF(oldrow*SIZECELL,oldcol*SIZECELL));

}

void MoveItem::returnToRange(int &x, int &y)
{
    if(x < 0) x = 0;
    if(x > 7) x = 7;
    if(y < 0) y = 0;
    if(y > 7) y = 7;
}

