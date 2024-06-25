#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "Games/MainGame.h"

class GameImages
{
    public:
        QPixmap* pWayPixmap;
        QPixmap* pFinishPixmap;
        QPixmap* pPlayerPixmap;
        QPixmap* pWallPixmaps[MazeBlockUnit::DIRECT_COUNT];

    public:
        GameImages();
        ~GameImages();
};

class GraphicsWidget : public QWidget
{
    Q_OBJECT

    private:
        static constexpr int REGION_BORDER = 16;
        static constexpr int WALL_WIDTH = 2;

    private:
        MainGame* pMainGame;
        GameImages* pGameImages;

    private:
        QList<MazeBlock> wayBlockList;
        int wayBlockPaintIndex;

    private:
        void paintMazeMap(QPainter& painter);
        void paintWayBlock(QPainter& painter);
        void paintPlayer(QPainter& painter);

    private:
        void paintEvent(QPaintEvent*) override;

    public:
        GraphicsWidget(QWidget* parent = nullptr);
        ~GraphicsWidget();

    public:
        void setMainGame(MainGame* pMainGame);
        void updateWayBlockList();
        void clearWayBlockList();
};
#endif