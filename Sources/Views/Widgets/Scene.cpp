#include "Views/Widgets/Scene.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pImages = ResourceManager::getImages();
}

void SceneWidget::paintMap(QPainter& painter)
{
    for (int i = 0; i < Map::MAP_ROWS; i++)
    {
        for (int j = 0; j < Map::MAP_COLS; j++)
        {
            for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
            {
                if (pMainGame->isMapHaveWall(i, j, (Direct)index))
                {
                    int x = MapUnit::BLOCK_SIZE * i + REGION_BORDER - WALL_WIDTH;
                    int y = MapUnit::BLOCK_SIZE * j + REGION_BORDER - WALL_WIDTH;

                    painter.drawPixmap(x, y, *pImages->getWallPixmap(index));
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
    int playerX = pMainGame->getPlayerX();
    int playerY = pMainGame->getPlayerY();

    painter.drawPixmap(playerX, playerY, *pImages->getPlayerPixmap());
}

void SceneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paintWay(painter);
    paintMap(painter);
    paintPlayer(painter);
}

void SceneWidget::setMainGame(MainGame* pMainGame)
{
    this->pMainGame = pMainGame;
}

void SceneWidget::updateWay()
{
    wayBlockList = pMainGame->getWayBlockList();
    wayBlocksPaintIndex = wayBlockList.length() - 1;
}

void SceneWidget::clearWay()
{
    wayBlockList.clear();
    wayBlocksPaintIndex = 0;
}
