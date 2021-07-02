#ifndef BALLSTATE_H
#define BALLSTATE_H
#include <ball/ballStates.h>
#include <QVector2D>
#include <direction.h>

class BallState
{
public:
    BallState();
    void moveBall(QVector2D& currentPosition, QVector2D& currentSpeed, bool moveWithPlatform, float platformX);
    int getStatePower();
    void changeState(BallStates newState);
    void collide(Direction direction, QVector2D& curSpeed, bool forceBounce = false);
    BallStates GetCurrentState();

private:
    BallStates currentState;
    float multiplyer = 1;               // to adjust speed

};

#endif // BALLSTATE_H
