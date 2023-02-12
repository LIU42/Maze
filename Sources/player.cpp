#include "player.h"

void Player::init(int initX, int initY, Map* pMap)
{
	this->initX = initX;
	this->initY = initY;
	this->setX(initX);
	this->setY(initY);
	this->pMap = pMap;
	this->direct = UP;
	this->isOnMove = false;
}

void Player::setDirect(Direct direct)
{
	this->direct = direct;
}

void Player::setIsOnMove(bool isOnMove)
{
	this->isOnMove = isOnMove;
}

void Player::move()
{
	static RealPoint realPoint;
	static NearPoint nearPoint;

	if (isOnMove)
	{
		realPoint.setX(getRelativeX());
		realPoint.setY(getRelativeY());

		nearPoint.setX(qRound(realPoint.x()));
		nearPoint.setY(qRound(realPoint.y()));

		switch (direct)
		{
			case UP: moveUp(realPoint, nearPoint); break;
			case DOWN: moveDown(realPoint, nearPoint); break;
			case LEFT: moveLeft(realPoint, nearPoint); break;
			case RIGHT: moveRight(realPoint, nearPoint); break;
		}
	}
}

bool Player::isHaveWall(NearPoint& nearPoint, Direct direct)
{
	return pMap->isHaveWall(nearPoint.x(), nearPoint.y(), direct);
}

void Player::horizonDiffHandle(RealPoint& realPoint, NearPoint& nearPoint, Direct direct)
{
	if (isHaveWall(nearPoint, direct))
	{
		return;
	}
	else if (nearPoint.x() > realPoint.x()) { moveRight(realPoint, nearPoint); }
	else if (nearPoint.x() < realPoint.x()) { moveLeft(realPoint, nearPoint); }
}

void Player::verticalDiffHandle(RealPoint& realPoint, NearPoint& nearPoint, Direct direct)
{
	if (isHaveWall(nearPoint, direct))
	{
		return;
	}
	else if (nearPoint.y() > realPoint.y()) { moveDown(realPoint, nearPoint); }
	else if (nearPoint.y() < realPoint.y()) { moveUp(realPoint, nearPoint); }
}

void Player::moveUp(RealPoint& realPoint, NearPoint& nearPoint)
{
	if (realPoint.x() != nearPoint.x())
	{
		horizonDiffHandle(realPoint, nearPoint, UP);
		return;
	}
	else if (realPoint.x() == nearPoint.x() && realPoint.y() == nearPoint.y() && isHaveWall(nearPoint, UP))
	{
		return;
	}
	setY(this->y() - SPEED);
}

void Player::moveDown(RealPoint& realPoint, NearPoint& nearPoint)
{
	if (realPoint.x() != nearPoint.x())
	{
		horizonDiffHandle(realPoint, nearPoint, DOWN);
		return;
	}
	else if (realPoint.x() == nearPoint.x() && realPoint.y() == nearPoint.y() && isHaveWall(nearPoint, DOWN))
	{
		return;
	}
	setY(this->y() + SPEED);
}

void Player::moveLeft(RealPoint& realPoint, NearPoint& nearPoint)
{
	if (realPoint.y() != nearPoint.y())
	{
		verticalDiffHandle(realPoint, nearPoint, LEFT);
		return;
	}
	else if (realPoint.x() == nearPoint.x() && realPoint.y() == nearPoint.y() && isHaveWall(nearPoint, LEFT))
	{
		return;
	}
	setX(this->x() - SPEED);
}

void Player::moveRight(RealPoint& realPoint, NearPoint& nearPoint)
{
	if (realPoint.y() != nearPoint.y())
	{
		verticalDiffHandle(realPoint, nearPoint, RIGHT);
		return;
	}
	else if (realPoint.x() == nearPoint.x() && realPoint.y() == nearPoint.y() && isHaveWall(nearPoint, RIGHT))
	{
		return;
	}
	setX(this->x() + SPEED);
}

double Player::getRelativeX()
{
	return (double)(this->x() - initX) / Map::UNIT_SIZE;
}

double Player::getRelativeY()
{
	return (double)(this->y() - initY) / Map::UNIT_SIZE;
}
