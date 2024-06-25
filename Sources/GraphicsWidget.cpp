#include "Graphics.h"

GameImages::GameImages()
{
    pWayPixmap = new QPixmap(":/Images/way.png");
    pFinishPixmap = new QPixmap(":/Images/finish.png");
    pPlayerPixmap = new QPixmap(":/Images/player.png");

    for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
    {
        pWallPixmaps[index] = new QPixmap(QString(":/Images/wall_%1.png").arg(index));
    }
}

GameImages::~GameImages()
{
    delete pWayPixmap;
    delete pFinishPixmap;
    delete pPlayerPixmap;

    for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
    {
        delete pWallPixmaps[index];
    }
}

GraphicsWidget::GraphicsWidget(QWidget* parent): QWidget(parent)
{
    pGameImages = new GameImages();
}

GraphicsWidget::~GraphicsWidget()
{
    delete pGameImages;
}

void GraphicsWidget::paintMazeMap(QPainter& painter)
{
    for (int i = 0; i < MazeMap::MAZE_ROWS; i++)
    {
        for (int j = 0; j < MazeMap::MAZE_COLS; j++)
        {
            for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
            {
                if (pMainGame->isMapHaveWall(i, j, (Direct)index))
                {
                    int x = MazeBlockUnit::BLOCK_SIZE * i + REGION_BORDER - WALL_WIDTH;
                    int y = MazeBlockUnit::BLOCK_SIZE * j + REGION_BORDER - WALL_WIDTH;

                    painter.drawPixmap(x, y, *pGameImages->pWallPixmaps[index]);
                }
            }
        }
    }
    int x = MazeBlockUnit::BLOCK_SIZE * (MazeMap::MAZE_ROWS - 1) + REGION_BORDER;
    int y = MazeBlockUnit::BLOCK_SIZE * (MazeMap::MAZE_COLS - 1) + REGION_BORDER;

    painter.drawPixmap(x, y, *pGameImages->pFinishPixmap);
}

void GraphicsWidget::paintWayBlock(QPainter& painter)
{
    if (wayBlockList.isEmpty())
    {
        return;
    }
    for (int i = wayBlockList.length() - 1; i >= wayBlockPaintIndex; i--)
    {
        int x = wayBlockList[i].x() * MazeBlockUnit::BLOCK_SIZE + REGION_BORDER;
        int y = wayBlockList[i].y() * MazeBlockUnit::BLOCK_SIZE + REGION_BORDER;

        painter.drawPixmap(x, y, *pGameImages->pWayPixmap);
    }
    if (wayBlockPaintIndex > 0)
    {
        wayBlockPaintIndex -= 1;
    }
}

void GraphicsWidget::paintPlayer(QPainter& painter)
{
    int playerX = pMainGame->getPlayerX();
    int playerY = pMainGame->getPlayerY();

    painter.drawPixmap(playerX, playerY, *pGameImages->pPlayerPixmap);
}

void GraphicsWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    paintWayBlock(painter);
    paintMazeMap(painter);
    paintPlayer(painter);
}

void GraphicsWidget::setMainGame(MainGame* pMainGame)
{
    this->pMainGame = pMainGame;
}

void GraphicsWidget::updateWayBlockList()
{
    wayBlockList = pMainGame->getWayBlockList();
    wayBlockPaintIndex = wayBlockList.length() - 1;
}

void GraphicsWidget::clearWayBlockList()
{
    wayBlockList.clear();
    wayBlockPaintIndex = 0;
}