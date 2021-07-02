#ifndef PUBLICCONSTANTS_H
#define PUBLICCONSTANTS_H

#include <QVector2D>


class PublicConstants
{
public:
    static QVector2D PlatformStartPoint = QVector2D(10, 10);
    static QVector2D PlatformSize = QVector2D(10, 80);
    static QVector2D PlatformDefaultSpeed = QVector2D(10, 0);
    // x - left, y - right bounds of platform center by x coordinate
    static QVector2D PlatformMoveBounds = QVector2D(0, 20);
    static QVector2D BallSize = QVector2D(10, 10);
    static QVector2D PlatformBallOffset = PlatformSize.x/2 + BallSize.x/2;
};

#endif // PUBLICCONSTANTS_H
