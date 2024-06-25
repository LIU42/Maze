#ifndef __ENGINES_PLAYER_H__
#define __ENGINES_PLAYER_H__

#include "Engines/Map.h"
#include "Engines/Point.h"

using FloatIndex = FloatPoint;
using RoundIndex = IntPoint;

class Player : public IntPoint
{
    private:
        static constexpr int MOVE_SPEED = 4;
        static constexpr int INIT_X = 16;
        static constexpr int INIT_Y = 16;

    private:
        Map* pMap;

    private:
        FloatIndex floatIndex;
        RoundIndex roundIndex;
        Direct forwardDirect;

    private:
        bool onMove;

    private:
        bool isForwardHaveWall();
        void handleHorizonDeviation();
        void handleVerticalDeviation();

    private:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

    public:
        Player(Map* pMap);

    public:
        void setForwardDirect(Direct direct);
        void setMoveStart();
        void setMoveStop();

    public:
        void reset();
        void move();

    public:
        double getFloatIndexX();
        double getFloatIndexY();
};
#endif
