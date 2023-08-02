#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "maze.h"

class GameImages
{
    friend class GraphicsWidget;

    private:
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
        void displayMap(QPainter&);
        void displayWay(QPainter&);
        void displayPlayer(QPainter&);

    private:
        void paintEvent(QPaintEvent*);

    public:
        GraphicsWidget(QWidget* parent = nullptr);

    public:
        void setGame(MainGame*);
        void updateWayData();
        void clearWayData();
};
#endif