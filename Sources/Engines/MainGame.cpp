#include "Engines/MainGame.h"

MainGame::MainGame(bool* pKeyPress)
{
    this->pKeyPress = pKeyPress;

    pMap = new Map();
    pPlayer = new Player(pMap);
}

MainGame::~MainGame()
{
    delete pMap;
    delete pPlayer;
}

void MainGame::setTracked()
{
    tracked = true;
}

void MainGame::restart()
{
    status = GameStatus::STATUS_MAINLOOP;
    tracked = false;

    pMap->initUnits();
    pMap->generateMaze();
    pPlayer->reset();
}

void MainGame::playerMove()
{
    pPlayer->setMoveStop();

    for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
    {
        if (pKeyPress[index])
        {
            pPlayer->setMoveStart();
            pPlayer->setForwardDirect((Direct)index);
        }
    }
    pPlayer->move();
}

QList<MapBlock> MainGame::getWayBlockList()
{
    tracked = true;

    int playerX = qRound(pPlayer->getFloatIndexX());
    int playerY = qRound(pPlayer->getFloatIndexY());

    return pMap->getWayBlockList(playerX, playerY);
}

int MainGame::getPlayerX()
{
    return pPlayer->getX();
}

int MainGame::getPlayerY()
{
    return pPlayer->getY();
}

bool MainGame::hasTracked()
{
    return tracked;
}

bool MainGame::isInMainLoop()
{
    return status == GameStatus::STATUS_MAINLOOP;
}

bool MainGame::isGameover()
{
    double playerX = pPlayer->getFloatIndexX();
    double playerY = pPlayer->getFloatIndexY();

    if (playerX == Map::MAP_ROWS - 1 && playerY == Map::MAP_COLS - 1)
    {
        status = GameStatus::STATUS_GAMEOVER;
        return true;
    }
    return false;
}

bool MainGame::isMapHaveWall(int x, int y, Direct direct)
{
    return pMap->hasWall(x, y, direct);
}
