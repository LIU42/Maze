#include "cores/map.h"

void MapUnit::init()
{
    for (int index = 0; index < DirectIndex::COUNT; index++)
    {
        wall[index] = true;
    }
    visited = false;
}

void MapUnit::setVisited(bool visited)
{
    this->visited = visited;
}

void MapUnit::setPrevious(MapBlock& previousBlock)
{
    this->previousBlock = previousBlock;
}

void MapUnit::setStepCount(int stepCount)
{
    this->stepCount = stepCount;
}

void MapUnit::removeWall(int directIndex)
{
    this->wall[directIndex] = false;
}

bool MapUnit::isVisited()
{
    return visited;
}

bool MapUnit::hasWall(int directIndex)
{
    return wall[directIndex];
}

int MapUnit::getStepCount()
{
    return stepCount;
}

MapBlock& MapUnit::getPrevious()
{
    return previousBlock;
}

void Map::initUnits()
{
    for (int x = 0; x < MapProperties::ROWS; x++)
    {
        for (int y = 0; y < MapProperties::COLS; y++)
        {
            units[x][y].init();
        }
    }
}

bool Map::isInRange(int x, int y)
{
    return x >= 0 && x < MapProperties::ROWS && y >= 0 && y < MapProperties::COLS;
}

QList<MapBlock> Map::getNeighbors(MapBlock& currentBlock)
{
    QList<MapBlock> neighbors;

    int x = currentBlock.getX();
    int y = currentBlock.getY();

    if (isInRange(x + 1, y) && !units[x + 1][y].isVisited())
    {
        neighbors.append(MapBlock(x + 1, y));
    }
    if (isInRange(x - 1, y) && !units[x - 1][y].isVisited())
    {
        neighbors.append(MapBlock(x - 1, y));
    }
    if (isInRange(x, y + 1) && !units[x][y + 1].isVisited())
    {
        neighbors.append(MapBlock(x, y + 1));
    }
    if (isInRange(x, y - 1) && !units[x][y - 1].isVisited())
    {
        neighbors.append(MapBlock(x, y - 1));
    }
    return neighbors;
}

void Map::setVisited(MapBlock& currentBlock)
{
    units[currentBlock.getX()][currentBlock.getY()].setVisited(true);
}

bool Map::hasWall(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int x1 = currentBlock.getX();
    int y1 = currentBlock.getY();

    int x2 = nextBlock.getX();
    int y2 = nextBlock.getY();

    if (x2 == x1 && y2 < y1)
    {
        return units[x1][y1].hasWall(DirectIndex::UP);
    }
    else if (x2 == x1 && y2 > y1)
    {
        return units[x1][y1].hasWall(DirectIndex::DOWN);
    }
    else if (x2 < x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(DirectIndex::LEFT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(DirectIndex::RIGHT);
    }
    return true;
}

void Map::removeWall(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int x1 = currentBlock.getX();
    int y1 = currentBlock.getY();

    int x2 = nextBlock.getX();
    int y2 = nextBlock.getY();

    if (x2 == x1 && y2 < y1)
    {
        units[x1][y1].removeWall(DirectIndex::UP);
        units[x2][y2].removeWall(DirectIndex::DOWN);
    }
    else if (x2 == x1 && y2 > y1)
    {
        units[x1][y1].removeWall(DirectIndex::DOWN);
        units[x2][y2].removeWall(DirectIndex::UP);
    }
    else if (x2 < x1 && y2 == y1)
    {
        units[x1][y1].removeWall(DirectIndex::LEFT);
        units[x2][y2].removeWall(DirectIndex::RIGHT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        units[x1][y1].removeWall(DirectIndex::RIGHT);
        units[x2][y2].removeWall(DirectIndex::LEFT);
    }
}

void Map::setPrevious(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int x2 = nextBlock.getX();
    int y2 = nextBlock.getY();

    units[x2][y2].setPrevious(currentBlock);

    int x1 = currentBlock.getX();
    int y1 = currentBlock.getY();

    units[x2][y2].setStepCount(units[x1][y1].getStepCount() + 1);
}

MapBlock& Map::getPrevious(MapBlock& currentBlock)
{
    return units[currentBlock.getX()][currentBlock.getY()].getPrevious();
}

void Map::generateMaze()
{
    QStack<MapBlock> blockStack;

    int startX = QRandomGenerator::global()->bounded(MapProperties::ROWS);
    int startY = QRandomGenerator::global()->bounded(MapProperties::COLS);

    MapBlock currentBlock(startX, startY);

    setVisited(currentBlock);
    blockStack.push(currentBlock);

    while (!blockStack.isEmpty())
    {
        QList<MapBlock> neighbors = getNeighbors(currentBlock);

        if (neighbors.isEmpty())
        {
            currentBlock = blockStack.pop();
            continue;
        }
        MapBlock nextBlock = neighbors[QRandomGenerator::global()->bounded(neighbors.length())];

        removeWall(currentBlock, nextBlock);
        setVisited(nextBlock);

        blockStack.push(nextBlock);
        currentBlock = nextBlock;
    }
}

bool Map::hasWall(int x, int y, int directIndex)
{
    return units[x][y].hasWall(directIndex);
}

QList<MapBlock> Map::getWayBlocks(int startX, int startY)
{
    QQueue<MapBlock> blockQueue;

    for (int x = 0; x < MapProperties::ROWS; x++)
    {
        for (int y = 0; y < MapProperties::COLS; y++)
        {
            units[x][y].setVisited(false);
            units[x][y].setStepCount(0);
        }
    }
    MapBlock currentBlock(startX, startY);

    setVisited(currentBlock);
    blockQueue.enqueue(currentBlock);

    while (!blockQueue.isEmpty())
    {
        currentBlock = blockQueue.front();

        if (currentBlock.getX() == MapProperties::ROWS - 1 && currentBlock.getY() == MapProperties::COLS - 1)
        {
            break;
        }
        for (MapBlock& nearbyBlock : getNeighbors(currentBlock))
        {
            if (!hasWall(currentBlock, nearbyBlock))
            {
                blockQueue.enqueue(nearbyBlock);

                setVisited(nearbyBlock);
                setPrevious(currentBlock, nearbyBlock);
            }
        }
        blockQueue.dequeue();
    }
    QList<MapBlock> wayBlocks;

    for (int step = units[currentBlock.getX()][currentBlock.getY()].getStepCount(); step >= 0; step--)
    {
        wayBlocks.append(currentBlock);
        currentBlock = getPrevious(currentBlock);
    }
    return wayBlocks;
}
