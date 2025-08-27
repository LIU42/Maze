#ifndef __CORES_PLAYER_H__
#define __CORES_PLAYER_H__

#include "cores/map.h"
#include "cores/points.h"

class Player : public IntPoint
{
    private:
        Map* map;

    private:
        double floatX;
        double floatY;

    private:
        int roundX;
        int roundY;

    private:
        void compensateX();
        void compensateY();

    public:
        Player(Map* map);

    public:
        bool moveUp();
        bool moveDown();
        bool moveLeft();
        bool moveRight();

    public:
        void reset();
        void updateLocationInfo();

    public:
        double getFloatLocationX();
        double getFloatLocationY();
};
#endif
