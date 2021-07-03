#include "tntbrick.h"

TNTBrick::TNTBrick(QVector2D position)
{
    setPosition(position);
    setHP(1);
    boom_size=1;
    this->itemShape.addRect(boundingRect());
    //setBonus_flag(false);
}

int TNTBrick::getBoomsize()
{
    return boom_size;
}
