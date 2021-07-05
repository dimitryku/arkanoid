#ifndef BONUSBODY_H
#define BONUSBODY_H
#include <bonus/bonusproperty.h>
#include <QGraphicsItem>
#include <QVector2D>
#include "bonus.h"
#include "publicconstants.h"
#include <QPainter>



class BonusBody : public QGraphicsItem
{
private:
    Bonus* bonusInside;
    QVector2D position;
    QPainterPath itemShape;
    BonusProperty* property;
public:
    BonusBody(QVector2D pos, Bonus* insideBonus, BonusProperty* prop);
    void Move();
    Bonus* getBonus();
    QPainterPath shape();
    QVector2D getPosition();
    void drop();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BONUSBODY_H
