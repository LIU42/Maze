#ifndef __GAMES_PLAYER_H__
#define __GAMES_PLAYER_H__

#include "Games/MazeMap.h"

using FloatIndex = QPointF;
using RoundIndex = QPoint;

class Player
{
    private:
        static constexpr int MOVE_SPEED = 5;
        static constexpr int INIT_POSITION_X = 20;
        static constexpr int INIT_POSITION_Y = 20;

    private:
        MazeMap* pMazeMap;

    private:
        FloatIndex floatIndex;
        RoundIndex roundIndex;
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
        Player(MazeMap* pMazeMap);

    public:
        void setForwardDirect(Direct direct);
        void setMoveStart();
        void setMoveStop();

    public:
        void resetPlayer();
        void playerMove();

    public:
        int getPositionX();
        int getPositionY();

    public:
        double getFloatIndexX();
        double getFloatIndexY();
};
#endif