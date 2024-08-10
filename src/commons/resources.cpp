#include "commons/resources.h"

GameResources::GameResources()
{
    pFinishPixmap = new QPixmap(":/images/finish.png");
    pPlayerPixmap = new QPixmap(":/images/player.png");
    pWayPixmap = new QPixmap(":/images/way.png");

    for (int index = 0; index < DirectIndex::COUNT; index++)
    {
        pWallPixmaps[index] = new QPixmap(QString(":/images/wall_%1.png").arg(index));
    }
}

GameResources::~GameResources()
{
    delete pFinishPixmap;
    delete pPlayerPixmap;
    delete pWayPixmap;

    for (int index = 0; index < DirectIndex::COUNT; index++)
    {
        delete pWallPixmaps[index];
    }
}

QPixmap* GameResources::getWayPixmap()
{
    return pWayPixmap;
}

QPixmap* GameResources::getFinishPixmap()
{
    return pFinishPixmap;
}

QPixmap* GameResources::getPlayerPixmap()
{
    return pPlayerPixmap;
}

QPixmap* GameResources::getWallPixmap(int index)
{
    return pWallPixmaps[index];
}
