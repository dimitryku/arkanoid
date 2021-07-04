#include "bonus.h"

Bonus::Bonus(int positive_chance)
{
    srand(time(NULL));
    int type;
    if((rand()%100+1)<=positive_chance)
           type=rand()%7;
    else
           type=rand()%3+7;

    switch (type) {
        case 0: type_bonus = extend_platform;       break;
        case 1: type_bonus = plus_ball;             break;
        case 2: type_bonus = add_life;              break;
        case 3: type_bonus = stick_platform;        break;
        case 4: type_bonus = magnet_ball;           break;
        case 5: type_bonus = uber_ball;             break;
        case 6: type_bonus = slow_ball;             break;
        case 7: type_bonus = fast_ball;             break;
        case 8: type_bonus = inverse;               break;
        case 9: type_bonus = shorten_platform;      break;
    }
}

Bonus::Bonus(const Bonus &obj)
{
    this->type_bonus = obj.type_bonus;

}

Bonus::Bonus()
{
    int type;
    if((rand()%100+1)<=50)
           type=rand()%7;
    else
           type=rand()%3+7;

    switch (type) {
        case 0: type_bonus = extend_platform;       break;
        case 1: type_bonus = plus_ball;             break;
        case 2: type_bonus = add_life;              break;
        case 3: type_bonus = stick_platform;        break;
        case 4: type_bonus = magnet_ball;           break;
        case 5: type_bonus = uber_ball;             break;
        case 6: type_bonus = slow_ball;             break;
        case 7: type_bonus = fast_ball;             break;
        case 8: type_bonus = inverse;               break;
        case 9: type_bonus = shorten_platform;      break;
    }
}

Bonuses Bonus::getTypeBonus()
{
    return type_bonus;
}

Bonuses Bonus::start()
{
    timer=new QTimer(this);
    connect(timer, SIGNAL(&QTimer::timeout), this, SLOT(tick));
    switch(type_bonus){
    case extend_platform:   emit(this->increaseSizePlatform());         break;
    case plus_ball:         emit(this->addNewBall());                   break;
    case add_life:          emit(this->addLife());                      break;
    case stick_platform:    emit(this->changeStickness());              break;
    case magnet_ball:       emit(this->setMagnet());                    break;
    case uber_ball:         emit(this->setUberBall());                  break;
    case slow_ball:         emit(this->decreaseSpeedBall());            break;
    case fast_ball:         emit(this->increaseSpeedBall());            break;
    case inverse:           emit(this->changeInverse());                break;
    case shorten_platform:  emit(this->decreaseSizePlatform());         break;
    }
    timer->start(lifetime);
    return type_bonus;
}

void Bonus::operator =(const Bonus &obj)
{
    this->type_bonus = obj.type_bonus;
}

void Bonus::tick()
{
    switch (type_bonus) {
    case extend_platform:   emit(this->decreaseSizePlatform());               break;
    case stick_platform:    emit(this->changeStickness());                    break;
    case magnet_ball:       emit(this->setCommonBall());                      break;
    case uber_ball:         emit(this->setCommonBall());                      break;
    case inverse:           emit(this->changeInverse());                      break;
    case shorten_platform:  emit(this->increaseSizePlatform());               break;
    case slow_ball:         emit(this->increaseSpeedBall());                  break;
    case fast_ball:         emit(this->decreaseSpeedBall());                  break;
    }
    timer->stop();
}
