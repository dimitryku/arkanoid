#ifndef BRICKBUILDER_H
#define BRICKBUILDER_H
#include <brick/brick.h>
#include <QVector2D>
#include <vector>
#include <random>
#include <time.h>
class BrickBuilder
{
public:
    BrickBuilder(int row, int col);
    Brick* makeBrick();
    std::vector<Brick> makeBricks(int quantity);
    void reset();

private:
    //Brick brick;
    bool not_metallic=false;
    QVector2D coord;
    int num_lastRow;
    int num_lastColum;
};

#endif // BRICKBUILDER_H
