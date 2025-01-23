#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    this->gameFramework = nullptr;
    this->gameResources = nullptr;
}

void SceneWidget::paintMap(QPainter& painter)
{
    for (int row = 0; row < MapProperties::ROWS; row++)
    {
        for (int col = 0; col < MapProperties::COLS; col++)
        {
            for (int index = 0; index < MapProperties::WALL_COUNT; index++)
            {
                if (gameFramework->isMapHaveWall(row, col, index))
                {
                    int x = MapProperties::BLOCK_SIZE * row + MapProperties::BORDER - MapProperties::WALL_WIDTH;
                    int y = MapProperties::BLOCK_SIZE * col + MapProperties::BORDER - MapProperties::WALL_WIDTH;

                    painter.drawPixmap(x, y, *gameResources->getWallPixmap(index));
                }
            }
        }
    }
    int x = MapProperties::BLOCK_SIZE * (MapProperties::ROWS - 1) + MapProperties::BORDER;
    int y = MapProperties::BLOCK_SIZE * (MapProperties::COLS - 1) + MapProperties::BORDER;

    painter.drawPixmap(x, y, *gameResources->getFinishPixmap());
}

void SceneWidget::paintWay(QPainter& painter)
{
    for (MapBlock& wayBlock : paintedWayBlocks)
    {
        int x = wayBlock.getX() * MapProperties::BLOCK_SIZE + MapProperties::BORDER;
        int y = wayBlock.getY() * MapProperties::BLOCK_SIZE + MapProperties::BORDER;

        painter.drawPixmap(x, y, *gameResources->getWayPixmap());
    }
    if (!wayBlocks.isEmpty())
    {
        paintedWayBlocks.append(wayBlocks.takeLast());
    }
}

void SceneWidget::paintPlayer(QPainter& painter)
{
    int playerX = gameFramework->getPlayerX();
    int playerY = gameFramework->getPlayerY();

    painter.drawPixmap(playerX, playerY, *gameResources->getPlayerPixmap());
}

void SceneWidget::paintFog(QPainter& painter)
{
    int playerCenterX = gameFramework->getPlayerX() + MapProperties::BLOCK_SIZE / 2;
    int playerCenterY = gameFramework->getPlayerY() + MapProperties::BLOCK_SIZE / 2;

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

    if (gameFramework->isFogMode())
    {
        paintFog(painter);
    }
}

void SceneWidget::setGameFramework(GameFramework* gameFramework)
{
    this->gameFramework = gameFramework;
}

void SceneWidget::setGameResources(GameResources* gameResources)
{
    this->gameResources = gameResources;
}

void SceneWidget::clearWayBlocks()
{
    wayBlocks.clear();
    paintedWayBlocks.clear();
}

void SceneWidget::updateWayBlocks()
{
    wayBlocks = gameFramework->getWayBlocks();
    paintedWayBlocks.clear();
}
