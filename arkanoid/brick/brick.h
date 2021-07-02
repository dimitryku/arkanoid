#ifndef BRICK_H
#define BRICK_H
#include <QVector2D>
#include <brick/brickproperty.h>
#include <random>
#include <QObject>
//abstract?
class Brick : public QObject
{

    Q_OBJECT

public:
    Brick();
    Brick(const Brick& brick);
    int getHP();
    QVector2D getPosition();
//    bool hasBonus();
    void setHP(int hp);
    void setPosition(QVector2D position);
//    void setBonus_flag(bool hasB);
    void hit(int hp);
    BrickProperty* getProperty();

signals:
    void destroyed(Brick* brick); //Если надо получить имя класса, попробовать brick->metaObject()->className();  Если будет выводить тоже самое, то ввести имя кирпича как поле класса
    //TODO destroy

private:
    QVector2D position;
    int HealPoints;
    BrickProperty* property;
//    bool bonus_flag;

};

#endif // BRICK_H
