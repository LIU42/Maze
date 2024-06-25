#include "Engines/Map.h"

void MapUnit::init()
{
    for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
    {
        wall[index] = true;
    }
    visited = false;
}

void MapUnit::setVisited(bool visited)
{
    this->visited = visited;
}

void MapUnit::setPreBlock(MapBlock& preBlock)
{
    this->preBlock = preBlock;
}

void MapUnit::setStepCount(int stepCount)
{
    this->stepCount = stepCount;
}

void MapUnit::removeWall(Direct direct)
{
    this->wall[(int)direct] = false;
}

bool MapUnit::isVisited()
{
    return visited;
}

bool MapUnit::hasWall(Direct direct)
{
    return wall[(int)direct];
}

int MapUnit::getStepCount()
{
    return stepCount;
}

MapBlock& MapUnit::getPreBlock()
{
    return preBlock;
}

void Map::initUnits()
{
    for (int x = 0; x < MAP_ROWS; x++)
    {
        for (int y = 0; y < MAP_COLS; y++)
        {
            units[x][y].init();
        }
    }
}

bool Map::isInRange(int x, int y)
{
    return x >= 0 && x < MAP_ROWS && y >= 0 && y < MAP_COLS;
}

QList<MapBlock> Map::getNearbyList(MapBlock& currentBlock)
{
    QList<MapBlock> nearbyList;

    int currentX = currentBlock.getX();
    int currentY = currentBlock.getY();

    if (isInRange(currentX + 1, currentY) && !units[currentX + 1][currentY].isVisited())
    {
        nearbyList.append(MapBlock(currentX + 1, currentY));
    }
    if (isInRange(currentX - 1, currentY) && !units[currentX - 1][currentY].isVisited())
    {
        nearbyList.append(MapBlock(currentX - 1, currentY));
    }
    if (isInRange(currentX, currentY + 1) && !units[currentX][currentY + 1].isVisited())
    {
        nearbyList.append(MapBlock(currentX, currentY + 1));
    }
    if (isInRange(currentX, currentY - 1) && !units[currentX][currentY - 1].isVisited())
    {
        nearbyList.append(MapBlock(currentX, currentY - 1));
    }
    return nearbyList;
}

void Map::setVisited(MapBlock& currentBlock)
{
    units[currentBlock.getX()][currentBlock.getY()].setVisited(true);
}

bool Map::hasWall(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int currentX = currentBlock.getX();
    int currentY = currentBlock.getY();

    int nextX = nextBlock.getX();
    int nextY = nextBlock.getY();

    if (nextX == currentX && nextY < currentY)
    {
        return units[currentX][currentY].hasWall(Direct::DIRECT_UP);
    }
    else if (nextX == currentX && nextY > currentY)
    {
        return units[currentX][currentY].hasWall(Direct::DIRECT_DOWN);
    }
    else if (nextX < currentX && nextY == currentY)
    {
        return units[currentX][currentY].hasWall(Direct::DIRECT_LEFT);
    }
    else if (nextX > currentX && nextY == currentY)
    {
        return units[currentX][currentY].hasWall(Direct::DIRECT_RIGHT);
    }
    return true;
}

void Map::removeWall(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int currentX = currentBlock.getX();
    int currentY = currentBlock.getY();

    int nextX = nextBlock.getX();
    int nextY = nextBlock.getY();

    if (nextX == currentX && nextY < currentY)
    {
        units[currentX][currentY].removeWall(Direct::DIRECT_UP);
        units[nextX][nextY].removeWall(Direct::DIRECT_DOWN);
    }
    else if (nextX == currentX && nextY > currentY)
    {
        units[currentX][currentY].removeWall(Direct::DIRECT_DOWN);
        units[nextX][nextY].removeWall(Direct::DIRECT_UP);
    }
    else if (nextX < currentX && nextY == currentY)
    {
        units[currentX][currentY].removeWall(Direct::DIRECT_LEFT);
        units[nextX][nextY].removeWall(Direct::DIRECT_RIGHT);
    }
    else if (nextX > currentX && nextY == currentY)
    {
        units[currentX][currentY].removeWall(Direct::DIRECT_RIGHT);
        units[nextX][nextY].removeWall(Direct::DIRECT_LEFT);
    }
}

void Map::setPreBlock(MapBlock& currentBlock, MapBlock& nextBlock)
{
    int currentX = currentBlock.getX();
    int currentY = currentBlock.getY();

    int nextX = nextBlock.getX();
    int nextY = nextBlock.getY();

    units[nextX][nextY].setStepCount(units[currentX][currentY].getStepCount() + 1);
    units[nextX][nextY].setPreBlock(currentBlock);
}

MapBlock& Map::getPreBlock(MapBlock& currentBlock)
{
    return units[currentBlock.getX()][currentBlock.getY()].getPreBlock();
}

void Map::generateMaze()
{
    int initX = QRandomGenerator::global()->bounded(MAP_ROWS);
    int initY = QRandomGenerator::global()->bounded(MAP_COLS);

    QStack<MapBlock> blockStack;
    MapBlock currentBlock(initX, initY);

    setVisited(currentBlock);
    blockStack.push(currentBlock);

    while (!blockStack.isEmpty())
    {
        QList<MapBlock> nearbyList = getNearbyList(currentBlock);

        if (nearbyList.isEmpty())
        {
            currentBlock = blockStack.pop();
            continue;
        }
        MapBlock nextBlock = nearbyList[QRandomGenerator::global()->bounded(nearbyList.length())];

        removeWall(currentBlock, nextBlock);
        setVisited(nextBlock);
        blockStack.push(nextBlock);
        currentBlock = nextBlock;
    }
}

bool Map::hasWall(int x, int y, Direct direct)
{
    return units[x][y].hasWall(direct);
}

QList<MapBlock> Map::getWayBlockList(int initX, int initY)
{
    QQueue<MapBlock> blockQueue;
    MapBlock currentBlock(initX, initY);

    for (int x = 0; x < MAP_ROWS; x++)
    {
        for (int y = 0; y < MAP_COLS; y++)
        {
            units[x][y].setVisited(false);
            units[x][y].setStepCount(0);
        }
    }
    setVisited(currentBlock);
    blockQueue.enqueue(currentBlock);

    while (!blockQueue.isEmpty())
    {
        currentBlock = blockQueue.front();

        if (currentBlock.getX() == MAP_ROWS - 1 && currentBlock.getY() == MAP_COLS - 1)
        {
            break;
        }
        for (MapBlock& nearbyBlock : getNearbyList(currentBlock))
        {
            if (!hasWall(currentBlock, nearbyBlock))
            {
                blockQueue.enqueue(nearbyBlock);
                setPreBlock(currentBlock, nearbyBlock);
                setVisited(nearbyBlock);
            }
        }
        blockQueue.dequeue();
    }
    QList<MapBlock> wayBlockList;

    for (int step = units[currentBlock.getX()][currentBlock.getY()].getStepCount(); step >= 0; step--)
    {
        wayBlockList.append(currentBlock);
        currentBlock = getPreBlock(currentBlock);
    }
    return wayBlockList;
}
