#ifndef __VIEWS_WIDGETS_SCENEWIDGET_H__
#define __VIEWS_WIDGETS_SCENEWIDGET_H__

#include <QPainter>
#include <QWidget>
#include <QRadialGradient>

#include "commons/resources.h"
#include "cores/environment.h"

class SceneWidget : public QWidget
{
    Q_OBJECT

    private:
        GameEnvironment* pGameEnvironment;
        GameResources* pGameResources;

    private:
        QList<MapBlock> wayBlocks;
        QRadialGradient* pRadialGradient;

    private:
        int wayBlocksPaintIndex;

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
        void setGameEnvironment(GameEnvironment* pGameEnvironment);
        void setGameResources(GameResources* pGameResources);

    public:
        void updateWayBlocks();
        void clearWayBlocks();
};
#endif
