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
        case 8: type_bonus = iverse;                break;
        case 9: type_bonus = shorten_platform;      break;
    }
}

Bonuses Bonus::getTypeBonus()
{
    return type_bonus;
}
