#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"

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
        void setForwardDirect(Direct);
		void setIsOnMove(bool);

	public:
        void setMap(Map*);
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