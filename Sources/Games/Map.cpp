#include "Games/MazeMap.h"

void MazeMap::initUnitMatrix()
{
    for (int x = 0; x < MAZE_ROWS; x++)
    {
        for (int y = 0; y < MAZE_COLS; y++)
        {
            for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
            {
                unitMatrix[x][y].isWall[index] = true;
            }
            unitMatrix[x][y].isVisited = false;
        }
    }
}

bool MazeMap::isInRange(int x, int y)
{
    return x >= 0 && x < MAZE_ROWS && y >= 0 && y < MAZE_COLS;
}

QList<MazeBlock> MazeMap::getNearbyList(MazeBlock& currentBlock)
{
    QList<MazeBlock> nearbyList;

    int currentX = currentBlock.x();
    int currentY = currentBlock.y();

    if (isInRange(currentX + 1, currentY) && !unitMatrix[currentX + 1][currentY].isVisited)
    {
        nearbyList.append(MazeBlock(currentX + 1, currentY));
    }
    if (isInRange(currentX - 1, currentY) && !unitMatrix[currentX - 1][currentY].isVisited)
    {
        nearbyList.append(MazeBlock(currentX - 1, currentY));
    }
    if (isInRange(currentX, currentY + 1) && !unitMatrix[currentX][currentY + 1].isVisited)
    {
        nearbyList.append(MazeBlock(currentX, currentY + 1));
    }
    if (isInRange(currentX, currentY - 1) && !unitMatrix[currentX][currentY - 1].isVisited)
    {
        nearbyList.append(MazeBlock(currentX, currentY - 1));
    }
    return nearbyList;
}

void MazeMap::setVisited(MazeBlock& currentBlock)
{
    unitMatrix[currentBlock.x()][currentBlock.y()].isVisited = true;
}

bool MazeMap::isHaveWall(MazeBlock& currentBlock, MazeBlock& nextBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();

    int nextX = nextBlock.x();
    int nextY = nextBlock.y();

    if (nextX == currentX && nextY < currentY)
    {
        return unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_UP];
    }
    else if (nextX == currentX && nextY > currentY)
    {
        return unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_DOWN];
    }
    else if (nextX < currentX && nextY == currentY)
    {
        return unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_LEFT];
    }
    else if (nextX > currentX && nextY == currentY)
    {
        return unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_RIGHT];
    }
    return true;
}

void MazeMap::removeWall(MazeBlock& currentBlock, MazeBlock& nextBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();

    int nextX = nextBlock.x();
    int nextY = nextBlock.y();

    if (nextX == currentX && nextY < currentY)
    {
        unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_UP] = false;
        unitMatrix[nextX][nextY].isWall[(int)Direct::DIRECT_DOWN] = false;
    }
    else if (nextX == currentX && nextY > currentY)
    {
        unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_DOWN] = false;
        unitMatrix[nextX][nextY].isWall[(int)Direct::DIRECT_UP] = false;
    }
    else if (nextX < currentX && nextY == currentY)
    {
        unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_LEFT] = false;
        unitMatrix[nextX][nextY].isWall[(int)Direct::DIRECT_RIGHT] = false;
    }
    else if (nextX > currentX && nextY == currentY)
    {
        unitMatrix[currentX][currentY].isWall[(int)Direct::DIRECT_RIGHT] = false;
        unitMatrix[nextX][nextY].isWall[(int)Direct::DIRECT_LEFT] = false;
    }
}

void MazeMap::setPrecursorBlock(MazeBlock& currentBlock, MazeBlock& nextBlock)
{
    int currentX = currentBlock.x();
    int currentY = currentBlock.y();

    int nextX = nextBlock.x();
    int nextY = nextBlock.y();

    unitMatrix[nextX][nextY].stepCount = unitMatrix[currentX][currentY].stepCount + 1;
    unitMatrix[nextX][nextY].precursorBlock = currentBlock;
}

MazeBlock MazeMap::getPrecursorBlock(MazeBlock& currentBlock)
{
    return unitMatrix[currentBlock.x()][currentBlock.y()].precursorBlock;
}

void MazeMap::generateMaze()
{
    int initX = QRandomGenerator::global()->bounded(MAZE_ROWS);
    int initY = QRandomGenerator::global()->bounded(MAZE_COLS);

    QStack<MazeBlock> blockStack;
    MazeBlock currentBlock(initX, initY);

    setVisited(currentBlock);
    blockStack.push(currentBlock);

    while (!blockStack.isEmpty())
    {
        QList<MazeBlock> nearbyList = getNearbyList(currentBlock);

        if (nearbyList.isEmpty())
        {
            currentBlock = blockStack.pop();
            continue;
        }
        MazeBlock nextBlock = nearbyList[QRandomGenerator::global()->bounded(nearbyList.length())];

        removeWall(currentBlock, nextBlock);
        setVisited(nextBlock);
        blockStack.push(nextBlock);
        currentBlock = nextBlock;
    }
}

bool MazeMap::isHaveWall(int x, int y, Direct direct)
{
    return unitMatrix[x][y].isWall[(int)direct];
}

QList<MazeBlock> MazeMap::getWayBlockList(int initX, int initY)
{
    QQueue<MazeBlock> blockQueue;
    MazeBlock currentBlock(initX, initY);

    for (int x = 0; x < MAZE_ROWS; x++)
    {
        for (int y = 0; y < MAZE_COLS; y++)
        {
            unitMatrix[x][y].isVisited = false;
            unitMatrix[x][y].stepCount = 0;
        }
    }
    setVisited(currentBlock);
    blockQueue.enqueue(currentBlock);

    while (!blockQueue.isEmpty())
    {
        currentBlock = blockQueue.front();

        if (currentBlock.x() == MAZE_ROWS - 1 && currentBlock.y() == MAZE_COLS - 1)
        {
            break;
        }
        for (MazeBlock& nearbyBlock : getNearbyList(currentBlock))
        {
            if (!isHaveWall(currentBlock, nearbyBlock))
            {
                blockQueue.enqueue(nearbyBlock);
                setPrecursorBlock(currentBlock, nearbyBlock);
                setVisited(nearbyBlock);
            }
        }
        blockQueue.dequeue();
    }
    QList<MazeBlock> wayBlockList;

    for (int step = unitMatrix[currentBlock.x()][currentBlock.y()].stepCount; step >= 0; step--)
    {
        wayBlockList.append(currentBlock);
        currentBlock = getPrecursorBlock(currentBlock);
    }
    return wayBlockList;
}