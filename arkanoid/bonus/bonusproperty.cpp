#include "bonusproperty.h"

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
    if(num < 0)
        num = 0;
    return &pixmap[num];
}
