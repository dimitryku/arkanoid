#include "gamefield.h"

GameField::GameField()
{
    //TODO
    Ball* ball = new Ball(QVector2D(25,25), QVector2D(0,0), true);
    Ball* ball1 = new Ball(QVector2D(100,100), QVector2D(100,100));
    platform = new Platform();
    scene = new QGraphicsScene();
    scene->addItem(platform);
    scene->addItem(ball);
    ball->moveOneStep(platform->getPosition().x());
    scene->addItem(ball1);
    this->setScene(scene);
}
