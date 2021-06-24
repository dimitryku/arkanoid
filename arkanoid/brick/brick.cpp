#include "brick/brick.h"

Brick::Brick()
{
    //TODO
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
//    if(HealPoints==0)
//        destroy();

}
