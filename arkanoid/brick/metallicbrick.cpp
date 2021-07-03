#include "metallicbrick.h"

MetallicBrick::MetallicBrick(QVector2D position)
{
    setPosition(position);
    setHP(1500);
    this->itemShape.addRect(boundingRect());
}
