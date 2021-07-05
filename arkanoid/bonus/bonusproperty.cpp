#include "bonusproperty.h"
#include <iostream>

BonusProperty::BonusProperty()
{
    QPixmap pix = QPixmap(":/bonuses");
    for(int i = 0; i < 9; i++)
    {
        pixmap.push_back(pix.copy(i*20, 0, 20, 20));
    }
}

QPixmap *BonusProperty::getPixMap(int num)
{
    std::cout << num << std::endl;
    if(num < 0)
        num = 0;
    return &pixmap[num];
}
