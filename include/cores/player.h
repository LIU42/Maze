#ifndef __CORES_PLAYER_H__
#define __CORES_PLAYER_H__

#include "cores/map.h"
#include "cores/points.h"

using FloatLocation = FloatPoint;
using RoundLocation = IntPoint;

class Player : public IntPoint
{
    private:
        Map* pMap;

    private:
        FloatLocation floatLocation;
        RoundLocation roundLocation;

    private:
        bool onMove;
        int directIndex;

    private:
        bool isForwardHaveWall();
        void horizonReparation();
        void verticalReparation();

    private:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

    public:
        Player(Map* pMap);

    public:
        void setDirect(int directIndex);
        void moveStart();
        void moveStop();

    public:
        void reset();
        void move();

    public:
        double getFloatLocationX();
        double getFloatLocationY();
};
#endif
