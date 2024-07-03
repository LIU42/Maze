#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pImages = ResourceManager::getImages();
}

void SceneWidget::paintMap(QPainter& painter)
{
    for (int row = 0; row < Map::MAP_ROWS; row++)
    {
        for (int col = 0; col < Map::MAP_COLS; col++)
        {
            for (int directCode = 0; directCode < MapUnit::DIRECT_COUNT; directCode++)
            {
                if (pGameController->isMapHaveWall(row, col, (Direct)directCode))
                {
                    int x = MapUnit::BLOCK_SIZE * row + REGION_BORDER - WALL_WIDTH;
                    int y = MapUnit::BLOCK_SIZE * col + REGION_BORDER - WALL_WIDTH;

                    painter.drawPixmap(x, y, *pImages->getWallPixmap(directCode));
                }
            }
        }
    }
    int x = MapUnit::BLOCK_SIZE * (Map::MAP_ROWS - 1) + REGION_BORDER;
    int y = MapUnit::BLOCK_SIZE * (Map::MAP_COLS - 1) + REGION_BORDER;

    painter.drawPixmap(x, y, *pImages->getFinishPixmap());
}

void SceneWidget::paintWay(QPainter& painter)
{
    if (wayBlockList.isEmpty())
    {
        return;
    }
    for (int i = wayBlockList.length() - 1; i >= wayBlocksPaintIndex; i--)
    {
        int x = wayBlockList[i].getX() * MapUnit::BLOCK_SIZE + REGION_BORDER;
        int y = wayBlockList[i].getY() * MapUnit::BLOCK_SIZE + REGION_BORDER;

        painter.drawPixmap(x, y, *pImages->getWayPixmap());
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

    painter.drawPixmap(playerX, playerY, *pImages->getPlayerPixmap());
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

void SceneWidget::updateWay()
{
    wayBlockList = pGameController->getWayBlockList();
    wayBlocksPaintIndex = wayBlockList.length() - 1;
}

void SceneWidget::clearWay()
{
    wayBlockList.clear();
    wayBlocksPaintIndex = 0;
}
