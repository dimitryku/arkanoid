#ifndef TNTBRICK_H
#define TNTBRICK_H

#include "brick.h"

class TNTBrick : public Brick
{
    Q_OBJECT
private:
    int boom_size;

public:
    TNTBrick(QVector2D position);
    int getBoomsize();

};

#endif // TNTBRICK_H
