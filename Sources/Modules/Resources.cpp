#include "Modules/Resources.h"

ResourceImages* ResourceManager::pImages = nullptr;

ResourceImages::ResourceImages()
{
    pFinishPixmap = new QPixmap(":/Images/finish.png");
    pPlayerPixmap = new QPixmap(":/Images/player.png");
    pWayPixmap = new QPixmap(":/Images/way.png");

    for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
    {
        pWallPixmaps[index] = new QPixmap(QString(":/Images/wall_%1.png").arg(index));
    }
}

ResourceImages::~ResourceImages()
{
    delete pFinishPixmap;
    delete pPlayerPixmap;
    delete pWayPixmap;

    for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
    {
        delete pWallPixmaps[index];
    }
}

QPixmap* ResourceImages::getWayPixmap()
{
    return pWayPixmap;
}

QPixmap* ResourceImages::getFinishPixmap()
{
    return pFinishPixmap;
}

QPixmap* ResourceImages::getPlayerPixmap()
{
    return pPlayerPixmap;
}

QPixmap* ResourceImages::getWallPixmap(int index)
{
    return pWallPixmaps[index];
}

void ResourceManager::load()
{
    pImages = new ResourceImages();
}

void ResourceManager::release()
{
    delete pImages;
}

ResourceImages* ResourceManager::getImages()
{
    return pImages;
}
