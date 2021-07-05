#include "platform.h"
#include "publicconstants.h"

Platform::Platform()
{
    this->position = PublicConstants::PlatformStartPoint;
    this->size = PublicConstants::PlatformSize;
    this->stepSpeed = PublicConstants::PlatformDefaultSpeed;
    this->itemShape.addRoundedRect(this->boundingRect(), 10, 10);
    this->bounds = PublicConstants::PlatformMoveBounds;
}

void Platform::stepLeft()
{
    position -= stepSpeed;
    float xmin = bounds.x();
    float xmax = bounds.y();
    if(position.x() < xmin)
        position.setX(xmin);
    if(position.x() > xmax)
        position.setX(xmax);
}

void Platform::stepRight()
{
    position += stepSpeed;
    float xmax = bounds.y();
    float xmin = bounds.x();
    if(position.x() > xmax)
        position.setX(xmax);
    if(position.x() < xmin)
            position.setX(xmin);
}

void Platform::setSize(QVector2D newSize)
{
    this->size = newSize;
}

QVector2D Platform::getSize()
{
    return this->size;
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
    painter->setBrush(QBrush(Qt::lightGray));
    painter->drawRoundedRect(this->boundingRect(), 10, 10);
}


QPainterPath Platform::shape()
{
    itemShape.moveTo(position.x(), position.y());
    return itemShape;
}

void Platform::changeSize(float multiplier, bool finished)
{
    float mult=size.x()*multiplier;
    if(finished){
        if(mult<size.x()&&counts_increase_decrease.x()>0){
            counts_increase_decrease.setX(counts_increase_decrease.x()-1);
            return ;
         } else if(mult>size.x()&&counts_increase_decrease.y()>0){
            counts_increase_decrease.setY(counts_increase_decrease.y()-1);
            return ;
         }
    }
    else if(mult>=PublicConstants::SceneRect.width()){
        counts_increase_decrease.setX(counts_increase_decrease.x()+1);
        return ;
    }
    else if(mult<=10){
        counts_increase_decrease.setY(counts_increase_decrease.y()+1);
        return ;
    }
    size.setX(mult);
    bounds=QVector2D(size.x() / 2, PublicConstants::SceneRect.width() - size.x() / 2);

}

void Platform::changeInverse()
{
    stepSpeed*=(-1);
}


