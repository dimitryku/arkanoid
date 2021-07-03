#include "gamefield.h"


GameField::GameField()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(PublicConstants::SceneRect); // ограничивает сцену
    //TODO scene size and rules
    //TODO background

    platform = new Platform();
    srand(time(NULL));
    //TODO привести скорость к какой-то одной, рандомизировать направление.
    //temp:
    balls.push_back(new Ball(QVector2D(3,3), QVector2D(3, 3), false));
    //balls.push_back(new Ball(QVector2D(3,3), QVector2D(3, 3), true)); // make ball
    //balls[0]->moveOneStep(platform->getPosition().x()); // move to platform

    BrickBuilder builder(4);
    bricks = builder.makeBricks();
    //scene->addItem(platform);

    for(int i = 0; i < balls.size(); i++)
        scene->addItem(balls[i]);
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

    // do platform?

    //ball bounsing
    for(int i = 0; i < balls.size(); i++)
    {
        QVector2D newPos = balls[i]->moveOneStep(platform->getPosition().x());
        if(newPos.y() + PublicConstants::BallSize.y() / 2 >= PublicConstants::SceneRect.height())
        {
            //TODO delete ball
            //temp:
            balls[i]->collide(Direction::down, true);
            balls[i]->moveOneStep(platform->getPosition().x());
            balls.push_back(new Ball(QVector2D(rand()%500 + 15,rand()%500 + 15), QVector2D(rand()%10, rand()%10), false));
            scene->addItem(balls[balls.size() - 1]);
        }
        else
        {
            if(newPos.x() + PublicConstants::BallSize.x() / 2 >= PublicConstants::SceneRect.width()
                    || newPos.x() + PublicConstants::BallSize.x() / 2 <= 0)
            {
                balls[i]->collide(Direction::right, true);   // left == right, doesn't matter here
                balls[i]->moveOneStep(platform->getPosition().x());
            }

            if(newPos.y() + PublicConstants::BallSize.y() / 2 <= 0)
            {
                balls[i]->collide(Direction::up, true);
                balls[i]->moveOneStep(platform->getPosition().x());
            }
        }
    }


    // check collision
    // do sth

    scene->invalidate(PublicConstants::SceneRect);
}
