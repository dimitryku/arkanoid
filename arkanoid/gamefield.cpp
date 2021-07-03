#include "gamefield.h"


GameField::GameField()
{
    scene = new QGraphicsScene();
    //scene->setSceneRect(0, 0, 1000, 900); // ограничивает сцену
    //TODO scene size and rules
    //TODO background

    platform = new Platform();
    srand(time(NULL));
    //TODO привести скорость к какой-то одной, рандомизировать направление.
    balls.push_back(new Ball(QVector2D(25,25), QVector2D(rand() % 20 - 10, rand() % 10), true));
    balls[0]->moveOneStep(platform->getPosition().x()); //move to platform

    BrickBuilder builder(4, 4);
    bricks = builder.makeBricks();

    scene->addItem(platform);
    scene->addItem(balls[0]);
    for(int i = 0; i < bricks.size(); i++)
        scene->addItem(bricks[i]);

    //TODO the rest

    this->setScene(scene);

    MainGameTimer = new QTimer(this);
    connect(MainGameTimer, &QTimer::timeout, this, QOverload<>::of(&GameField::Tick));
    MainGameTimer->start(PublicConstants::DefaultTimerTick);
}

void GameField::Tick()
{
    // do a barrel roll
}
