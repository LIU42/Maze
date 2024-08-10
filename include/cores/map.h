#ifndef __CORES_MAP_H__
#define __CORES_MAP_H__

#include <QRandomGenerator>
#include <QList>
#include <QStack>
#include <QQueue>

#include "commons/constants.h"
#include "cores/points.h"

using MapBlock = IntPoint;

class MapUnit
{
    private:
        MapBlock previousBlock;

    private:
        bool wall[DirectIndex::COUNT];
        bool visited;
        int stepCount;

    public:
        void init();
        void removeWall(int directIndex);

    public:
        void setPrevious(MapBlock& previousBlock);

    public:
        void setVisited(bool visited);
        void setStepCount(int stepCount);

    public:
        MapBlock& getPrevious();

    public:
        int getStepCount();

    public:
        bool hasWall(int directIndex);
        bool isVisited();
};

class Map
{
    private:
        MapUnit units[MapProperties::ROWS][MapProperties::COLS];

    private:
        QList<MapBlock> getNeighbors(MapBlock& currentBlock);

    private:
        MapBlock& getPrevious(MapBlock& currentBlock);

    private:
        void setPrevious(MapBlock& currentBlock, MapBlock& nextBlock);
        void setVisited(MapBlock& currentBlock);
        void removeWall(MapBlock& currentBlock, MapBlock& nextBlock);

    private:
        bool isInRange(int x, int y);
        bool hasWall(MapBlock& currentBlock, MapBlock& nextBlock);

    public:
        void initUnits();
        void generateMaze();

    public:
        bool hasWall(int x, int y, int directIndex);

    public:
        QList<MapBlock> getWayBlocks(int startX, int startY);
};
#endif
