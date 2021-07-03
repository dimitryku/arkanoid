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
#include "QKeyEvent"
#include <math.h>


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
    QTimer* PlatformUpdateTimer;
    void Tick();
    void UpdatePlatform();

    enum PlatformAction{
        None,
        MoveRight,
        MoveLeft,
        Shoot
    };
    PlatformAction CurrentPlatformAction;

    //std::vector<Bonus> activeBonuses;
    //Score score
    //std::vector<BonusBody> fallingBonuses

    void ballCollision(Ball* ball);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // GAMEFIELD_H
