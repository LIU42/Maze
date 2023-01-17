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
	static Real real;
	static Near near;

	if (isOnMove)
	{
		real.setX(getRelativeX());
		real.setY(getRelativeY());

		near.setX(qRound(real.x()));
		near.setY(qRound(real.y()));

		switch (direct)
		{
			case UP: moveUp(real, near); break;
			case DOWN: moveDown(real, near); break;
			case LEFT: moveLeft(real, near); break;
			case RIGHT: moveRight(real, near); break;
		}
	}
}

bool Player::isHaveWall(Near& near, Direct direct)
{
	return pMap->isHaveWall(near.x(), near.y(), direct);
}

void Player::horizonDiffHandle(Real& real, Near& near, Direct direct)
{
	if (isHaveWall(near, direct))
	{
		return;
	}
	else if (near.x() > real.x()) { moveRight(real, near); }
	else if (near.x() < real.x()) { moveLeft(real, near); }
}

void Player::verticalDiffHandle(Real& real, Near& near, Direct direct)
{
	if (isHaveWall(near, direct))
	{
		return;
	}
	else if (near.y() > real.y()) { moveDown(real, near); }
	else if (near.y() < real.y()) { moveUp(real, near); }
}

void Player::moveUp(Real& real, Near& near)
{
	if (real.x() != near.x())
	{
		horizonDiffHandle(real, near, UP);
		return;
	}
	else if (real.x() == near.x() && real.y() == near.y() && isHaveWall(near, UP))
	{
		return;
	}
	setY(this->y() - SPEED);
}

void Player::moveDown(Real& real, Near& near)
{
	if (real.x() != near.x())
	{
		horizonDiffHandle(real, near, DOWN);
		return;
	}
	else if (real.x() == near.x() && real.y() == near.y() && isHaveWall(near, DOWN))
	{
		return;
	}
	setY(this->y() + SPEED);
}

void Player::moveLeft(Real& real, Near& near)
{
	if (real.y() != near.y())
	{
		verticalDiffHandle(real, near, LEFT);
		return;
	}
	else if (real.x() == near.x() && real.y() == near.y() && isHaveWall(near, LEFT))
	{
		return;
	}
	setX(this->x() - SPEED);
}

void Player::moveRight(Real& real, Near& near)
{
	if (real.y() != near.y())
	{
		verticalDiffHandle(real, near, RIGHT);
		return;
	}
	else if (real.x() == near.x() && real.y() == near.y() && isHaveWall(near, RIGHT))
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

