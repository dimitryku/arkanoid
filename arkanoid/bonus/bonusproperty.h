#ifndef BONUSPROPERTY_H
#define BONUSPROPERTY_H
#include <QVector2D>
#include <QPixmap>

class BonusProperty
{
public:
    BonusProperty();
    QPixmap* getPixMap(int num);

private:
    std::vector<QPixmap> pixmap;
};

#endif // BONUSPROPERTY_H
