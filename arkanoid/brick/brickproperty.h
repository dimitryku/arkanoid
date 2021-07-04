#ifndef BRICKPROPERTY_H
#define BRICKPROPERTY_H
#include <QVector2D>
#include <QPixmap>

class BrickProperty
{
public:
    BrickProperty();
    QPixmap* getPixMap(int num);

private:
    std::vector<QPixmap> pixmap;
};

#endif // BRICKPROPERTY_H
