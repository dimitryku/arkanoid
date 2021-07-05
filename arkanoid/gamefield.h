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
#include <bonus/bonuses.h>
#include <bonus/bonusbody.h>

class GameField : public QGraphicsView
{
    Q_OBJECT

public:
    GameField();
    QGraphicsScene* scene;
    int GetScore();
    
public slots:
   void brickDestoryed(Brick* brick);
   void increaseSizePlatform(bool finished);
   void decreaseSizePlatform(bool finished);
   void increaseSpeedBall();
   void decreaseSpeedBall();
   void changeInverse();
   void addLife();
   void addBall();
   void setUberBall();
   void setMagnetBall();
   void setCommonBall();
   void finishedBonus(Bonus* bonus);

signals:
   void GameEnded(); /// TODO emit

private:
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
    std::vector<Bonus*> bonuses;
    std::vector<BonusBody*> bonusbodies;
    int lives=1;
    Platform* platform;
    QTimer* MainGameTimer;
    QTimer* PlatformUpdateTimer;
    void Tick();
    void UpdatePlatform();

    int CurrentScore;

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

    void bonusCollision(BonusBody* bonus);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // GAMEFIELD_H
