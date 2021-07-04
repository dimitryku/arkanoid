#ifndef BRICK_H
#define BRICK_H
#include <QVector2D>
#include <brick/brickproperty.h>
#include <random>
#include <QObject>
#include <QGraphicsItem>
#include <publicconstants.h>
#include <QPainter>

//abstract?
class Brick : public QObject, public QGraphicsItem
{

    Q_OBJECT
    //shape returns correctly by itself, because it is brick

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
    void setProp(BrickProperty* property);

signals:
    void destroyed(Brick* brick); //Если надо получить имя класса, попробовать brick->metaObject()->className();  Если будет выводить тоже самое, то ввести имя кирпича как поле класса
    //TODO destroy

private:
    QVector2D position;
    int HealPoints;
    BrickProperty* property;
//    bool bonus_flag;

protected:
    QPainterPath itemShape;
    int typeNum;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // BRICK_H
