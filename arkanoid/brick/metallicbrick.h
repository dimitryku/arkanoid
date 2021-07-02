#ifndef METALLICBRICK_H
#define METALLICBRICK_H
#include <brick/brick.h>

class MetallicBrick : public Brick
{
    Q_OBJECT

public:
    MetallicBrick(QVector2D position);
};

#endif // METALLICBRICK_H
