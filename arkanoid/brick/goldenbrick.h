#ifndef GOLDENBRICK_H
#define GOLDENBRICK_H

#include "brick.h"

class GoldenBrick : public Brick
{
    Q_OBJECT

public:
    GoldenBrick(QVector2D pos);
};

#endif // GOLDENBRICK_H
