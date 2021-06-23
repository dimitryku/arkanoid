#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <vector>
#include <ball/ball.h>

class GameField
{
public:
    GameField();

private:
    std::vector<Ball> balls;
    //std::vector<Brick> bricks;
    //Platform platform;
    //std::vector<Bonus> activeBonuses;
    //Score score
    //std::vector<BonusBody> fallingBonuses
};

#endif // GAMEFIELD_H
