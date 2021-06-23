#ifndef BALL_H
#define BALL_H
#include <QVector2D>
#include <ball/ballstate.h>

class Ball
{
    //TODO qt part of code (property ++)

public:
    Ball();
    //TODO check startSpeed
    Ball(QVector2D startPosition, QVector2D startSpeed = QVector2D(0, 0),
         BallState* state = nullptr, bool onPlatform = false); //mb change onPlatform

    void changeState(BallStates state = BallStates::normal);
    QVector2D moveOneStep(float platformX);                                     // returns Vector - end position

    //use it to return
    void collide(Direction direction, bool forcedBounce = false);               //recalculate speed
    void collideWithPlatform(/*Platform &platform*/);                           //recalculate speed
    QVector2D followPlatform(/*Platform &platform or QVector2D moveDelta*/);    // returns Vector - end position
    void startMoving(); //start from Platform
    int getCurrentPosition();
    int getCurrentPower();

private:
    QVector2D currentPosition;
    bool isOnPlatform;
    QVector2D currentSpeed;
    BallState* currentBallState;

};

#endif // BALL_H
