#ifndef __CORES_FRAMEWORK_H__
#define __CORES_FRAMEWORK_H__

#include <QList>

#include "cores/map.h"
#include "cores/player.h"

class GameFramework
{
    private:
        Map* map;
        Player* player;

    private:
        bool tracked;
        bool fogMode;
        bool gameover;

    public:
        GameFramework();
        ~GameFramework();

    public:
        void playerMove(QList<int>& directPriority);
        void restart();
        void switchFogMode();

    public:
        QList<MapBlock> getWayBlocks();

    public:
        int getPlayerX();
        int getPlayerY();

    public:
        bool hasTracked();
        bool isFogMode();
        bool isPlaying();
        bool isGameover();
        bool isMapHaveWall(int x, int y, int direct);
};
#endif
