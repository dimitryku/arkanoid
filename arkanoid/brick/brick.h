#ifndef BRICK_H
#define BRICK_H
#include <QVector2D>
#include <brick/brickproperty.h>
#include <random>
#include <QObject>
//abstract?
class Brick
{


public:
    Brick();
    int getHP();
    QVector2D getPosition();
//    bool hasBonus();
    void setHP(int hp);
    void setPosition(QVector2D position);
//    void setBonus_flag(bool hasB);
    void hit(int hp);

    //TO DO destroy

private:
    QVector2D position;
    int HealPoints;
    BrickProperty* property;
//    bool bonus_flag;

};

#endif // BRICK_H
