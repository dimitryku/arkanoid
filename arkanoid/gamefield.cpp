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
            connect(bricks[i],SIGNAL(destroyed(Brick*)),this,SLOT(brickDestoryed(Brick*)));
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

int GameField::GetScore()
{
    return CurrentScore;
}

void GameField::brickDestoryed(Brick *brick)
{
    QString type_brick=brick->metaObject()->className();

    Bonus* bonus=NULL;
    BonusBody* body=NULL;
    if(type_brick.compare("CommonBrick")){
        CurrentScore += 1;
        if(rand() % 100 + 1 <= 45){
             bonus = new Bonus(50);
             std::cout<<bonus->getTypeBonus()<<std::endl;
        }

    } else if(type_brick.compare("GoldenBrick")){
        CurrentScore += 5;
            bonus = new Bonus(100);

    } else if(type_brick.compare("TNTBrick")){
        CurrentScore += 3;
           //TODO call hit(50) nearby(boomsize)bricks
            qreal x, y, w, h;
            brick->boundingRect().getRect(&x, &y, &w, &h);
            QRect boomRect = QRect(x - w, y - h, w * 3, h * 3);
            QList<QGraphicsItem*> boomItems = scene->items(boomRect, Qt::IntersectsItemShape);
            for(int i = 0; i < boomItems.size(); i++)
            {
                QString type = typeid(boomItems[i]).name();
                if (type.contains("Brick"))
                {
                    ((Brick*)boomItems[i])->hit(50);
                }
            }
            std::cout<<"BOOM!"<<std::endl;
    }
    scene->removeItem(brick);
    scene->invalidate(brick->boundingRect());
    bricks.erase(std::remove(bricks.begin(), bricks.end(), brick), bricks.end());
    delete brick;

    if(bonus!=NULL){
        body = new BonusBody(brick->getPosition(), bonus);
        bonusbodies.push_back(body);
    }
    //std::cout<<bonuses.size()<<std::endl;

}



void GameField::Tick()
{
    // do a barrel roll
    // this->rotate(1);

    if(balls.size() < 1){
        MainGameTimer->stop();
        PlatformUpdateTimer->stop();

        emit(GameEnded());
    }

    //ball move and bounce
    for(size_t i = 0; i < balls.size(); i++)
    {
        QVector2D newPos = balls[i]->moveOneStep(platform->getPosition().x());
        if(newPos.y() >= PublicConstants::SceneRect.height())
        {
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
        }
        ballCollision(balls[i]);
    }

    ///TODO bonuces

    for(auto* x: balls)
        scene->invalidate(x->boundingRect()
                          .marginsAdded(QMargins(30,30,30,30)));

    /// TODO invalidate bonus bodies
    //for(auto x: bon)

    //scene->invalidate(PublicConstants::SceneRect);
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

    scene->invalidate(QRectF(0, PublicConstants::SceneRect.height()-30,
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

//            if (type.find("Platform") != std::string::npos)
//            {
//                //std::cout << "platform" << std::endl;
//                ball->collide(Direction::up, true);
//                ball->moveOneStep(platform->getPosition().x());
//            }
        }
    }
}

void GameField::bonusCollision(BonusBody *bonusbody)
{
    switch (bonusbody->getBonus()->getTypeBonus()) {
    case Bonuses::extend_platform:
    case Bonuses::shorten_platform:{
         connect(bonusbody->getBonus(),SIGNAL(increaseSizePlatform), this, SLOT(this->increaseSizePlatform));
         connect(bonusbody->getBonus(),SIGNAL(decreaseSizePlatform), this, SLOT(this->decreaseSizePlatform));
         break;
    }

    case Bonuses::fast_ball:
    case Bonuses::slow_ball:{
        connect(bonusbody->getBonus(),SIGNAL(increaseSpeedBall), this, SLOT(this->increaseSpeedBall));
        connect(bonusbody->getBonus(),SIGNAL(increaseSpeedBall), this, SLOT(this->decreaseSpeedBall));
        break;
    }

    case Bonuses::inverse:
        connect(bonusbody->getBonus(),SIGNAL(changeInverse), this, SLOT(this->changeInverse));
        break;

    case Bonuses::add_life:
        connect(bonusbody->getBonus(),SIGNAL(addLife), this, SLOT(this->addLife));
        break;

    case Bonuses::plus_ball:
        connect(bonusbody->getBonus(),SIGNAL(addNewBall), this, SLOT(this->addBall));
        break;

    case Bonuses::uber_ball:{
        connect(bonusbody->getBonus(),SIGNAL(setUberBall), this, SLOT(this->setUberBall));
        connect(bonusbody->getBonus(),SIGNAL(setCommonBall), this, SLOT(this->setCommonBall));
    }

    case Bonuses::magnet_ball:{
        connect(bonusbody->getBonus(),SIGNAL(setMagnet), this, SLOT(this->setMagnetBall;));
        connect(bonusbody->getBonus(),SIGNAL(setCommonBall), this, SLOT(this->setCommonBall));
    }
    }
}



void GameField::increaseSizePlatform()
{
    platform->changeSize(PublicConstants::sizePlatformMultiplier_inc);
}

void GameField::decreaseSizePlatform()
{
    platform->changeSize(PublicConstants::sizePlatformMultiplier_dec);
}

void GameField::increaseSpeedBall()
{
    for(int i=0; i<balls.size(); i++){
        balls[i]->changeSpeed(PublicConstants::speedBallMultiplyier_inc);
    }
}

void GameField::decreaseSpeedBall()
{
    for(int i=0; i<balls.size(); i++){
        balls[i]->changeSpeed(PublicConstants::speedBallMultiplyier_dec);
    }
}

void GameField::changeInverse()
{
    platform->changeInverse();
}

void GameField::addLife(){

    //TODO увеличить количество жизней

}

void  GameField::addBall(){

     //TODO раздвоение шарика
}

void GameField::setUberBall(){

    for(int i=0; i<balls.size(); i++){
        balls[i]->changeState(BallStates::uber);
    }

}

void GameField::setMagnetBall(){
    for(int i=0; i<balls.size(); i++){
        balls[i]->changeState(BallStates::magnet);
    }
}

void GameField::setCommonBall(){
    for(int i=0; i<balls.size(); i++){
        balls[i]->changeState(BallStates::normal);
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
