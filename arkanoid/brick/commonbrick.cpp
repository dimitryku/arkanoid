#include "commonbrick.h"

CommonBrick::CommonBrick(QVector2D pos, int hp)
{
    int chance_bon=rand()%3+1;
    setPosition(pos);
    setHP(hp);

//    if(chance_bon==1)
//        //setBonus_flag(true);
//    else
//        //setBonus_flag(false);


}
