#include "Models/Maze.h"

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
    status = STATUS_MAINLOOP;
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
    if (status == STATUS_MAINLOOP)
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

bool MainGame::isInMainLoop()
{
    return status == STATUS_MAINLOOP;
}

bool MainGame::isGameover()
{
    double playerX = player.getRelativeX();
    double playerY = player.getRelativeY();

    if (playerX == Map::ROWS - 1 && playerY == Map::COLS - 1)
    {
        status = STATUS_GAMEOVER;
        return true;
    }
    return false;
}

bool MainGame::isMapHaveWall(int x, int y, Direct direct)
{
    return map.isHaveWall(x, y, direct);
}
