#include "graphics.h"

GraphicsWidget::GraphicsWidget(QWidget *parent): QWidget(parent)
{
    images.way.load(":/Images/way.png");
    images.finish.load(":/Images/finish.png");
    images.player.load(":/Images/player.png");

    for (int direct = UP; direct <= RIGHT; direct++)
    {
        images.wall[direct].load(QString(":/Images/wall_%1.png").arg(direct));
    }
}

void GraphicsWidget::displayMap(QPainter& painter)
{
    static QRect wallRect;

    for (int x = 0; x < Map::ROWS; x++)
    {
        for (int y = 0; y < Map::COLS; y++)
        {
            for (int direct = UP; direct <= RIGHT; direct++)
            {
                if (pGame->isMapHaveWall(x, y, (Direct)direct))
                {
                    wallRect.setX(MazeBlockUnit::SIZE * x + BORDER - WALL_WIDTH);
                    wallRect.setY(MazeBlockUnit::SIZE * y + BORDER - WALL_WIDTH);
                    wallRect.setWidth(MazeBlockUnit::SIZE + WALL_WIDTH * 2);
                    wallRect.setHeight(MazeBlockUnit::SIZE + WALL_WIDTH * 2);

                    painter.drawPixmap(wallRect, images.wall[direct]);
                }
            }
        }
    }
    int x = MazeBlockUnit::SIZE * (Map::ROWS - 1) + BORDER;
    int y = MazeBlockUnit::SIZE * (Map::COLS - 1) + BORDER;

    painter.drawPixmap(x, y, MazeBlockUnit::SIZE, MazeBlockUnit::SIZE, images.finish);
}

void GraphicsWidget::displayWay(QPainter& painter)
{
    if (!wayData.isEmpty())
    {
        for (int i = wayData.length() - 1; i >= wayDisplayIndex; i--)
        {
            int x = wayData[i].x() * MazeBlockUnit::SIZE + BORDER;
            int y = wayData[i].y() * MazeBlockUnit::SIZE + BORDER;

            painter.drawPixmap(x, y, MazeBlockUnit::SIZE, MazeBlockUnit::SIZE, images.way);
        }
        if (wayDisplayIndex > 0) { wayDisplayIndex -= 1; }
    }
}

void GraphicsWidget::displayPlayer(QPainter& painter)
{
    int playerX = pGame->getPlayerX();
    int playerY = pGame->getPlayerY();

    painter.drawPixmap(playerX, playerY, MazeBlockUnit::SIZE, MazeBlockUnit::SIZE, images.player);
}

void GraphicsWidget::paintEvent(QPaintEvent* pPaintEvent)
{
    Q_UNUSED(pPaintEvent);
    QPainter painter(this);

    displayWay(painter);
    displayMap(painter);
    displayPlayer(painter);
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