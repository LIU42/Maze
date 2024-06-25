#ifndef __GAMES_MAZEMAP_H__
#define __GAMES_MAZEMAP_H__

#include <QRandomGenerator>
#include <QList>
#include <QPoint>
#include <QStack>
#include <QQueue>

using MazeBlock = QPoint;

enum class Direct
{
    DIRECT_UP,
    DIRECT_DOWN,
    DIRECT_LEFT,
    DIRECT_RIGHT
};

class MazeBlockUnit
{
    public:
        static constexpr int BLOCK_SIZE = 24;
        static constexpr int DIRECT_COUNT = 4;

    public:
        MazeBlock precursorBlock;
        int stepCount;
        bool isVisited;
        bool isWall[DIRECT_COUNT];
};

class MazeMap
{
    public:
        static constexpr int MAZE_ROWS = 30;
        static constexpr int MAZE_COLS = 20;

    private:
        MazeBlockUnit unitMatrix[MAZE_ROWS][MAZE_COLS];

    private:
        QList<MazeBlock> getNearbyList(MazeBlock& currentBlock);
        MazeBlock getPrecursorBlock(MazeBlock& currentBlock);

    private:
        void setPrecursorBlock(MazeBlock& currentBlock, MazeBlock& nextBlock);
        void setVisited(MazeBlock& currentBlock);
        void removeWall(MazeBlock& currentBlock, MazeBlock& nextBlock);

    private:
        bool isInRange(int x, int y);
        bool isHaveWall(MazeBlock& currentBlock, MazeBlock& nextBlock);

    public:
        void initUnitMatrix();
        void generateMaze();

    public:
        QList<MazeBlock> getWayBlockList(int initX, int initY);
        bool isHaveWall(int x, int y, Direct direct);
};
#endif