#ifndef FORM_GAME_H
#define FORM_GAME_H


#include <QWidget>
#include <QWidget>
#include "chess_engine.h"
#include <QVBoxLayout>
#include "moveitem.h"

namespace Ui {
class Form_game;
}

class Form_game : public QWidget
{
    Q_OBJECT

public:
    explicit Form_game(QWidget *parent = nullptr);
    ~Form_game();
    void setPlayerMap();
    int counter_click_button = 0;
    int firstClick = -1;
    int secondClick = -1;
    //QVBoxLayout *m_vLaayout;
    int SIZE_BUTTON = 60;
    int MERGE_BUTTON = 2;
    int color_backgroind_counter = 0;
    bool isMyHod = false;
    chess_Engine m_chess;                    //логика шахмат

    void moveItem_(int numberItem, int x, int y);
    void setNameTeame(QString name);

    void update_chess_map();
    void update_chess_array(int arr[8][8]);
    QVector <MoveItem*> chessMap;
    QGraphicsScene *scene;
    QString nameAnotherPlayer = "";

    int numHod = 0;
    bool getIsMyHod() const;
    void setIsMyHod(bool value);
    void setWinLos(QString value);
    void appendStoreHods(QString hode);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Form_game *ui;

};

#endif // FORM_GAME_H
