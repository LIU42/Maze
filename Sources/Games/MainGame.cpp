#include "Games/MainGame.h"

MainGame::MainGame()
{
    pMazeMap = new MazeMap();
    pPlayer = new Player(pMazeMap);
}

MainGame::~MainGame()
{
    delete pMazeMap;
    delete pPlayer;
}

void MainGame::setKeyStatus(bool isKeyPress[])
{
    for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
    {
        this->isKeyPress[index] = isKeyPress[index];
    }
}

void MainGame::setTracked()
{
    isHaveTracked = true;
}

void MainGame::restart()
{
    pMazeMap->initUnitMatrix();
    pMazeMap->generateMaze();
    pPlayer->resetPlayer();
    status = GameStatus::STATUS_MAINLOOP;
    isHaveTracked = false;
}

void MainGame::playerMove()
{
    pPlayer->setMoveStop();

    for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
    {
        if (isKeyPress[index])
        {
            pPlayer->setMoveStart();
            pPlayer->setForwardDirect((Direct)index);
        }
    }
    pPlayer->playerMove();
}

QList<MazeBlock> MainGame::getWayBlockList()
{
    isHaveTracked = true;

    int playerX = qRound(pPlayer->getFloatIndexX());
    int playerY = qRound(pPlayer->getFloatIndexY());

    return pMazeMap->getWayBlockList(playerX, playerY);
}

int MainGame::getPlayerX()
{
    return pPlayer->getPositionX();
}

int MainGame::getPlayerY()
{
    return pPlayer->getPositionY();
}

bool MainGame::getIsHaveTracked()
{
    return isHaveTracked;
}

bool MainGame::isInMainLoop()
{
    return status == GameStatus::STATUS_MAINLOOP;
}

bool MainGame::isGameover()
{
    double playerX = pPlayer->getFloatIndexX();
    double playerY = pPlayer->getFloatIndexY();

    if (playerX == MazeMap::MAZE_ROWS - 1 && playerY == MazeMap::MAZE_COLS - 1)
    {
        status = GameStatus::STATUS_GAMEOVER;
        return true;
    }
    return false;
}

bool MainGame::isMapHaveWall(int x, int y, Direct direct)
{
    return pMazeMap->isHaveWall(x, y, direct);
}
