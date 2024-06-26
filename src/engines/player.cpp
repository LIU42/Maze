#include "engines/player.h"

Player::Player(Map* pMap)
{
    this->pMap = pMap;
}

void Player::setForwardDirect(Direct direct)
{
    forwardDirect = direct;
}

void Player::reset()
{
    x = INIT_X;
    y = INIT_Y;
    onMove = false;
}

void Player::setMoveStart()
{
    onMove = true;
}

void Player::setMoveStop()
{
    onMove = false;
}

void Player::move()
{
    if (onMove)
    {
        floatIndex.setX(getFloatIndexX());
        floatIndex.setY(getFloatIndexY());

        roundIndex.setX(qRound(floatIndex.getX()));
        roundIndex.setY(qRound(floatIndex.getY()));

        if (forwardDirect == Direct::UP)
        {
            moveUp();
        }
        else if (forwardDirect == Direct::DOWN)
        {
            moveDown();
        }
        else if (forwardDirect == Direct::LEFT)
        {
            moveLeft();
        }
        else if (forwardDirect == Direct::RIGHT)
        {
            moveRight();
        }
    }
}

bool Player::isForwardHaveWall()
{
    return pMap->hasWall(roundIndex.getX(), roundIndex.getY(), forwardDirect);
}

void Player::handleHorizonDeviation()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundIndex.getX() > floatIndex.getX())
    {
        moveRight();
    }
    if (roundIndex.getX() < floatIndex.getX())
    {
        moveLeft();
    }
}

void Player::handleVerticalDeviation()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundIndex.getY() > floatIndex.getY())
    {
        moveDown();
    }
    if (roundIndex.getY() < floatIndex.getY())
    {
        moveUp();
    }
}

void Player::moveUp()
{
    if (floatIndex.getX() != roundIndex.getX())
    {
        handleHorizonDeviation();
    }
    else if (floatIndex.getY() != roundIndex.getY() || !isForwardHaveWall())
    {
        y -= MOVE_SPEED;
    }
}

void Player::moveDown()
{
    if (floatIndex.getX() != roundIndex.getX())
    {
        handleHorizonDeviation();
    }
    else if (floatIndex.getY() != roundIndex.getY() || !isForwardHaveWall())
    {
        y += MOVE_SPEED;
    }
}

void Player::moveLeft()
{
    if (floatIndex.getY() != roundIndex.getY())
    {
        handleVerticalDeviation();
    }
    else if (floatIndex.getX() != roundIndex.getX() || !isForwardHaveWall())
    {
        x -= MOVE_SPEED;
    }
}

void Player::moveRight()
{
    if (floatIndex.getY() != roundIndex.getY())
    {
        handleVerticalDeviation();
    }
    else if (floatIndex.getX() != roundIndex.getX() || !isForwardHaveWall())
    {
        x += MOVE_SPEED;
    }
}

double Player::getFloatIndexX()
{
    return (double)(x - INIT_X) / MapUnit::BLOCK_SIZE;
}

double Player::getFloatIndexY()
{
    return (double)(y - INIT_Y) / MapUnit::BLOCK_SIZE;
}
