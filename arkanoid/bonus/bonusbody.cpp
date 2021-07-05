#include "bonusbody.h"
#include <iostream>


BonusBody::BonusBody(QVector2D pos, Bonus* insideBonus, BonusProperty* prop)
{
    this->position = pos;
    this->bonusInside = insideBonus;
    this->property = prop;
    itemShape.addRect(boundingRect());
}

void BonusBody::Move()
{
    this->position += PublicConstants::BonusBodySpeed;
}

Bonus* BonusBody::getBonus()
{
    return this->bonusInside;
}

QPainterPath BonusBody::shape()
{
    QVector2D size = PublicConstants::BonusBodySize;
    itemShape.moveTo(position.x()- size.x()/2, position.y()-size.y()/2);
    return itemShape;
}

QVector2D BonusBody::getPosition()
{
    return position;
}


QRectF BonusBody::boundingRect() const
{
    QVector2D size = PublicConstants::BonusBodySize;
    return QRectF(position.x() - size.x()/2, position.y() - size.y()/2,
                  size.x(), size.y());
}

void BonusBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QPixmap(*(property->getPixMap((int)bonusInside->getTypeBonus())))));
    //painter->setBrush(QBrush(Qt::green));
    painter->drawRect(this->boundingRect());
}
