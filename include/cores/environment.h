#ifndef __CORES_ENVIRONMENT_H__
#define __CORES_ENVIRONMENT_H__

#include "cores/map.h"
#include "cores/player.h"

class GameEnvironment
{
    private:
        bool* pKeyInputs;

    private:
        Map* pMap;
        Player* pPlayer;

    private:
        bool gameover;
        bool tracked;
        bool fogMode;

    public:
        GameEnvironment(bool* pKeyInputs);
        ~GameEnvironment();

    public:
        void playerMove();
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
        bool isMapHaveWall(int x, int y, int directIndex);
};
#endif
