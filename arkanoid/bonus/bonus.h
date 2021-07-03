#ifndef BONUS_H
#define BONUS_H
#include <bonus/bonuses.h>
#include <random>
#include <time.h>
class Bonus
{
public:
    Bonus(int positive_chance);
    Bonuses getTypeBonus();
private:
    Bonuses type_bonus;
};

#endif // BONUS_H
