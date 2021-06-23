#include "ball.h"


Ball::Ball()
{
    //TODO maybe
}

Ball::Ball(QVector2D startPosition, QVector2D startSpeed, BallState* state,
           bool onPlatform)
{
    currentPosition = startPosition;

    if(startSpeed.isNull())
    {
        currentSpeed = QVector2D(0, 0);
    }
    else
        currentSpeed = startSpeed;

    if(state == nullptr)
        currentBallState = new BallState();
    else
        currentBallState = state;

    isOnPlatform = onPlatform;

    //TODO update if needs
}

void Ball::changeState(BallStates newState)
{
    currentBallState->changeState(newState);
    //TODO mb sth more later
}

QVector2D Ball::moveOneStep(float platformX)
{
    currentBallState->moveBall(currentPosition, currentSpeed, platformX);
    currentPosition += currentSpeed;
    return currentPosition;
}

void Ball::collideWithBrick(Direction direction)
{
    currentBallState->collideWithBrick(direction, currentSpeed);
}

void Ball::collideWithWall(Direction direction)
{
    currentBallState->collideWithBrick(direction, currentSpeed, true);
}

void Ball::collideWithPlatform(/*Platform &platform*/)
{
    //TODO after platform
}

QVector2D Ball::followPlatform(/*Platform &platform or QVector2D moveDelta*/)
{
    //TODO if on platform...
        //TODO after input decision
    return currentPosition;
}

void Ball::startMoving()
{
    //TODO after Platform
}

int Ball::getCurrentPower()
{
    return currentBallState->getStatePower();
}
