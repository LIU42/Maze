#ifndef __MAP_H__
#define __MAP_H__

#include <QPoint>
#include <QStack>
#include <QVector>
#include <QQueue>

typedef QPoint Unit;
typedef QStack <Unit> UnitStack;
typedef QQueue <Unit> UnitQueue;
typedef QVector <Unit> NearList;
typedef QVector <Unit> WayData;

enum Direct { UP, DOWN, LEFT, RIGHT };

struct MazeUnit
{
	bool isWall[4];
	bool isVisit;
	int stepCount;
	Unit lastUnit;
};

class Map
{
	public:
		static const int ROWS = 30;
		static const int COLS = 20;
		static const int UNIT_SIZE = 30;

	private:
		MazeUnit units[ROWS][COLS];

	private:
		NearList getNearList(Unit&);
		Unit getLastUnit(Unit&);
		int getStepCount(Unit&);

	private:
		void setVisit(Unit&, int&);
		void removeWall(Unit&, Unit&);
		void setLastUnit(Unit&, Unit&);

	private:
		bool isInRange(int, int);
		bool isHaveWall(Unit&, Unit&);

	public:
		void init();
		void generate();

	public:
		bool isHaveWall(int, int, Direct);
		WayData getWayData(int, int);
};
#endif