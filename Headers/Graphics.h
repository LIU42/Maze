#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "Models/Maze.h"

class GameImages
{
    public:
        QPixmap way;
        QPixmap finish;
        QPixmap player;
        QPixmap wall[MazeBlockUnit::DIRECT_COUNT];
};

class GraphicsWidget : public QWidget
{
    Q_OBJECT

    private:
        static const int BORDER = 20;
        static const int WALL_WIDTH = 3;

    private:
        MainGame* pGame;

    private:
        GameImages images;
        MazeWayData wayData;

    private:
        int wayDisplayIndex;

    private:
        void paintMap(QPainter& painter);
        void paintWay(QPainter& painter);
        void paintPlayer(QPainter& painter);

    private:
        void paintEvent(QPaintEvent* pPaintEvent);

    public:
        GraphicsWidget(QWidget* parent = nullptr);

    public:
        void setGame(MainGame* pGame);
        void updateWayData();
        void clearWayData();
};
#endif