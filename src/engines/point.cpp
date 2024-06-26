#include "engines/point.h"

IntPoint::IntPoint()
{
    this->x = 0;
    this->y = 0;
}

IntPoint::IntPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

void IntPoint::setX(int x)
{
    this->x = x;
}

void IntPoint::setY(int y)
{
    this->y = y;
}

int IntPoint::getX()
{
    return x;
}

int IntPoint::getY()
{
    return y;
}

FloatPoint::FloatPoint()
{
    this->x = 0;
    this->y = 0;
}

FloatPoint::FloatPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

void FloatPoint::setX(float x)
{
    this->x = x;
}

void FloatPoint::setY(float y)
{
    this->y = y;
}

float FloatPoint::getX()
{
    return x;
}

float FloatPoint::getY()
{
    return y;
}
