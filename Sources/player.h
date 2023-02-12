#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"

typedef QPointF RealPoint;
typedef QPoint NearPoint;

class Player : public QPoint
{
	private:
		static const int SPEED = 3;

	private:
		Direct direct;
		Map* pMap;

	private:
		bool isOnMove;
		int initX;
		int initY;

	private:
		bool isHaveWall(NearPoint&, Direct);
		void horizonDiffHandle(RealPoint&, NearPoint&, Direct);
		void verticalDiffHandle(RealPoint&, NearPoint&, Direct);

	private:
		void moveUp(RealPoint&, NearPoint&);
		void moveDown(RealPoint&, NearPoint&);
		void moveLeft(RealPoint&, NearPoint&);
		void moveRight(RealPoint&, NearPoint&);

	public:
		void setDirect(Direct);
		void setIsOnMove(bool);

	public:
		void init(int, int, Map*);
		void move();

	public:
		double getRelativeX();
		double getRelativeY();
};
#endif