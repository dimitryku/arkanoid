#ifndef BRICKBUILDER_H
#define BRICKBUILDER_H
#include <brick/brick.h>
#include <QVector2D>
#include <vector>
#include <random>
#include <time.h>
#include <brick/commonbrick.h>
#include <brick/goldenbrick.h>
#include <brick/metallicbrick.h>
#include <brick/tntbrick.h>
#include <publicconstants.h>
class BrickBuilder
{
public:
    BrickBuilder(int row, int col=0);
    Brick* makeBrick();
    std::vector<Brick*> makeBricks(int quantity = -1);
    void reset();

private:
    //Brick brick;
    bool not_metallic=false;
    QVector2D coord;
    int num_lastRow;
    int num_lastColum;
};

#endif // BRICKBUILDER_H
