#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"

typedef QPointF Real;
typedef QPoint Near;

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
		bool isHaveWall(Near&, Direct);
		void horizonDiffHandle(Real&, Near&, Direct);
		void verticalDiffHandle(Real&, Near&, Direct);

	private:
		void moveUp(Real&, Near&);
		void moveDown(Real&, Near&);
		void moveLeft(Real&, Near&);
		void moveRight(Real&, Near&);

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