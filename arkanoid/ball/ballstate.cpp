#include "ballstate.h"
#include "publicconstants.h"

BallState::BallState()
{
    currentState = BallStates::normal;                  //TODO append if necessary
}

void BallState::moveBall(QVector2D& currentPosition, QVector2D& currentSpeed,
                         bool moveWithPlatform=false, float platformX=0)
{
    if(!moveWithPlatform)
        switch (currentState) {
        case BallStates::magnet:
        {
            int diff = platformX - currentPosition.x();
            currentPosition.setX(currentPosition.x() + diff / 40);     //TODO adjust number
        }
            //no break!!!
        case BallStates::normal:
        case BallStates::uber:
            currentPosition += currentSpeed * multiplyer;
            break;
        }
    else{ /// ball is laying on platform
        QVector2D newPos = PublicConstants::PlatformStartPoint;
        newPos.setX(platformX);
        newPos.setY(newPos.y() - PublicConstants::PlatformBallOffset);
        currentPosition.setX(newPos.x());
        currentPosition.setY(newPos.y());
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

void BallState::collide(Direction direction, QVector2D& curSpeed, bool forceBounce)
{
    switch (direction) {
    case Direction::up:
    case Direction::down:
        if(forceBounce || currentState != BallStates::uber)
            curSpeed.setY(curSpeed.y()*(-1));
        break;
    case Direction::left:
    case Direction::right:
        if(forceBounce || currentState != BallStates::uber)
            curSpeed.setX(curSpeed.x()*(-1));
        break;
    default:
        break;
    }
}

BallStates BallState::GetCurrentState()
{
    return currentState;
}
