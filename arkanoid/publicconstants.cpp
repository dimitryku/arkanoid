#include "publicconstants.h"

const QRectF PublicConstants::SceneRect = QRectF(0, 0, 1000, 900);
const QVector2D PublicConstants::PlatformSize = QVector2D(80.0f, 10.0f);
//const QVector2D PublicConstants::PlatformStartPoint = QVector2D(10.0f, 10.0f);
const QVector2D PublicConstants::PlatformStartPoint = QVector2D(SceneRect.width() / 2, SceneRect.height() - PlatformSize.y());
const QVector2D PublicConstants::PlatformSizeExtended = QVector2D(120.0f, 10.0f);
const QVector2D PublicConstants::PlatformDefaultSpeed = QVector2D(10.0f, 0.0f);
// x - left, y - right bounds of platform center by x coordinate
const QVector2D PublicConstants::PlatformMoveBounds = QVector2D(PlatformSize.x() / 2, SceneRect.width() - PlatformSize.x() / 2);
const QVector2D PublicConstants::BallSize = QVector2D(10.0f, 10.0f);
const QVector2D PublicConstants::BrickSize = QVector2D(40.0f, 15.0f);
const float PublicConstants::PlatformBallOffset = PlatformSize.y()/2 + BallSize.y()/2;
const int PublicConstants::DefaultTimerTick = 20;
const QVector2D PublicConstants::BonusBodySize = QVector2D(20, 20);
const QVector2D PublicConstants::BonusBodySpeed = QVector2D(0, 20);
const float PublicConstants::sizePlatformMultiplier_dec = 0.5;
const float PublicConstants::sizePlatformMultiplier_inc = 2;
const float PublicConstants::speedBallMultiplyier_dec = 0.5;
const float PublicConstants::speedBallMultiplyier_inc = 2;
