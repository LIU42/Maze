#ifndef __MODELS_MAZE_H__
#define __MODELS_MAZE_H__

#include "Models/Map.h"
#include "Models/Player.h"

enum GameStatus
{
    STATUS_MAINLOOP,
    STATUS_GAMEOVER
};

class MainGame
{
    private:
        MazeWayData wayData;
        GameStatus status;

    private:
        Map map;
        Player player;

    private:
        bool isKeyPress[MazeBlockUnit::DIRECT_COUNT];
        bool isHaveTracked;

    public:
        void setKeyStatus(bool isKeyPress[]);
        void setTracked();
        void playerMove();
        void restart();

    public:
        MazeWayData getWayData();

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
