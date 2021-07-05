#include "gamefield.h"
#include <iostream>


GameField::GameField()
{
    CurrentScore = 0;
    scene = new QGraphicsScene();
    scene->setSceneRect(PublicConstants::SceneRect); // ограничивает сцену
    this->setFixedHeight(PublicConstants::SceneRect.height());
    this->setFixedWidth(PublicConstants::SceneRect.width());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap* map1 = new QPixmap(":/space");
    scene->setBackgroundBrush(QBrush(*map1));

    platform = new Platform();
    srand(time(NULL));

    //TODO привести скорость к какой-то одной, рандомизировать направление.
    balls.push_back(new Ball(QVector2D(3, 3), QVector2D(3, 3), true)); // make ball
    balls[0]->moveOneStep(platform->getPosition().x()); // move to platform

    BrickBuilder builder(10);
    bricks = builder.makeBricks();

    for(size_t i = 0; i < bricks.size(); i++){
            QString type_brick=bricks[i]->metaObject()->className();
            if(type_brick.contains("MetallicBrick"))
                amountMetallicBricks++;
            connect(bricks[i],SIGNAL(destroyed(Brick*)),this,SLOT(brickDestoryed(Brick*)));
            scene->addItem(bricks[i]);
    }
    for(size_t i = 0; i < balls.size(); i++)
        scene->addItem(balls[i]);
    scene->addItem(platform);
    //TODO the rest

    this->setScene(scene);
    bonusProp = new BonusProperty();

    MainGameTimer = new QTimer(this);
    connect(MainGameTimer, &QTimer::timeout, this, QOverload<>::of(&GameField::Tick));
    MainGameTimer->start(PublicConstants::DefaultTimerTick);

    PlatformUpdateTimer = new QTimer(this);
    connect(PlatformUpdateTimer, &QTimer::timeout, this, QOverload<>::of(&GameField::UpdatePlatform));
    PlatformUpdateTimer->start(PublicConstants::DefaultTimerTick);
}

int GameField::getScore()
{
    return CurrentScore;
}

int GameField::getLives()
{
    return lives;
}

void GameField::brickDestoryed(Brick *brick)
{
    QString type_brick=brick->metaObject()->className();
    Bonus* bonus=NULL;
    BonusBody* body=NULL;
    if(type_brick.contains("CommonBrick")){
        CurrentScore += 1;
        if(rand() % 100 + 1 <= 35){
             bonus = new Bonus(50);
        }

    } else if(type_brick.contains("GoldenBrick")){
        CurrentScore += 5;
            bonus = new Bonus(100);
    } else if(type_brick.contains("TNTBrick")){
        CurrentScore += 3;
            qreal x, y, w, h;
            brick->boundingRect().getRect(&x, &y, &w, &h);
            QRect boomRect = QRect(x - w, y - h, w * 3, h * 3);
            scene->removeItem(brick);
            scene->invalidate(brick->boundingRect());
            bricks.erase(std::remove(bricks.begin(), bricks.end(), brick), bricks.end());
            delete brick;
            QList<QGraphicsItem*> boomItems = scene->items(boomRect, Qt::IntersectsItemShape);
            for(int i = 0; i < boomItems.size(); i++)
            {
                if(boomItems[i] != nullptr)
                {
                    QString type = typeid(*boomItems[i]).name();
                    if (type.contains("Brick"))
                    {
                        if(((Brick*)boomItems[i])->getPosition() != brick->getPosition())
                            ((Brick*)boomItems[i])->hit(50);
                    }
                }
            }
            return; // because there are no bonuses and it's already deleted
    }
    scene->removeItem(brick);
    scene->invalidate(brick->boundingRect());
    bricks.erase(std::remove(bricks.begin(), bricks.end(), brick), bricks.end());
    delete brick;

    if(bonus != NULL){
        body = new BonusBody(brick->getPosition(), bonus, bonusProp);
        scene->addItem(body);
        bonusbodies.push_back(body);
    }

    if(bricks.size()==amountMetallicBricks)
    {
        for(int i=bricks.size(); i>=0;i--)
        {
            scene->removeItem(bricks[i]);
            scene->invalidate(brick->boundingRect());
            bricks.erase(std::remove(bricks.begin(), bricks.end(), bricks[i]), bricks.end());
            delete bricks[i];
        }
        bricks.clear();
        BrickBuilder builder(10);
        bricks = builder.makeBricks();

        for(size_t i = 0; i < bricks.size(); i++){
                QString type_brick=bricks[i]->metaObject()->className();
                if(type_brick.contains("MetallicBrick"))
                    amountMetallicBricks++;
                connect(bricks[i],SIGNAL(destroyed(Brick*)),this,SLOT(brickDestoryed(Brick*)));
                scene->addItem(bricks[i]);
        }
    }
    //std::cout<<bonuses.size()<<std::endl;

}

