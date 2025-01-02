#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pGameEnvironment = nullptr;
    pGameResources = nullptr;
}

void SceneWidget::paintMap(QPainter& painter)
{
    for (int row = 0; row < MapProperties::ROWS; row++)
    {
        for (int col = 0; col < MapProperties::COLS; col++)
        {
            for (int index = 0; index < DirectIndex::COUNT; index++)
            {
                if (pGameEnvironment->isMapHaveWall(row, col, index))
                {
                    int x = MapProperties::BLOCK_SIZE * row + MapProperties::BORDER - MapProperties::WALL_WIDTH;
                    int y = MapProperties::BLOCK_SIZE * col + MapProperties::BORDER - MapProperties::WALL_WIDTH;

                    painter.drawPixmap(x, y, *pGameResources->getWallPixmap(index));
                }
            }
        }
    }
    int x = MapProperties::BLOCK_SIZE * (MapProperties::ROWS - 1) + MapProperties::BORDER;
    int y = MapProperties::BLOCK_SIZE * (MapProperties::COLS - 1) + MapProperties::BORDER;

    painter.drawPixmap(x, y, *pGameResources->getFinishPixmap());
}

void SceneWidget::paintWay(QPainter& painter)
{
    if (wayBlocks.isEmpty())
    {
        return;
    }
    for (int i = wayBlocks.length() - 1; i >= wayBlocksPaintIndex; i--)
    {
        int x = wayBlocks[i].getX() * MapProperties::BLOCK_SIZE + MapProperties::BORDER;
        int y = wayBlocks[i].getY() * MapProperties::BLOCK_SIZE + MapProperties::BORDER;

        painter.drawPixmap(x, y, *pGameResources->getWayPixmap());
    }
    if (wayBlocksPaintIndex > 0)
    {
        wayBlocksPaintIndex -= 1;
    }
}

void SceneWidget::paintPlayer(QPainter& painter)
{
    int playerX = pGameEnvironment->getPlayerX();
    int playerY = pGameEnvironment->getPlayerY();

    painter.drawPixmap(playerX, playerY, *pGameResources->getPlayerPixmap());
}

void SceneWidget::paintFog(QPainter& painter)
{
    int playerCenterX = pGameEnvironment->getPlayerX() + MapProperties::BLOCK_SIZE / 2;
    int playerCenterY = pGameEnvironment->getPlayerY() + MapProperties::BLOCK_SIZE / 2;

    QRadialGradient radialGradient(playerCenterX, playerCenterY, MapProperties::VISIBLE_RADIUS);

    radialGradient.setColorAt(1, Qt::black);
    radialGradient.setColorAt(0, Qt::transparent);

    painter.fillRect(0, 0, SceneProperties::WIDTH, SceneProperties::HEIGHT, radialGradient);
}

void SceneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paintWay(painter);
    paintMap(painter);
    paintPlayer(painter);

    if (pGameEnvironment->isFogMode())
    {
        paintFog(painter);
    }
}

void SceneWidget::setGameEnvironment(GameEnvironment* pGameEnvironment)
{
    this->pGameEnvironment = pGameEnvironment;
}

void SceneWidget::setGameResources(GameResources* pGameResources)
{
    this->pGameResources = pGameResources;
}

void SceneWidget::updateWayBlocks()
{
    wayBlocks = pGameEnvironment->getWayBlocks();
    wayBlocksPaintIndex = wayBlocks.length();
}

void SceneWidget::clearWayBlocks()
{
    wayBlocks.clear();
    wayBlocksPaintIndex = 0;
}
