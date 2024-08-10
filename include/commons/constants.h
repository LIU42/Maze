#ifndef __COMMONS_CONSTANTS_H__
#define __COMMONS_CONSTANTS_H__

class DirectIndex
{
    public:
        static constexpr int COUNT = 4;
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
};

class PlayerProperties
{
    public:
        static constexpr int START_X = 16;
        static constexpr int START_Y = 16;
        static constexpr int MOVE_SPEED = 4;
};

class Interval
{
    public:
        static constexpr int CLOCK = 1000;
        static constexpr int FRAME = 16;
};

#endif
