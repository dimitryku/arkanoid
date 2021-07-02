#include "gamefield.h"

GameField::GameField()
{
    //TODO
    Ball* ball = new Ball(QVector2D(25,25), QVector2D(10,10));
    Ball* ball1 = new Ball(QVector2D(100,100), QVector2D(100,100));

    scene = new QGraphicsScene();
    scene->addItem(ball);
    scene->addItem(ball1);
    this->setScene(scene);
    for(int i = 0; i < 10; i++)
    {
        ball->moveOneStep(0);
    }

}
