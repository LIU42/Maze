#ifndef __ENGINES_MAP_H__
#define __ENGINES_MAP_H__

#include <QRandomGenerator>
#include <QList>
#include <QStack>
#include <QQueue>

#include "Engines/Point.h"

using MapBlock = IntPoint;

enum class Direct
{
    DIRECT_UP,
    DIRECT_DOWN,
    DIRECT_LEFT,
    DIRECT_RIGHT
};

class MapUnit
{
    public:
        static constexpr int BLOCK_SIZE = 24;
        static constexpr int DIRECT_COUNT = 4;

    private:
        MapBlock preBlock;

    private:
        bool wall[DIRECT_COUNT];
        bool visited;
        int stepCount;

    public:
        void init();

    public:
        void removeWall(Direct direct);
        void setPreBlock(MapBlock& preBlock);

    public:
        void setVisited(bool visited);
        void setStepCount(int stepCount);

    public:
        MapBlock& getPreBlock();

    public:
        int getStepCount();

    public:
        bool hasWall(Direct direct);
        bool isVisited();
};

class Map
{
    public:
        static constexpr int MAP_ROWS = 30;
        static constexpr int MAP_COLS = 20;

    private:
        MapUnit units[MAP_ROWS][MAP_COLS];

    private:
        QList<MapBlock> getNearbyList(MapBlock& currentBlock);
        MapBlock& getPreBlock(MapBlock& currentBlock);

    private:
        void setPreBlock(MapBlock& currentBlock, MapBlock& nextBlock);
        void setVisited(MapBlock& currentBlock);
        void removeWall(MapBlock& currentBlock, MapBlock& nextBlock);

    private:
        bool isInRange(int x, int y);
        bool hasWall(MapBlock& currentBlock, MapBlock& nextBlock);

    public:
        void initUnits();
        void generateMaze();

    public:
        bool hasWall(int x, int y, Direct direct);

    public:
        QList<MapBlock> getWayBlockList(int initX, int initY);
};
#endif
