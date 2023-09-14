#ifndef __MODELS_MAZE_H__
#define __MODELS_MAZE_H__

#include "map.h"
#include "player.h"

enum GameStatus
{
    STATUS_PLAYING,
    STATUS_OVER
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
        void setKeyStatus(bool[]);
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
        bool isPlaying();
        bool isGameover();
        bool isMapHaveWall(int, int, Direct);
};
#endif
