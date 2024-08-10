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

class FloatPoint
{
    protected:
        float x;
        float y;

    public:
        FloatPoint();
        FloatPoint(float x, float y);

    public:
        void setX(float x);
        void setY(float y);

    public:
        float getX();
        float getY();
};
#endif
