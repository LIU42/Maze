#include "player.h"

void Player::setMap(Map* pMap)
{
    this->pMap = pMap;
}

void Player::setForwardDirect(Direct direct)
{
    this->forwardDirect = direct;
}

void Player::setIsOnMove(bool isOnMove)
{
	this->isOnMove = isOnMove;
}

void Player::reset()
{
    positionX = INIT_POSITION_X;
    positionY = INIT_POSITION_Y;
    forwardDirect = UP;
    isOnMove = false;
}

void Player::move()
{
	if (isOnMove)
	{
        relativePoint.setX(getRelativeX());
        relativePoint.setY(getRelativeY());

        blockPoint.setX(qRound(relativePoint.x()));
        blockPoint.setY(qRound(relativePoint.y()));

        switch (forwardDirect)
		{
            case UP: moveUp(); break;
            case DOWN: moveDown(); break;
            case LEFT: moveLeft(); break;
            case RIGHT: moveRight(); break;
		}
	}
}

bool Player::isForwardHaveWall()
{
    return pMap->isHaveWall(blockPoint.x(), blockPoint.y(), forwardDirect);
}

void Player::horizonDiffHandler()
{
    if (!isForwardHaveWall())
	{
        if (blockPoint.x() > relativePoint.x()) { moveRight(); }
        if (blockPoint.x() < relativePoint.x()) { moveLeft(); }
	}
}

void Player::verticalDiffHandler()
{
    if (!isForwardHaveWall())
	{
        if (blockPoint.y() > relativePoint.y()) { moveDown(); }
        if (blockPoint.y() < relativePoint.y()) { moveUp(); }
	}
}

void Player::moveUp()
{
    if (relativePoint.x() != blockPoint.x())
	{
        horizonDiffHandler();
	}
    else if (relativePoint.y() != blockPoint.y() || !isForwardHaveWall())
    {
        positionY -= SPEED;
	}
}

void Player::moveDown()
{
    if (relativePoint.x() != blockPoint.x())
	{
        horizonDiffHandler();
	}
    else if (relativePoint.y() != blockPoint.y() || !isForwardHaveWall())
    {
        positionY += SPEED;
	}
}

void Player::moveLeft()
{
    if (relativePoint.y() != blockPoint.y())
	{
        verticalDiffHandler();
	}
    else if (relativePoint.x() != blockPoint.x() || !isForwardHaveWall())
    {
        positionX -= SPEED;
	}
}

void Player::moveRight()
{
    if (relativePoint.y() != blockPoint.y())
	{
        verticalDiffHandler();
	}
    else if (relativePoint.x() != blockPoint.x() || !isForwardHaveWall())
    {
        positionX += SPEED;
	}
}

int Player::getPositionX()
{
    return positionX;
}

int Player::getPositionY()
{
    return positionY;
}

double Player::getRelativeX()
{
    return (double)(positionX - INIT_POSITION_X) / MazeBlockUnit::SIZE;
}

double Player::getRelativeY()
{
    return (double)(positionY - INIT_POSITION_Y) / MazeBlockUnit::SIZE;
}
