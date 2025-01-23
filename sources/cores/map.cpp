#include "cores/map.h"

void MapUnit::reset()
{
    memset(wall, true, sizeof(wall));

    this->previousX = 0;
    this->previousY = 0;
    this->stepCount = 0;

    this->visited = false;
}

void MapUnit::setVisited(bool visited)
{
    this->visited = visited;
}

void MapUnit::setPreviousX(int previousX)
{
    this->previousX = previousX;
}

void MapUnit::setPreviousY(int previousY)
{
    this->previousY = previousY;
}

void MapUnit::setStepCount(int stepCount)
{
    this->stepCount = stepCount;
}

void MapUnit::removeWall(int direct)
{
    this->wall[direct] = false;
}

int MapUnit::getPreviousX()
{
    return previousX;
}

int MapUnit::getPreviousY()
{
    return previousY;
}

int MapUnit::getStepCount()
{
    return stepCount;
}

bool MapUnit::hasWall(int directIndex)
{
    return wall[directIndex];
}

bool MapUnit::isVisited()
{
    return visited;
}

void Map::reset()
{
    for (int x = 0; x < MapProperties::ROWS; x++)
    {
        for (int y = 0; y < MapProperties::COLS; y++)
        {
            units[x][y].reset();
        }
    }
}

bool Map::isInRange(int x, int y)
{
    return x >= 0 && x < MapProperties::ROWS && y >= 0 && y < MapProperties::COLS;
}

QList<MapBlock> Map::getNeighbors(int x, int y)
{
    QList<MapBlock> neighbors;

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

void Map::setVisited(int x, int y)
{
    units[x][y].setVisited(true);
}

bool Map::hasWall(int x1, int y1, int x2, int y2)
{
    if (x2 == x1 && y2 < y1)
    {
        return units[x1][y1].hasWall(Directs::UP);
    }
    else if (x2 == x1 && y2 > y1)
    {
        return units[x1][y1].hasWall(Directs::DOWN);
    }
    else if (x2 < x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(Directs::LEFT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        return units[x1][y1].hasWall(Directs::RIGHT);
    }
    return true;
}

void Map::removeWall(int x1, int y1, int x2, int y2)
{
    if (x2 == x1 && y2 < y1)
    {
        units[x1][y1].removeWall(Directs::UP);
        units[x2][y2].removeWall(Directs::DOWN);
    }
    else if (x2 == x1 && y2 > y1)
    {
        units[x1][y1].removeWall(Directs::DOWN);
        units[x2][y2].removeWall(Directs::UP);
    }
    else if (x2 < x1 && y2 == y1)
    {
        units[x1][y1].removeWall(Directs::LEFT);
        units[x2][y2].removeWall(Directs::RIGHT);
    }
    else if (x2 > x1 && y2 == y1)
    {
        units[x1][y1].removeWall(Directs::RIGHT);
        units[x2][y2].removeWall(Directs::LEFT);
    }
}

void Map::setPrevious(int x1, int y1, int x2, int y2)
{
    units[x2][y2].setPreviousX(x1);
    units[x2][y2].setPreviousY(y1);
    units[x2][y2].setStepCount(units[x1][y1].getStepCount() + 1);
}

int Map::getPreviousX(int x, int y)
{
    return units[x][y].getPreviousX();
}

int Map::getPreviousY(int x, int y)
{
    return units[x][y].getPreviousY();
}

void Map::generateMaze()
{
    QStack<MapBlock> blockStack;

    int currentX = QRandomGenerator::global()->bounded(MapProperties::ROWS);
    int currentY = QRandomGenerator::global()->bounded(MapProperties::COLS);

    setVisited(currentX, currentY);
    blockStack.push(MapBlock(currentX, currentY));

    while (!blockStack.isEmpty())
    {
        QList<MapBlock> neighbors = getNeighbors(currentX, currentY);

        if (neighbors.isEmpty())
        {
            MapBlock currentBlock = blockStack.pop();

            currentX = currentBlock.getX();
            currentY = currentBlock.getY();

            continue;
        }
        MapBlock nextBlock = neighbors[QRandomGenerator::global()->bounded(neighbors.length())];

        int nextX = nextBlock.getX();
        int nextY = nextBlock.getY();

        removeWall(currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;

        setVisited(nextX, nextY);
        blockStack.push(nextBlock);
    }
}

bool Map::hasWall(int x, int y, int direct)
{
    return units[x][y].hasWall(direct);
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
    int currentX = startX;
    int currentY = startY;

    setVisited(currentX, currentY);
    blockQueue.enqueue(MapBlock(currentX, currentY));

    while (!blockQueue.isEmpty())
    {
        MapBlock currentBlock = blockQueue.front();

        currentX = currentBlock.getX();
        currentY = currentBlock.getY();

        if (currentX == MapProperties::ROWS - 1 && currentY == MapProperties::COLS - 1)
        {
            break;
        }
        for (MapBlock& neighborBlock : getNeighbors(currentX, currentY))
        {
            int neighborX = neighborBlock.getX();
            int neighborY = neighborBlock.getY();

            if (!hasWall(currentX, currentY, neighborX, neighborY))
            {
                blockQueue.enqueue(neighborBlock);

                setVisited(neighborX, neighborY);
                setPrevious(currentX, currentY, neighborX, neighborY);
            }
        }
        blockQueue.dequeue();
    }
    QList<MapBlock> wayBlocks;

    for (int step = units[currentX][currentY].getStepCount(); step >= 0; step--)
    {
        wayBlocks.append(MapBlock(currentX, currentY));

        int previousX = getPreviousX(currentX, currentY);
        int previousY = getPreviousY(currentX, currentY);

        currentX = previousX;
        currentY = previousY;
    }
    return wayBlocks;
}
