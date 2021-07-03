#ifndef BALL_H
#define BALL_H
#include <QVector2D>
#include <ball/ballstate.h>
#include <QGraphicsItem>
#include <QPainter>
#include "platform.h"

class Ball : public QGraphicsItem
{
public:
    Ball();
    //TODO check startSpeed
    Ball(QVector2D startPosition, QVector2D startSpeed = QVector2D(0, 0),
         bool onPlatform = false, BallState* state = nullptr); //mb change onPlatform

    void changeState(BallStates state = BallStates::normal);
    QVector2D moveOneStep(float platformX);                                     // returns Vector - end position

    //use it to return
    void collide(Direction direction, bool forcedBounce = false);               //recalculate speed
    void collideWithPlatform(Platform &platform);                               //recalculate speed
    QVector2D followPlatform(/*Platform &platform or QVector2D moveDelta*/);    // returns Vector - end position
    void startMoving(); //start from Platform
    QVector2D getPosition();
    int getPower();
    //TODO Исправить полет по горизонтали

private:
    QVector2D currentPosition;
    bool isOnPlatform;
    QVector2D currentSpeed;
    BallState* currentBallState;
    QPainterPath itemShape;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // BALL_H
