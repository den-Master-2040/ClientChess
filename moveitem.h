#ifndef MOVEITEM_H
#define MOVEITEM_H
#define SIZECELL 60

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include "chess_engine.h"
#include "QGraphicsScene"
class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveItem(chess_Engine *m_chess, QObject *parent = 0 );
    ~MoveItem();
    Qt::GlobalColor color;

    bool beMove;//можно ли двигать объект
    QString name = "";
    int number = -1; //номер в будущем массиве фигур
    int col = -1;
    int row = -1;
    int oldcol, oldrow = -1;

    chess_Engine *m_chess = nullptr;
    QGraphicsScene *scene;
    void setPos_(int x, int y);
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setPosToCell();
    void returnToRange(int &x, int &y);
};

#endif // MOVEITEM_H
