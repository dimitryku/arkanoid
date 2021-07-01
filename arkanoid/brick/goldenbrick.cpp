#include "goldenbrick.h"

GoldenBrick::GoldenBrick(QVector2D pos)
{
    setPosition(pos);
    setHP(5); //Чтобы сразу бонус не получать, да и Золото явно крепче чем обычный кирпич
    //setBonus_flag(true);
}

