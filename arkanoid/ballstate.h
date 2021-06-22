#ifndef BALLSTATE_H
#define BALLSTATE_H
#include <ballStates.h>
#include <QVector2D>

class BallState
{
public:
    BallState();
    void moveBall(QVector2D& currentPosition, QVector2D& currentSpeed, float platformX);
    int getStatePower();
    void changeState(BallStates newState);
    void collideWithBrick(/*Brick &brick*/);
    BallStates GetCurrentState();

private:
    BallStates currentState;
    float multiplyer = 1;               // to adjust speed

};

#endif // BALLSTATE_H
