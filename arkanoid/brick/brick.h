#ifndef BRICK_H
#define BRICK_H
#include <QVector2D>
#include <brick/brickproperty.h>

//abstract?
class Brick
{
public:
    Brick();

private:
    QVector2D position;
    int HealPoints;
    BrickProperty* property;

};

#endif // BRICK_H
