#include "publicconstants.h"

const QVector2D PublicConstants::PlatformStartPoint = QVector2D(10.0f, 10.0f);
const QVector2D PublicConstants::PlatformSize = QVector2D(80.0f, 10.0f);
const QVector2D PublicConstants::PlatformDefaultSpeed = QVector2D(10.0f, 0.0f);
// x - left, y - right bounds of platform center by x coordinate
const QVector2D PublicConstants::PlatformMoveBounds = QVector2D(0.0f, 20.0f);
const QVector2D PublicConstants::BallSize = QVector2D(10.0f, 10.0f);
const float PublicConstants::PlatformBallOffset = PlatformSize.y()/2 + BallSize.y()/2;