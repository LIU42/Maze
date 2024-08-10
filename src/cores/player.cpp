#include "cores/player.h"

Player::Player(Map* pMap)
{
    this->pMap = pMap;
}

void Player::setDirect(int directIndex)
{
    this->directIndex = directIndex;
}

void Player::reset()
{
    x = PlayerProperties::START_X;
    y = PlayerProperties::START_Y;
    onMove = false;
}

void Player::moveStart()
{
    onMove = true;
}

void Player::moveStop()
{
    onMove = false;
}

void Player::move()
{
    if (onMove)
    {
        floatLocation.setX(getFloatLocationX());
        floatLocation.setY(getFloatLocationY());

        roundLocation.setX(qRound(floatLocation.getX()));
        roundLocation.setY(qRound(floatLocation.getY()));

        if (directIndex == DirectIndex::UP)
        {
            moveUp();
        }
        else if (directIndex == DirectIndex::DOWN)
        {
            moveDown();
        }
        else if (directIndex == DirectIndex::LEFT)
        {
            moveLeft();
        }
        else if (directIndex == DirectIndex::RIGHT)
        {
            moveRight();
        }
    }
}

bool Player::isForwardHaveWall()
{
    return pMap->hasWall(roundLocation.getX(), roundLocation.getY(), directIndex);
}

void Player::horizonReparation()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundLocation.getX() > floatLocation.getX())
    {
        moveRight();
    }
    if (roundLocation.getX() < floatLocation.getX())
    {
        moveLeft();
    }
}

void Player::verticalReparation()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundLocation.getY() > floatLocation.getY())
    {
        moveDown();
    }
    if (roundLocation.getY() < floatLocation.getY())
    {
        moveUp();
    }
}

void Player::moveUp()
{
    if (floatLocation.getX() != roundLocation.getX())
    {
        horizonReparation();
    }
    else if (floatLocation.getY() != roundLocation.getY() || !isForwardHaveWall())
    {
        y -= PlayerProperties::MOVE_SPEED;
    }
}

void Player::moveDown()
{
    if (floatLocation.getX() != roundLocation.getX())
    {
        horizonReparation();
    }
    else if (floatLocation.getY() != roundLocation.getY() || !isForwardHaveWall())
    {
        y += PlayerProperties::MOVE_SPEED;
    }
}

void Player::moveLeft()
{
    if (floatLocation.getY() != roundLocation.getY())
    {
        verticalReparation();
    }
    else if (floatLocation.getX() != roundLocation.getX() || !isForwardHaveWall())
    {
        x -= PlayerProperties::MOVE_SPEED;
    }
}

void Player::moveRight()
{
    if (floatLocation.getY() != roundLocation.getY())
    {
        verticalReparation();
    }
    else if (floatLocation.getX() != roundLocation.getX() || !isForwardHaveWall())
    {
        x += PlayerProperties::MOVE_SPEED;
    }
}

double Player::getFloatLocationX()
{
    return (double)(x - PlayerProperties::START_X) / MapProperties::BLOCK_SIZE;
}

double Player::getFloatLocationY()
{
    return (double)(y - PlayerProperties::START_Y) / MapProperties::BLOCK_SIZE;
}
