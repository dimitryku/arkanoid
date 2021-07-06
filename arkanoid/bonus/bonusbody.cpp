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
    itemShape.moveTo(position.x(), position.y());
    return itemShape;
}

QVector2D BonusBody::getPosition()
{
    return position;
}

void BonusBody::drop()
{
    this->position.setY(position.y() + 50);
}


QRectF BonusBody::boundingRect() const
{
    QVector2D size = PublicConstants::BonusBodySize;
    return QRectF(position.x()/* - size.x()/2*/, position.y()/* - size.y()/2*/,
                  size.x(), size.y());
}

void BonusBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(QBrush(QPixmap(*(property->getPixMap((int)bonusInside->getTypeBonus())))));
    painter->setBrush(QBrush(Qt::transparent));
    //painter->setPen(Qt::darkGray);
    painter->drawRoundedRect(this->boundingRect(), 1, 1);
    painter->drawPixmap(this->boundingRect(), *(property->getPixMap(bonusInside->getTypeBonus())), QRectF(0, 0, 20, 20));
}
