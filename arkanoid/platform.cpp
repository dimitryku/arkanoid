#include "platform.h"
#include "publicconstants.h"

Platform::Platform()
{
    this->position = PublicConstants::PlatformStartPoint;
    this->size = PublicConstants::PlatformSize;
    this->stepSpeed = PublicConstants::PlatformDefaultSpeed;
}

void Platform::stepLeft()
{
    position -= stepSpeed;
    float xmin = PublicConstants::PlatformMoveBounds.x();
    if(position.x() < xmin)
        position.setX(xmin);
}

void Platform::stepRight()
{
    position += stepSpeed;
    float xmax = PublicConstants::PlatformMoveBounds.y();
    if(position.x() > xmax)
        position.setX(xmax);
}

QVector2D Platform::getPosition()
{
    return this->position;
}


QRectF Platform::boundingRect() const
{
    return QRectF(position.x() - size.x()/2, position.y() - size.y()/2,
                  size.x(), size.y());
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::darkBlue));
    painter->drawRect(this->boundingRect());
}