void GameField::Tick()
{
    ///Temporary here
    for(auto* x : bonusbodies)
    {
        x->Move();
        if(x->collidesWithItem(platform))
        {
            scene->removeItem(x);
            scene->invalidate(x->boundingRect().marginsAdded(QMargins(1, 900, 1, 900)));
            bonusCollision(x);
//            bonuses.push_back(x->getBonus());
//            x->getBonus()->start();
//            bonusbodies.erase(std::remove(bonusbodies.begin(), bonusbodies.end(), x), bonusbodies.end());
            continue;
        }
        scene->invalidate(x->boundingRect().marginsAdded(QMargins(1, 900, 1, 900)));
    }
    ///Temporary here


    // do a barrel roll
    //this->rotate(1);

    if(balls.size() < 1)
        if(lives < 2)
        {
            CurrentPlatformAction = PlatformAction::None;
            MainGameTimer->stop();
            PlatformUpdateTimer->stop();

            emit(GameEnded());
        }
        else{
            lives--;
            balls.push_back(new Ball(QVector2D(3, 3), QVector2D(3, 3), true)); // make ball
            balls[balls.size()-1]->moveOneStep(platform->getPosition().x()); // move to platform
            scene->addItem(balls[balls.size()-1]);
        }

    //ball move and bounce
    for(size_t i = 0; i < balls.size(); i++)
    {
        QVector2D newPos = balls[i]->moveOneStep(platform->getPosition().x());
        if(newPos.y() >= PublicConstants::SceneRect.height() - 10)
        {

            balls[i]->collide(Direction::up, true);
            balls[i]->moveOneStep(platform->getPosition().x());
            balls[i]->drop();
            scene->removeItem(balls[i]);
            balls.erase(balls.begin() + i);
        }
        else
        {
            if(newPos.x() + PublicConstants::BallSize.x() / 2 >= PublicConstants::SceneRect.width()
                    || newPos.x() + PublicConstants::BallSize.x() / 2 <= 0)
            {
                balls[i]->collide(Direction::right, true);   // left == right, doesn't matter here
                balls[i]->moveOneStep(platform->getPosition().x());
            }

            if(newPos.y() - PublicConstants::BallSize.y() / 2 < 0)
            {
                balls[i]->collide(Direction::up, true);
                balls[i]->moveOneStep(platform->getPosition().x());
            }
            ballCollision(balls[i]);
        }

    }

    ///TODO bonuces

    for(auto* x: balls)
        scene->invalidate(x->boundingRect()
                          .marginsAdded(QMargins(30,30,30,30)));

    /// TODO invalidate bonus bodies
    //for(auto x: bon)
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
        /// TODO change temp
        if(balls.size() > 0)
        {
            balls[0]->startMoving();
        }
        break;
    default:
        break;
    }

    scene->invalidate(QRectF(0, PublicConstants::SceneRect.height()-35,
                             PublicConstants::SceneRect.width(), PublicConstants::SceneRect.height()));
}

//Checking and performing collision of ball with the other objects
void GameField::ballCollision(Ball *ball)
{
    if(ball->getPosition().y() > PublicConstants::SceneRect.height() - 25)
    {
        if(ball->collidesWithItem(platform))
        {
            ball->collideWithPlatform(platform);
            ball->moveOneStep(platform->getPosition().x());
            //balls.push_back(new Ball(QVector2D(ball->getPosition().x(),ball->getPosition().y()), QVector2D(rand()%10 - 5, rand()%10 - 5), false));
            //scene->addItem(balls[balls.size() - 1]);
        }
        else
            if(ball->getPosition().y() > platform->getPosition().y())
                ball->drop();
    }
    else
    {
        //QList<QGraphicsItem*> collided = scene->items(ball->shape(), Qt::IntersectsItemShape);
        QList<QGraphicsItem*> collided = scene->collidingItems(ball);
        for(int j = 0; j < collided.size(); j++)
        {
            QString type = typeid(*collided[j]).name();
            if (type.contains("Brick"))
            {
                ((Brick*)collided[j])->hit(ball->getPower());
                //scene->invalidate(((Brick*)collided[j])->boundingRect());
                QVector2D dist = ball->getPosition() - ((Brick*)collided[j])->getPosition();
                float angle = abs(asin(dist.x() / dist.length()));
                if(angle < 45)
                    ball->collide(Direction::up);
                else
                    ball->collide(Direction::left);
                ball->moveOneStep(platform->getPosition().x());
                break;
            }
        }
    }
}

