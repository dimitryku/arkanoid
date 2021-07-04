#ifndef BONUSBODY_H
#define BONUSBODY_H

#include <QGraphicsItem>
#include <QVector2D>
#include "bonus.h"
#include "publicconstants.h"
#include <QPainter>



class BonusBody : public QGraphicsItem
{
private:
    Bonus bonusInside;
    QVector2D position;
    QPainterPath itemShape;
public:
    BonusBody(QVector2D pos, Bonus insideBonus);
    void Move();
    Bonus getBonus();
    QPainterPath shape();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BONUSBODY_H
