#include "maze.h"

void MainGame::setKeyStatus(bool isKeyPress[])
{
    for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
    {
        this->isKeyPress[direct] = isKeyPress[direct];
    }
}

void MainGame::setTracked()
{
    isHaveTracked = true;
}

void MainGame::restart()
{
    map.initUnitMatrix();
    map.generateMaze();
    player.setMap(&map);
    player.reset();
    status = STATUS_PROGRESS;
    isHaveTracked = false;
}

void MainGame::playerMove()
{
    player.setIsOnMove(false);

    for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
    {
        if (isKeyPress[direct])
        {
            player.setIsOnMove(true);
            player.setForwardDirect((Direct)direct);
        }
    }
    player.move();
}

MazeWayData MainGame::getWayData()
{
    if (status == STATUS_PROGRESS)
    {
        int playerX = qRound(player.getRelativeX());
        int playerY = qRound(player.getRelativeY());

        wayData = map.getWayData(playerX, playerY);
        isHaveTracked = true;
    }
    return wayData;
}

int MainGame::getPlayerX()
{
    return player.getPositionX();
}

int MainGame::getPlayerY()
{
    return player.getPositionY();
}

bool MainGame::getIsHaveTracked()
{
    return isHaveTracked;
}

bool MainGame::isPlaying()
{
    return status == STATUS_PROGRESS;
}

bool MainGame::isGameover()
{
    double playerX = player.getRelativeX();
    double playerY = player.getRelativeY();

    if (playerX == Map::ROWS - 1 && playerY == Map::COLS - 1)
    {
        status = STATUS_OVER;
        return true;
    }
    return false;
}

bool MainGame::isMapHaveWall(int x, int y, Direct direct)
{
    return map.isHaveWall(x, y, direct);
}
