#include "cores/points.h"

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
