#ifndef __MAP_H__
#define __MAP_H__

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QQueue>

using MazeBlockPoint = QPoint;
using MazeBlockStack = QStack<QPoint>;
using MazeBlockQueue = QQueue<QPoint>;
using MazeNearbyList = QVector<QPoint>;
using MazeWayData = QVector<QPoint>;

enum Direct { UP, DOWN, LEFT, RIGHT };

class MazeBlockUnit
{
    friend class Map;

    public:
        static const int SIZE = 30;
        static const int DIRECT_COUNT = 4;

    private:
        MazeBlockPoint preBlock;

    private:
        bool isWall[DIRECT_COUNT];
        bool isVisited;
        int stepCount;
};

class Map
{
	public:
		static const int ROWS = 30;
        static const int COLS = 20;

    private:
        MazeBlockUnit unitMatrix[ROWS][COLS];

	private:
        MazeNearbyList getNearbyList(MazeBlockPoint&);
        MazeBlockPoint getPreBlock(MazeBlockPoint&);
        int getStepCount(MazeBlockPoint&);

	private:
        void setVisited(MazeBlockPoint&, int&);
        void removeWall(MazeBlockPoint&, MazeBlockPoint&);
        void setPreBlock(MazeBlockPoint&, MazeBlockPoint&);

	private:
		bool isInRange(int, int);
        bool isHaveWall(MazeBlockPoint&, MazeBlockPoint&);

	public:
        void initUnitMatrix();
        void generateMaze();

	public:
		bool isHaveWall(int, int, Direct);
        MazeWayData getWayData(int, int);
};
#endif