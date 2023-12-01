#ifndef __MODELS_MAP_H__
#define __MODELS_MAP_H__

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QQueue>

using MazeBlockPoint = QPoint;
using MazeBlockStack = QStack<QPoint>;
using MazeBlockQueue = QQueue<QPoint>;
using MazeNearbyList = QVector<QPoint>;
using MazeWayData = QVector<QPoint>;

enum Direct
{
    DIRECT_UP,
    DIRECT_DOWN,
    DIRECT_LEFT,
    DIRECT_RIGHT
};

class MazeBlockUnit
{
    public:
        static const int SIZE = 30;
        static const int DIRECT_COUNT = 4;

    public:
        MazeBlockPoint preBlock;

    public:
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
        MazeNearbyList getNearbyList(MazeBlockPoint& currentBlock);
        MazeBlockPoint getPreBlock(MazeBlockPoint& block);
        int getStepCount(MazeBlockPoint& block);

    private:
        void setVisited(MazeBlockPoint& block, int& visitedCount);
        void removeWall(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock);
        void setPreBlock(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock);

    private:
        bool isInRange(int x, int y);
        bool isHaveWall(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock);

    public:
        void initUnitMatrix();
        void generateMaze();

    public:
        bool isHaveWall(int x, int y, Direct direct);
        MazeWayData getWayData(int initX, int initY);
};
#endif