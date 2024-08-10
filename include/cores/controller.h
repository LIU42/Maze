#ifndef __CORES_CONTROLLER_H__
#define __CORES_CONTROLLER_H__

#include "cores/map.h"
#include "cores/player.h"

class GameController
{
    private:
        bool* pKeyInputs;

    private:
        Map* pMap;
        Player* pPlayer;

    private:
        bool gameover;
        bool tracked;

    public:
        GameController(bool* pKeyInputs);
        ~GameController();

    public:
        void playerMove();
        void restart();

    public:
        QList<MapBlock> getWayBlocks();

    public:
        int getPlayerX();
        int getPlayerY();

    public:
        bool hasTracked();
        bool isPlaying();
        bool isGameover();
        bool isMapHaveWall(int x, int y, int directIndex);
};
#endif
