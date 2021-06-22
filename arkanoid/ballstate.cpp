#include "ballstate.h"

BallState::BallState()
{
    currentState = BallStates::normal;                  //TODO append if necessary
}

void BallState::moveBall(QVector2D& currentPosition, QVector2D& currentSpeed, float platformX)
{
    switch (currentState) {
    case BallStates::magnet:
    {
        int diff = platformX - currentPosition.x();
        currentPosition.setX(currentPosition.x() + diff / 20.0);     //TODO adjust num
    }
        //no break!!!
    case BallStates::normal:
    case BallStates::uber:
        currentPosition += currentSpeed * multiplyer;
        break;
    }
}

int BallState::getStatePower()
{
    switch (currentState) {
        case BallStates::magnet:
        case BallStates::normal:
            return 1;
        break;
        case BallStates::uber:
            return 10;                              //TODO adjust
        break;
    }
    return 1;
}

void BallState::changeState(BallStates newState)
{
    currentState = newState;                        //TODO mb sth more
}

void BallState::collideWithBrick(/*Brick &brick*/)
{
    //TODO after brick
}

BallStates BallState::GetCurrentState()
{
    return currentState;
}