void GameField::bonusCollision(BonusBody *bonusbody)
{


    switch (bonusbody->getBonus()->getTypeBonus()) {
        case Bonuses::shorten_platform:
             CurrentScore+=25;
        case Bonuses::extend_platform:
             CurrentScore+=25;
             connect(bonusbody->getBonus(), SIGNAL(increaseSizePlatform(bool)), this, SLOT(increaseSizePlatform(bool)));
             connect(bonusbody->getBonus(), SIGNAL(decreaseSizePlatform(bool)), this, SLOT(decreaseSizePlatform(bool)));
             break;

        case Bonuses::fast_ball:
            CurrentScore+=25;
        case Bonuses::slow_ball:
            CurrentScore+=25;
            connect(bonusbody->getBonus(), SIGNAL(increaseSpeedBall()), this, SLOT(increaseSpeedBall()));
            connect(bonusbody->getBonus(), SIGNAL(decreaseSpeedBall()), this, SLOT(decreaseSpeedBall()));
            break;

        case Bonuses::inverse:
            CurrentScore+=50;
            connect(bonusbody->getBonus(), SIGNAL(changeInverse()), this, SLOT(changeInverse()));
            break;

        case Bonuses::add_life:
            CurrentScore+=25;
            connect(bonusbody->getBonus(), SIGNAL(addLife()), this, SLOT(addLife()));
            break;

        case Bonuses::plus_ball:
            CurrentScore+=25;
            connect(bonusbody->getBonus(), SIGNAL(addNewBall()), this, SLOT(addBall()));
            break;

        case Bonuses::uber_ball:
            CurrentScore+=25;
            connect(bonusbody->getBonus(), SIGNAL(setUberBall()), this, SLOT(setUberBall()));
            connect(bonusbody->getBonus(), SIGNAL(setCommonBall()), this, SLOT(setCommonBall()));
            break;

        case Bonuses::magnet_ball:
            CurrentScore+=25;
            connect(bonusbody->getBonus(), SIGNAL(setMagnet()), this, SLOT(setMagnetBall()));
            connect(bonusbody->getBonus(), SIGNAL(setCommonBall()), this, SLOT(setCommonBall()));
            break;
        case Bonuses::stick_platform:
            break;
    }
     connect(bonusbody->getBonus(),SIGNAL(stop(Bonus*)), this, SLOT(finishedBonus(Bonus*)));
     bonuses.push_back(bonusbody->getBonus());
     bonusbody->getBonus()->start();

     bonusbodies.erase(std::remove(bonusbodies.begin(), bonusbodies.end(), bonusbody), bonusbodies.end());
     //disconnect(bonusbody);

     //delete bonusbody;
}

void GameField::increaseSizePlatform(bool finished)
{

    platform->changeSize(PublicConstants::sizePlatformMultiplier_inc, finished);
}

void GameField::decreaseSizePlatform(bool finished)
{
    platform->changeSize(PublicConstants::sizePlatformMultiplier_dec,finished);
}

void GameField::increaseSpeedBall()
{

    for(size_t i = 0; i < balls.size(); i++){
        balls[i]->changeSpeed(PublicConstants::speedBallMultiplyier_inc);
    }
}

void GameField::decreaseSpeedBall()
{

    for(size_t i = 0; i < balls.size(); i++){
        balls[i]->changeSpeed(PublicConstants::speedBallMultiplyier_dec);
    }
}

void GameField::changeInverse()
{

    platform->changeInverse();
}

void GameField::addLife(){

    lives++;

}

void  GameField::addBall(){
    std::vector<Ball*> newballs;
    for(auto* ball: balls){
        newballs.push_back(new Ball(ball->getPosition(),
                                    QVector2D(0 - ball->getSpeed().x(),
                                              0 - ball->getSpeed().y()), false)); // make ball
    }

    for(auto* newball: newballs){
        balls.push_back(newball);
        scene->addItem(newball);
    }
}

void GameField::setUberBall(){
    for(size_t i = 0; i < balls.size(); i++){
        balls[i]->changeState(BallStates::uber);
    }

}

void GameField::setMagnetBall(){
    for(size_t i = 0; i < balls.size(); i++){
        balls[i]->changeState(BallStates::magnet);
    }
}

void GameField::setCommonBall(){
    for(size_t i = 0; i < balls.size(); i++){
        balls[i]->changeState(BallStates::normal);
    }
}

void GameField::finishedBonus(Bonus* bonus){
     std::cout<<"Finish"<<std::endl;
      disconnect(bonus);
      bonuses.erase(std::remove(bonuses.begin(), bonuses.end(), bonus), bonuses.end());
      delete bonus;
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
