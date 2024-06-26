#ifndef __VIEWS_WIDGETS_SCENE_H__
#define __VIEWS_WIDGETS_SCENE_H__

#include <QPainter>
#include <QWidget>

#include "engines/controller.h"
#include "modules/resources.h"

class SceneWidget : public QWidget
{
    Q_OBJECT

    private:
        static constexpr int REGION_BORDER = 16;
        static constexpr int WALL_WIDTH = 2;

    private:
        GameController* pGameController;
        ResourceImages* pImages;

    private:
        QList<MapBlock> wayBlockList;

    private:
        int wayBlocksPaintIndex;

    private:
        void paintMap(QPainter& painter);
        void paintWay(QPainter& painter);
        void paintPlayer(QPainter& painter);

    private:
        void paintEvent(QPaintEvent*) override;

    public:
        SceneWidget(QWidget* parent = nullptr);

    public:
        void setGameController(GameController* pGameController);
        void updateWay();
        void clearWay();
};
#endif
