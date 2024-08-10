#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pGameController = nullptr;
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
                if (pGameController->isMapHaveWall(row, col, index))
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
    int playerX = pGameController->getPlayerX();
    int playerY = pGameController->getPlayerY();

    painter.drawPixmap(playerX, playerY, *pGameResources->getPlayerPixmap());
}

void SceneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paintWay(painter);
    paintMap(painter);
    paintPlayer(painter);
}

void SceneWidget::setGameController(GameController* pGameController)
{
    this->pGameController = pGameController;
}

void SceneWidget::setGameResources(GameResources* pGameResources)
{
    this->pGameResources = pGameResources;
}

void SceneWidget::updateWayBlocks()
{
    wayBlocks = pGameController->getWayBlocks();
    wayBlocksPaintIndex = wayBlocks.length();
}

void SceneWidget::clearWayBlocks()
{
    wayBlocks.clear();
    wayBlocksPaintIndex = 0;
}
