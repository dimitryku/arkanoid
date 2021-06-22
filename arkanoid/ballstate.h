#ifndef BALLSTATE_H
#define BALLSTATE_H
#include <ballStates.h>
#include <QVector2D>

class BallState
{
public:
    BallState();
    void MoveBall(QVector2D& currentPosition, QVector2D& currentSpeed, float platformX);
    void GetStatePower();
    void ChangeState(BallStates newState);
    BallStates GetCurrentState();

private:
    BallStates currentState;
    float multiplyer = 1;               // to adjust speed

};

#endif // BALLSTATE_H
