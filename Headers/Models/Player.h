#ifndef __MODELS_PLAYER_H__
#define __MODELS_PLAYER_H__

#include "Models/Map.h"

using RelativePoint = QPointF;
using BlockPoint = QPoint;

class Player
{
    private:
        static const int SPEED = 5;
        static const int INIT_POSITION_X = 20;
        static const int INIT_POSITION_Y = 20;

    private:
        Map* pMap;

    private:
        RelativePoint relativePoint;
        BlockPoint blockPoint;
        Direct forwardDirect;

    private:
        bool isOnMove;
        int positionX;
        int positionY;

    private:
        bool isForwardHaveWall();
        void horizonDiffHandler();
        void verticalDiffHandler();

    private:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

    public:
        void setForwardDirect(Direct direct);
        void setIsOnMove(bool isOnMove);

    public:
        void setMap(Map* pMap);
        void reset();
        void move();

    public:
        int getPositionX();
        int getPositionY();

    public:
        double getRelativeX();
        double getRelativeY();
};
#endif