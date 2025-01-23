#include "utils/resources.h"

GameResources::GameResources()
{
    playerPixmap = new QPixmap(":/images/player.png");
    finishPixmap = new QPixmap(":/images/finish.png");

    for (int index = 0; index < MapProperties::WALL_COUNT; index++)
    {
        wallPixmaps[index] = new QPixmap(QString(":/images/wall_%1.png").arg(index));
    }
    wayPixmap = new QPixmap(":/images/way.png");
}

GameResources::~GameResources()
{
    delete playerPixmap;
    delete finishPixmap;

    for (int index = 0; index < MapProperties::WALL_COUNT; index++)
    {
        delete wallPixmaps[index];
    }
    delete wayPixmap;
}

const QPixmap* GameResources::getWayPixmap()
{
    return wayPixmap;
}

const QPixmap* GameResources::getFinishPixmap()
{
    return finishPixmap;
}

const QPixmap* GameResources::getPlayerPixmap()
{
    return playerPixmap;
}

const QPixmap* GameResources::getWallPixmap(int index)
{
    return wallPixmaps[index];
}
