#include "brick/brickproperty.h"
#include <random>
#include <time.h>
BrickProperty::BrickProperty()
{
    srand(time(0));
    int a=1;
    sizes=QVector2D(rand()%a+1,rand()%a+1);
}
