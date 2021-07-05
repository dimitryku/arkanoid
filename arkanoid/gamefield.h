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
    int getScore();
    int getLives();
    
public slots:
   void brickDestoryed(Brick* brick);
   void increaseSizePlatform();
   void decreaseSizePlatform();
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
    BonusProperty* bonusProp;
    int lives=2;
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
