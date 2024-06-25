#ifndef __ENGINES_MAINGAME_H__
#define __ENGINES_MAINGAME_H__

#include "Engines/Map.h"
#include "Engines/Player.h"

enum class GameStatus
{
    STATUS_MAINLOOP,
    STATUS_GAMEOVER,
};

class MainGame
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
        MainGame(bool* pKeyPress);
        ~MainGame();

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
