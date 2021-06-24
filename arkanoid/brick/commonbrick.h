#ifndef COMMONBRICK_H
#define COMMONBRICK_H
#include <brick\brick.h>

class CommonBrick : public Brick
{
public:
    CommonBrick(QVector2D pos, int hp);
};

#endif // COMMONBRICK_H
