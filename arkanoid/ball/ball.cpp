#include "ball.h"
#include <math.h>


Ball::Ball()
{
    //TODO maybe
}

Ball::Ball(QVector2D startPosition, QVector2D startSpeed,
           bool onPlatform, BallState* state)
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

    itemShape.addEllipse(boundingRect());

    //TODO update if needs
    // test
    // test 2
}

void Ball::changeState(BallStates newState)
{
    currentBallState->changeState(newState);
    //TODO mb sth more later
}

QVector2D Ball::moveOneStep(float platformX)
{
    currentBallState->moveBall(currentPosition, currentSpeed, isOnPlatform, platformX);
    return currentPosition;
}

void Ball::collide(Direction direction, bool forcedBounce)
{
    currentBallState->collide(direction, currentSpeed, forcedBounce);
}

void Ball::collideWithPlatform(Platform* platform)
{
    this->collide(Direction::down, true);
}


void Ball::startMoving()
{
    isOnPlatform = false;
    //TODO after Platform
}

QVector2D Ball::getPosition()
{
    return currentPosition;
}

QVector2D Ball::getSpeed()
{
    return currentSpeed;
}

int Ball::getPower()
{
    return currentBallState->getStatePower();
}

void Ball::drop()
{
    currentPosition.setY(currentPosition.y() + 50);
}

void Ball::changeSpeed(float multiplier)
{
    currentSpeed*=multiplier;
}

QRectF Ball::boundingRect() const
{
    return QRectF(currentPosition.x()-5, currentPosition.y()-5, 10, 10);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(this->boundingRect());
}


QPainterPath Ball::shape()
{
    itemShape.moveTo(currentPosition.x(), currentPosition.y());
    return itemShape;
}
