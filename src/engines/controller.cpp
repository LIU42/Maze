#include "engines/controller.h"

GameController::GameController(bool* pKeyPress)
{
    this->pKeyPress = pKeyPress;

    pMap = new Map();
    pPlayer = new Player(pMap);
}

GameController::~GameController()
{
    delete pMap;
    delete pPlayer;
}

void GameController::setTracked()
{
    tracked = true;
}

void GameController::restart()
{
    status = GameStatus::MAINLOOP;
    tracked = false;

    pMap->initUnits();
    pMap->generateMaze();
    pPlayer->reset();
}

void GameController::playerMove()
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

QList<MapBlock> GameController::getWayBlockList()
{
    tracked = true;

    int playerX = qRound(pPlayer->getFloatIndexX());
    int playerY = qRound(pPlayer->getFloatIndexY());

    return pMap->getWayBlockList(playerX, playerY);
}

int GameController::getPlayerX()
{
    return pPlayer->getX();
}

int GameController::getPlayerY()
{
    return pPlayer->getY();
}

bool GameController::hasTracked()
{
    return tracked;
}

bool GameController::isInMainLoop()
{
    return status == GameStatus::MAINLOOP;
}

bool GameController::isGameover()
{
    double playerX = pPlayer->getFloatIndexX();
    double playerY = pPlayer->getFloatIndexY();

    if (playerX == Map::MAP_ROWS - 1 && playerY == Map::MAP_COLS - 1)
    {
        status = GameStatus::GAMEOVER;
        return true;
    }
    return false;
}

bool GameController::isMapHaveWall(int x, int y, Direct direct)
{
    return pMap->hasWall(x, y, direct);
}
