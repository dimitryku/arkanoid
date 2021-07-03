#include "tntbrick.h"

TNTBrick::TNTBrick(QVector2D position)
{
    setPosition(position);
    setHP(1);
    this->itemShape.addRect(boundingRect());
    //setBonus_flag(false);
}
