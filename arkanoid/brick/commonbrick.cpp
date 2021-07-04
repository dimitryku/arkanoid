#include "commonbrick.h"

CommonBrick::CommonBrick(QVector2D pos, int hp)
{

    setPosition(pos);
    setHP(hp);
    this->itemShape.addRect(boundingRect());
    typeNum = 0;
//    if(chance_bon==1)
//        //setBonus_flag(true);
//    else
//        //setBonus_flag(false);


}
