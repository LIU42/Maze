#ifndef __VIEWS_WIDGETS_SCENEWIDGET_H__
#define __VIEWS_WIDGETS_SCENEWIDGET_H__

#include <QPainter>
#include <QWidget>
#include <QRadialGradient>

#include "cores/framework.h"
#include "utils/resources.h"

class SceneWidget : public QWidget
{
    Q_OBJECT

    private:
        QList<MapBlock> wayBlocks;
        QList<MapBlock> paintedWayBlocks;

    private:
        GameFramework* gameFramework;
        GameResources* gameResources;

    private:
        void paintMap(QPainter& painter);
        void paintWay(QPainter& painter);
        void paintFog(QPainter& painter);
        void paintPlayer(QPainter& painter);

    private:
        void paintEvent(QPaintEvent*) override;

    public:
        SceneWidget(QWidget* parent = nullptr);

    public:
        void setGameFramework(GameFramework* gameFramework);
        void setGameResources(GameResources* gameResources);

    public:
        void clearWayBlocks();
        void updateWayBlocks();
};
#endif
