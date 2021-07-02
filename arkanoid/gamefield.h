#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <vector>
#include <ball/ball.h>
#include <brick/brick.h>
#include "mainwindow.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include <brick/brickbuilder.h>

class GameField : public QGraphicsView
{
public:
    GameField();
    QGraphicsScene* scene;

private:
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
    Platform* platform;
    //std::vector<Bonus> activeBonuses;
    //Score score
    //std::vector<BonusBody> fallingBonuses
};

#endif // GAMEFIELD_H
