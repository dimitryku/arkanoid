#ifndef PUBLICCONSTANTS_H
#define PUBLICCONSTANTS_H

#include <QVector2D>
#include <QRectF>


class PublicConstants
{
public:
    static const QVector2D PlatformStartPoint;
    static const QVector2D PlatformSize;
    static const QVector2D PlatformSizeExtended;
    static const QVector2D PlatformDefaultSpeed;
    // x - left, y - right bounds of platform center by x coordinate
    static const QVector2D PlatformMoveBounds;
    static const QVector2D BallSize;
    static const QVector2D BrickSize;
    static const QRectF SceneRect;
    static const float PlatformBallOffset;
};

#endif // PUBLICCONSTANTS_H
