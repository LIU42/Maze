#ifndef __UTILS_CONSTANTS_H__
#define __UTILS_CONSTANTS_H__

class Directs
{
    public:
        static constexpr int UP = 0;
        static constexpr int DOWN = 1;
        static constexpr int LEFT = 2;
        static constexpr int RIGHT = 3;
};

class MapProperties
{
    public:
        static constexpr int BORDER = 16;
        static constexpr int ROWS = 30;
        static constexpr int COLS = 20;
        static constexpr int BLOCK_SIZE = 24;
        static constexpr int WALL_WIDTH = 2;
        static constexpr int WALL_COUNT = 4;
        static constexpr int VISIBLE_RADIUS = 150;
};

class PlayerProperties
{
    public:
        static constexpr int START_X = 16;
        static constexpr int START_Y = 16;
        static constexpr int MOVE_SPEED = 4;
};

class TimerInterval
{
    public:
        static constexpr int CLOCK = 1000;
        static constexpr int FRAME = 16;
};

class SceneProperties
{
    public:
        static constexpr int WIDTH = 752;
        static constexpr int HEIGHT = 512;
};
#endif
