#include "Graphics.h"

GraphicsWidget::GraphicsWidget(QWidget *parent): QWidget(parent)
{
    images.way.load(":/Images/way.png");
    images.finish.load(":/Images/finish.png");
    images.player.load(":/Images/player.png");

    for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
    {
        images.wall[direct].load(QString(":/Images/wall_%1.png").arg(direct));
    }
}

void GraphicsWidget::paintMap(QPainter& painter)
{
    for (int i = 0; i < Map::ROWS; i++)
    {
        for (int j = 0; j < Map::COLS; j++)
        {
            for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
            {
                if (pGame->isMapHaveWall(i, j, (Direct)direct))
                {
                    int x = MazeBlockUnit::SIZE * i + BORDER - WALL_WIDTH;
                    int y = MazeBlockUnit::SIZE * j + BORDER - WALL_WIDTH;

                    painter.drawPixmap(x, y, images.wall[direct]);
                }
            }
        }
    }
    int x = MazeBlockUnit::SIZE * (Map::ROWS - 1) + BORDER;
    int y = MazeBlockUnit::SIZE * (Map::COLS - 1) + BORDER;

    painter.drawPixmap(x, y, images.finish);
}

void GraphicsWidget::paintWay(QPainter& painter)
{
    if (!wayData.isEmpty())
    {
        for (int i = wayData.length() - 1; i >= wayDisplayIndex; i--)
        {
            int x = wayData[i].x() * MazeBlockUnit::SIZE + BORDER;
            int y = wayData[i].y() * MazeBlockUnit::SIZE + BORDER;

            painter.drawPixmap(x, y, images.way);
        }
        if (wayDisplayIndex > 0) { wayDisplayIndex -= 1; }
    }
}

void GraphicsWidget::paintPlayer(QPainter& painter)
{
    int playerX = pGame->getPlayerX();
    int playerY = pGame->getPlayerY();

    painter.drawPixmap(playerX, playerY, images.player);
}

void GraphicsWidget::paintEvent(QPaintEvent* pPaintEvent)
{
    Q_UNUSED(pPaintEvent);
    QPainter painter(this);

    paintWay(painter);
    paintMap(painter);
    paintPlayer(painter);
}

void GraphicsWidget::setGame(MainGame* pGame)
{
    this->pGame = pGame;
}

void GraphicsWidget::updateWayData()
{
    wayData = pGame->getWayData();
    wayDisplayIndex = wayData.length() - 1;
}

void GraphicsWidget::clearWayData()
{
    wayData.clear();
    wayDisplayIndex = 0;
}