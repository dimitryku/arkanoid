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

signals:
    void destroyed(Brick* brick);


private:
    QVector2D position;
    int HealPoints;
    BrickProperty* property;
//    bool bonus_flag;

protected:
    QPainterPath itemShape;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // BRICK_H
