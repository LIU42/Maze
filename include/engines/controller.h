#ifndef __ENGINES_GAME_H__
#define __ENGINES_GAME_H__

#include "engines/map.h"
#include "engines/player.h"

enum class GameStatus
{
    MAINLOOP,
    GAMEOVER,
};

class GameController
{
    private:
        GameStatus status;

    private:
        Map* pMap;
        Player* pPlayer;

    private:
        bool* pKeyPress;
        bool tracked;

    public:
        GameController(bool* pKeyPress);
        ~GameController();

    public:
        void setTracked();
        void playerMove();
        void restart();

    public:
        QList<MapBlock> getWayBlockList();

    public:
        int getPlayerX();
        int getPlayerY();

    public:
        bool hasTracked();
        bool isInMainLoop();
        bool isGameover();
        bool isMapHaveWall(int x, int y, Direct direct);
};
#endif
