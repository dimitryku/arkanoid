#include "gamefield.h"
#include <iostream>


GameField::GameField()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(PublicConstants::SceneRect); // ограничивает сцену
    this->setFixedHeight(PublicConstants::SceneRect.height());
    this->setFixedWidth(PublicConstants::SceneRect.width());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //TODO background

    platform = new Platform();
    srand(time(NULL));
    //TODO привести скорость к какой-то одной, рандомизировать направление.
    //temp:
    balls.push_back(new Ball(QVector2D(500, 500), QVector2D(3, 3), false));
    //balls.push_back(new Ball(QVector2D(3,3), QVector2D(3, 3), true)); // make ball
    //balls[0]->moveOneStep(platform->getPosition().x()); // move to platform

    BrickBuilder builder(10);
    bricks = builder.makeBricks();

    for(size_t i = 0; i < bricks.size(); i++){
            connect(bricks[i],SIGNAL(destroyed(Brick*)),this,SLOT(generateBonus(Brick*)));
            scene->addItem(bricks[i]);
    }
    for(size_t i = 0; i < balls.size(); i++)
        scene->addItem(balls[i]);
    scene->addItem(platform);
    //TODO the rest

    this->setScene(scene);

    MainGameTimer = new QTimer(this);
    connect(MainGameTimer, &QTimer::timeout, this, QOverload<>::of(&GameField::Tick));
    MainGameTimer->start(PublicConstants::DefaultTimerTick);

    PlatformUpdateTimer = new QTimer(this);
    connect(PlatformUpdateTimer, &QTimer::timeout, this, QOverload<>::of(&GameField::UpdatePlatform));
    PlatformUpdateTimer->start(PublicConstants::DefaultTimerTick);
}

void GameField::generateBonus(Brick *brick)
{
    std::cout<<brick->metaObject()->className()<<std::endl;

    QString type_brick=brick->metaObject()->className();

    Bonus* bonus=NULL;
    if(type_brick.compare("CommonBrick")){
        if(rand()%100+1<=45){
             bonus=new Bonus(50);
             std::cout<<bonus->getTypeBonus()<<std::endl;
        }


    } else if(type_brick.compare("GoldenBrick")){
             bonus=new Bonus(100);
             std::cout<<bonus->getTypeBonus()<<std::endl;


    } else if(type_brick.compare("TNTBrick")){
           //TODO call hit(50) nearby(boomsize)bricks
            std::cout<<"BOOM!"<<std::endl;
    }


    if(bonus!=NULL)
        bonuses.push_back(bonus);

    std::cout<<bonuses.size()<<std::endl;
}

void GameField::Tick()
{
    ///УДАЛИТЬ
     bricks[rand()%bricks.size()]->hit(1);
    ///УДАЛИТЬ


    // do a barrel roll
    // this->rotate(1);



    //ball move and bounce
    for(size_t i = 0; i < balls.size(); i++)
    {
        QVector2D newPos = balls[i]->moveOneStep(platform->getPosition().x());
        if(newPos.y() + PublicConstants::BallSize.y() / 2 >= PublicConstants::SceneRect.height())
        {
            //TODO delete ball
            //temp:
            if(balls.size() < 10)
            {
                balls[i]->collide(Direction::down, true);
                balls[i]->moveOneStep(platform->getPosition().x());
                balls.push_back(new Ball(QVector2D(balls[i]->getPosition().x(),balls[i]->getPosition().y()), QVector2D(rand()%10 - 5, rand()%10 - 5), false));
                scene->addItem(balls[balls.size() - 1]);
            }
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
        ballCollision(balls[i]);
    }

    ///TODO bonuces

    scene->invalidate(PublicConstants::SceneRect);
}

void GameField::UpdatePlatform()
{
    switch (CurrentPlatformAction) {
    case PlatformAction::MoveRight:
        platform->stepRight();
        break;
    case PlatformAction::MoveLeft:
        platform->stepLeft();
        break;
    case PlatformAction::Shoot:
        /// TODO
        break;
    default:
        break;
    }
}

//Checking and performing collision of ball with the other objects
void GameField::ballCollision(Ball *ball)
{
    QList<QGraphicsItem*> collided = scene->items(ball->boundingRect(), Qt::IntersectsItemShape);
    for(int j = 0; j < collided.size(); j++)
    {
        std::string type = typeid(*collided[j]).name();
        if (type.find("Brick") != std::string::npos)
        {
            ((Brick*)collided[j])->hit(ball->getPower());
            QVector2D dist = ball->getPosition() - ((Brick*)collided[j])->getPosition();
            float angle = abs(asin(dist.x() / dist.length()));
            if(angle < 45)
                ball->collide(Direction::up);
            else
                ball->collide(Direction::left);
            ball->moveOneStep(platform->getPosition().x());
            break;
        }

        if (type.find("Platform") != std::string::npos)
        {
            ball->collide(Direction::up, true);
            ball->moveOneStep(platform->getPosition().x());
        }
    }
}




void GameField::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Right:
        CurrentPlatformAction = PlatformAction::MoveRight;
        break;
    case Qt::Key_Left:
        CurrentPlatformAction = PlatformAction::MoveLeft;
        break;
    case Qt::Key_Space:
        CurrentPlatformAction = PlatformAction::Shoot;
        break;
    default:
        break;
    }
}


void GameField::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Space:
        CurrentPlatformAction = PlatformAction::None;
        break;
    default:
        break;
    }
}
