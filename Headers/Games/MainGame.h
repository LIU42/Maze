#ifndef __GAMES_MAINGAME_H__
#define __GAMES_MAINGAME_H__

#include "Games/MazeMap.h"
#include "Games/Player.h"

enum class GameStatus
{
    STATUS_MAINLOOP,
    STATUS_GAMEOVER
};

class MainGame
{
    private:
        GameStatus status;

    private:
        MazeMap* pMazeMap;
        Player* pPlayer;

    private:
        bool isKeyPress[MazeBlockUnit::DIRECT_COUNT];
        bool isHaveTracked;

    public:
        MainGame();
        ~MainGame();

    public:
        void setKeyStatus(bool isKeyPress[]);
        void setTracked();
        void playerMove();
        void restart();

    public:
        QList<MazeBlock> getWayBlockList();

    public:
        int getPlayerX();
        int getPlayerY();

    public:
        bool getIsHaveTracked();
        bool isInMainLoop();
        bool isGameover();
        bool isMapHaveWall(int x, int y, Direct direct);
};
#endif
