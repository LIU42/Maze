#include "cores/controller.h"

GameController::GameController(bool* pKeyInputs)
{
    this->pKeyInputs = pKeyInputs;
    this->pMap = new Map();
    this->pPlayer = new Player(pMap);
}

GameController::~GameController()
{
    delete pMap;
    delete pPlayer;
}

void GameController::restart()
{
    gameover = false;
    tracked = false;

    pMap->initUnits();
    pMap->generateMaze();
    pPlayer->reset();
}

void GameController::playerMove()
{
    pPlayer->moveStop();

    for (int index = 0; index < DirectIndex::COUNT; index++)
    {
        if (pKeyInputs[index])
        {
            pPlayer->setDirect(index);
            pPlayer->moveStart();
        }
    }
    pPlayer->move();
}

QList<MapBlock> GameController::getWayBlocks()
{
    tracked = true;

    int playerX = qRound(pPlayer->getFloatLocationX());
    int playerY = qRound(pPlayer->getFloatLocationY());

    return pMap->getWayBlocks(playerX, playerY);
}

int GameController::getPlayerX()
{
    return pPlayer->getX();
}

int GameController::getPlayerY()
{
    return pPlayer->getY();
}

bool GameController::isPlaying()
{
    return !gameover;
}

bool GameController::hasTracked()
{
    return tracked;
}

bool GameController::isGameover()
{
    double playerX = pPlayer->getFloatLocationX();
    double playerY = pPlayer->getFloatLocationY();

    if (playerX == MapProperties::ROWS - 1 && playerY == MapProperties::COLS - 1)
    {
        gameover = true;
    }
    return gameover;
}

bool GameController::isMapHaveWall(int x, int y, int directIndex)
{
    return pMap->hasWall(x, y, directIndex);
}
