#include "cores/framework.h"

GameFramework::GameFramework()
{
    this->map = new Map();
    this->player = new Player(map);
    this->fogMode = false;
    this->tracked = false;
    this->gameover = false;
}

GameFramework::~GameFramework()
{
    delete map;
    delete player;
}

void GameFramework::restart()
{
    player->reset();
    map->reset();
    map->generateMaze();
    tracked = false;
    gameover = false;
}

void GameFramework::playerMove(QList<int>& directPriority)
{
    bool isMoveSuccess = false;

    for (int index = directPriority.size() - 1; index >= 0; index--)
    {
        if (directPriority[index] == Directs::UP)
        {
            isMoveSuccess = player->moveUp();
        }
        else if (directPriority[index] == Directs::DOWN)
        {
            isMoveSuccess = player->moveDown();
        }
        else if (directPriority[index] == Directs::LEFT)
        {
            isMoveSuccess = player->moveLeft();
        }
        else if (directPriority[index] == Directs::RIGHT)
        {
            isMoveSuccess = player->moveRight();
        }
        if (isMoveSuccess)
        {
            player->updateLocationInfo();
            return;
        }
    }
}

void GameFramework::switchFogMode()
{
    fogMode = !fogMode;
}

QList<MapBlock> GameFramework::getWayBlocks()
{
    tracked = true;

    int playerX = qRound(player->getFloatLocationX());
    int playerY = qRound(player->getFloatLocationY());

    return map->getWayBlocks(playerX, playerY);
}

int GameFramework::getPlayerX()
{
    return player->getX();
}

int GameFramework::getPlayerY()
{
    return player->getY();
}

bool GameFramework::hasTracked()
{
    return tracked;
}

bool GameFramework::isFogMode()
{
    return fogMode;
}

bool GameFramework::isPlaying()
{
    return !gameover;
}

bool GameFramework::isGameover()
{
    double playerX = player->getFloatLocationX();
    double playerY = player->getFloatLocationY();

    if (playerX == MapProperties::ROWS - 1 && playerY == MapProperties::COLS - 1)
    {
        gameover = true;
    }
    return gameover;
}

bool GameFramework::isMapHaveWall(int x, int y, int direct)
{
    return map->hasWall(x, y, direct);
}
