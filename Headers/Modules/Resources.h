#ifndef __MODULES_RESOURCES_H__
#define __MODULES_RESOURCES_H__

#include <QPixmap>

#include "Engines/Map.h"

class ResourceImages
{
    private:
        QPixmap* pFinishPixmap;
        QPixmap* pPlayerPixmap;
        QPixmap* pWayPixmap;
        QPixmap* pWallPixmaps[MapUnit::DIRECT_COUNT];

    public:
        ResourceImages();
        ~ResourceImages();

    public:
        QPixmap* getFinishPixmap();
        QPixmap* getPlayerPixmap();
        QPixmap* getWayPixmap();
        QPixmap* getWallPixmap(int index);
};

class ResourceManager
{
    private:
        static ResourceImages* pImages;

    public:
        static void load();
        static void release();

    public:
        static ResourceImages* getImages();
};
#endif
