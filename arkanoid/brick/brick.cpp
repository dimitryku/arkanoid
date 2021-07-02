#include "brick/brick.h"

Brick::Brick()
{
    //TODO
    setHP(1);
    setPosition(QVector2D(0,0));
}

Brick::Brick(const Brick &brick)
{
    this->property=brick.property;
    this->HealPoints=brick.HealPoints;
    this->position=brick.position;
}

int Brick::getHP()
{
    return HealPoints;
}

QVector2D Brick::getPosition()
{
    return position;
}

//bool Brick::hasBonus()
//{
//    return bonus_flag;
//}

void Brick::setHP(int hp)
{
    if(hp>0)
        HealPoints=hp;
    else
        hp=1;
}

void Brick::setPosition(QVector2D position)
{
    this->position=position;
}

//void Brick::setBonus_flag(bool hasB)
//{
//    bonus_flag=hasB;
//}

void Brick::hit(int hp)
{
    HealPoints-=hp;
        if(HealPoints==0)
             emit(destroyed(this));

}

BrickProperty* Brick::getProperty(){
    return property;
}
