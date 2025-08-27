#ifndef __CORES_POINTS_H__
#define __CORES_POINTS_H__

class IntPoint
{
    protected:
        int x;
        int y;

    public:
        IntPoint();
        IntPoint(int x, int y);

    public:
        void setX(int x);
        void setY(int y);

    public:
        int getX();
        int getY();
};
#endif
