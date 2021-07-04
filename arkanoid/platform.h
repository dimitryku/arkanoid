#ifndef PLATFORM_H
#define PLATFORM_H
#include <QVector2D>
#include <QGraphicsItem>
#include <QPainter>


class Platform : public QGraphicsItem
{
public:
    Platform();
    void stepLeft();
    void stepRight();
    void setSize(QVector2D newSize);
    QVector2D getSize();
    QVector2D getPosition();
private:
    QVector2D position;
    QVector2D size;
    QVector2D stepSpeed;
    QPainterPath itemShape;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape();
};

#endif // PLATFORM_H
