#ifndef __VIEWS_WIDGETS_SCENEWIDGET_H__
#define __VIEWS_WIDGETS_SCENEWIDGET_H__

#include <QPainter>
#include <QWidget>

#include "commons/resources.h"
#include "cores/controller.h"

class SceneWidget : public QWidget
{
    Q_OBJECT

    private:
        GameController* pGameController;
        GameResources* pGameResources;

    private:
        QList<MapBlock> wayBlocks;

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
        void setGameResources(GameResources* pGameResources);

    public:
        void updateWayBlocks();
        void clearWayBlocks();
};
#endif
