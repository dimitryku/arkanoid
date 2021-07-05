#include "brick/brickproperty.h"
#include <iostream>

BrickProperty::BrickProperty()
{
    QPixmap pix = QPixmap(":/bricks");
    for(int i = 0; i < 6; i++)
    {
        pixmap.push_back(pix.copy(80 * i, 0, 80, 30));
    }
    // normal   // golden   // steel    // tnt  // forced
    for(int i = 0; i < pixmap.size(); i++)
    {
        pixmap[i] = pixmap[i].scaled(40, 15);
    }
}

QPixmap *BrickProperty::getPixMap(int num)
{
    if(num < 0)
        num = 0;
    return &pixmap[num];
}

