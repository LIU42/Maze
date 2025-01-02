#include "cores/environment.h"

GameEnvironment::GameEnvironment(bool* pKeyInputs)
{
    this->pKeyInputs = pKeyInputs;
    this->pMap = new Map();
    this->pPlayer = new Player(pMap);
}

GameEnvironment::~GameEnvironment()
{
    delete pMap;
    delete pPlayer;
}

void GameEnvironment::restart()
{
    gameover = false;
    tracked = false;
    fogMode = false;

    pMap->initUnits();
    pMap->generateMaze();
    pPlayer->reset();
}

void GameEnvironment::playerMove()
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

void GameEnvironment::switchFogMode()
{
    fogMode = !fogMode;
}

QList<MapBlock> GameEnvironment::getWayBlocks()
{
    tracked = true;

    int playerX = qRound(pPlayer->getFloatLocationX());
    int playerY = qRound(pPlayer->getFloatLocationY());

    return pMap->getWayBlocks(playerX, playerY);
}

int GameEnvironment::getPlayerX()
{
    return pPlayer->getX();
}

int GameEnvironment::getPlayerY()
{
    return pPlayer->getY();
}

bool GameEnvironment::hasTracked()
{
    return tracked;
}

bool GameEnvironment::isFogMode()
{
    return fogMode;
}

bool GameEnvironment::isPlaying()
{
    return !gameover;
}

bool GameEnvironment::isGameover()
{
    double playerX = pPlayer->getFloatLocationX();
    double playerY = pPlayer->getFloatLocationY();

    if (playerX == MapProperties::ROWS - 1 && playerY == MapProperties::COLS - 1)
    {
        gameover = true;
    }
    return gameover;
}

bool GameEnvironment::isMapHaveWall(int x, int y, int directIndex)
{
    return pMap->hasWall(x, y, directIndex);
}
