#include "maze.h"

void MainGame::setKeyStatus(bool isKeyPress[])
{
    for (int key = UP; key <= RIGHT; key++)
    {
        this->isKeyPress[key] = isKeyPress[key];
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
    status = PLAYING;
    isHaveTracked = false;
}

void MainGame::playerMove()
{
    player.setIsOnMove(false);

    for (int direct = UP; direct <= RIGHT; direct++)
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
    if (status == PLAYING)
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
    return status == PLAYING;
}

bool MainGame::isGameover()
{
    double playerX = player.getRelativeX();
    double playerY = player.getRelativeY();

    if (playerX == Map::ROWS - 1 && playerY == Map::COLS - 1)
    {
        status = OVER;
        return true;
    }
    return false;
}

bool MainGame::isMapHaveWall(int x, int y, Direct direct)
{
    return map.isHaveWall(x, y, direct);
}
