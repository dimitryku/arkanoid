#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <vector>
#include <ball/ball.h>
#include <brick/brick.h>
#include "mainwindow.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QTimer"
#include <brick/brickbuilder.h>
#include <bonus/bonus.h>
#include "QString"
class GameField : public QGraphicsView
{
    Q_OBJECT

public:
    GameField();
    QGraphicsScene* scene;
public slots:
   void generateBonus(Brick* brick);
private:
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
    std::vector<Bonus*> bonuses;
    Platform* platform;
    QTimer* MainGameTimer;
    void Tick();
    //std::vector<Bonus> activeBonuses;
    //Score score
    //std::vector<BonusBody> fallingBonuses

    void ballCollision(Ball* ball);
};

#endif // GAMEFIELD_H
