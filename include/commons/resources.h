#ifndef __COMMONS_RESOURCES_H__
#define __COMMONS_RESOURCES_H__

#include <QPixmap>

#include "commons/constants.h"

class GameResources
{
    private:
        QPixmap* pFinishPixmap;
        QPixmap* pPlayerPixmap;
        QPixmap* pWayPixmap;
        QPixmap* pWallPixmaps[DirectIndex::COUNT];

    public:
        GameResources();
        ~GameResources();

    public:
        QPixmap* getFinishPixmap();
        QPixmap* getPlayerPixmap();
        QPixmap* getWayPixmap();
        QPixmap* getWallPixmap(int directIndex);
};
#endif
