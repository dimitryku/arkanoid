#include "ballstate.h"

BallState::BallState()
{
    //TODO
}

void BallState::MoveBall(QVector2D& currentPosition, QVector2D& currentSpeed, float platformX)
{
    switch (currentState) {
    case BallStates::magnet:
    {
        int diff = platformX - currentPosition.x();
        currentPosition.setX(currentPosition.x() + diff /* * multiplyer*/);
    }
        //no break!!!
    case BallStates::normal:
    case BallStates::uber:
        currentPosition += currentSpeed * multiplyer;
        break;
    }
}

void BallState::GetStatePower()
{
    //TODO
}

void BallState::ChangeState(BallStates newState)
{
    currentState = newState;
    //TODO mb sth more
}

BallStates BallState::GetCurrentState()
{
    return currentState;
}
