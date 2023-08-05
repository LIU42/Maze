#include "map.h"

void Map::initUnitMatrix()
{
    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
            {
                unitMatrix[x][y].isWall[direct] = true;
            }
            unitMatrix[x][y].isVisited = false;
        }
    }
}

bool Map::isInRange(int x, int y)
{
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
    {
        return true;
    }
    return false;
}

MazeNearbyList Map::getNearbyList(MazeBlockPoint& currentBlock)
{
    MazeNearbyList nearbyList;

    int currentX = currentBlock.x();
    int currentY = currentBlock.y();

    if (isInRange(currentX + 1, currentY) && !unitMatrix[currentX + 1][currentY].isVisited)
    {
        nearbyList.append(MazeBlockPoint(currentX + 1, currentY));
    }
    if (isInRange(currentX - 1, currentY) && !unitMatrix[currentX - 1][currentY].isVisited)
    {
        nearbyList.append(MazeBlockPoint(currentX - 1, currentY));
    }
    if (isInRange(currentX, currentY + 1) && !unitMatrix[currentX][currentY + 1].isVisited)
    {
        nearbyList.append(MazeBlockPoint(currentX, currentY + 1));
    }
    if (isInRange(currentX, currentY - 1) && !unitMatrix[currentX][currentY - 1].isVisited)
    {
        nearbyList.append(MazeBlockPoint(currentX, currentY - 1));
    }
    return nearbyList;
}

void Map::setVisited(MazeBlockPoint& block, int& visitedCount)
{
    int x = block.x();
    int y = block.y();

    unitMatrix[x][y].isVisited = true;
    visitedCount += 1;
}

bool Map::isHaveWall(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();
    int nearbyX = nearbyBlock.x();
    int nearbyY = nearbyBlock.y();

    if (nearbyX == currentX && nearbyY < currentY)
    {
        return unitMatrix[currentX][currentY].isWall[DIRECT_UP];
    }
    else if (nearbyX == currentX && nearbyY > currentY)
    {
        return unitMatrix[currentX][currentY].isWall[DIRECT_DOWN];
    }
    else if (nearbyX < currentX && nearbyY == currentY)
    {
        return unitMatrix[currentX][currentY].isWall[DIRECT_LEFT];
    }
    else if (nearbyX > currentX && nearbyY == currentY)
    {
        return unitMatrix[currentX][currentY].isWall[DIRECT_RIGHT];
    }
    return true;
}

void Map::removeWall(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();
    int nearbyX = nearbyBlock.x();
    int nearbyY = nearbyBlock.y();

    if (nearbyX == currentX && nearbyY < currentY)
    {
        unitMatrix[currentX][currentY].isWall[DIRECT_UP] = false;
        unitMatrix[nearbyX][nearbyY].isWall[DIRECT_DOWN] = false;
    }
    else if (nearbyX == currentX && nearbyY > currentY)
    {
        unitMatrix[currentX][currentY].isWall[DIRECT_DOWN] = false;
        unitMatrix[nearbyX][nearbyY].isWall[DIRECT_UP] = false;
    }
    else if (nearbyX < currentX && nearbyY == currentY)
    {
        unitMatrix[currentX][currentY].isWall[DIRECT_LEFT] = false;
        unitMatrix[nearbyX][nearbyY].isWall[DIRECT_RIGHT] = false;
    }
    else if (nearbyX > currentX && nearbyY == currentY)
    {
        unitMatrix[currentX][currentY].isWall[DIRECT_RIGHT] = false;
        unitMatrix[nearbyX][nearbyY].isWall[DIRECT_LEFT] = false;
    }
}

void Map::setPreBlock(MazeBlockPoint& currentBlock, MazeBlockPoint& nearbyBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();
    int nearbyX = nearbyBlock.x();
    int nearbyY = nearbyBlock.y();

    unitMatrix[nearbyX][nearbyY].stepCount = unitMatrix[currentX][currentY].stepCount + 1;
    unitMatrix[nearbyX][nearbyY].preBlock = currentBlock;
}

int Map::getStepCount(MazeBlockPoint& block)
{
    return unitMatrix[block.x()][block.y()].stepCount;
}

MazeBlockPoint Map::getPreBlock(MazeBlockPoint& block)
{
    return unitMatrix[block.x()][block.y()].preBlock;
}

void Map::generateMaze()
{
    MazeBlockStack blockStack;
    MazeNearbyList nearbyList;
    MazeBlockPoint currentBlock;
    MazeBlockPoint nearbyBlock;
    int visitCount = 0;

    currentBlock.setX(rand() % ROWS);
    currentBlock.setY(rand() % COLS);
    setVisited(currentBlock, visitCount);

    while (visitCount < ROWS * COLS)
    {
        nearbyList = getNearbyList(currentBlock);

        if (!nearbyList.isEmpty())
        {
            nearbyBlock = nearbyList[rand() % nearbyList.length()];
            blockStack.push(currentBlock);
            removeWall(currentBlock, nearbyBlock);
            setVisited(nearbyBlock, visitCount);
            currentBlock = nearbyBlock;
        }
        else if (!blockStack.isEmpty())
        {
            currentBlock = blockStack.pop();
        }
    }
}

bool Map::isHaveWall(int x, int y, Direct direct)
{
    return unitMatrix[x][y].isWall[direct];
}

MazeWayData Map::getWayData(int initX, int initY)
{
    MazeBlockQueue blockQueue;
    MazeNearbyList nearbyList;
    MazeBlockPoint currentBlock;
    MazeWayData wayData;
    int visitCount = 0;

    for (int x = 0; x < ROWS; x++)
    {
        for (int y = 0; y < COLS; y++)
        {
            unitMatrix[x][y].isVisited = false;
            unitMatrix[x][y].stepCount = 0;
        }
    }
    currentBlock.setX(initX);
    currentBlock.setY(initY);
    setVisited(currentBlock, visitCount);
    blockQueue.enqueue(currentBlock);

    while (!blockQueue.isEmpty())
    {
        currentBlock = blockQueue.front();

        if (currentBlock.x() == ROWS - 1 && currentBlock.y() == COLS - 1)
        {
            break;
        }
        nearbyList = getNearbyList(currentBlock);

        for (int i = 0; i < nearbyList.length(); i++)
        {
            if (!isHaveWall(currentBlock, nearbyList[i]))
            {
                blockQueue.enqueue(nearbyList[i]);
                setPreBlock(currentBlock, nearbyList[i]);
                setVisited(nearbyList[i], visitCount);
            }
        }
        blockQueue.dequeue();
    }
    for (int stepCount = getStepCount(currentBlock); stepCount >= 0; stepCount--)
    {
        wayData.append(currentBlock);
        currentBlock = getPreBlock(currentBlock);
    }
    return wayData;
}