#include "Games/Player.h"

Player::Player(MazeMap* pMazeMap)
{
    this->pMazeMap = pMazeMap;
}

void Player::setForwardDirect(Direct direct)
{
    forwardDirect = direct;
}

void Player::resetPlayer()
{
    positionX = INIT_POSITION_X;
    positionY = INIT_POSITION_Y;
    isOnMove = false;
}

void Player::setMoveStart()
{
    isOnMove = true;
}

void Player::setMoveStop()
{
    isOnMove = false;
}

void Player::playerMove()
{
    if (isOnMove)
    {
        floatIndex.setX(getFloatIndexX());
        floatIndex.setY(getFloatIndexY());

        roundIndex.setX(qRound(floatIndex.x()));
        roundIndex.setY(qRound(floatIndex.y()));

        if (forwardDirect == Direct::DIRECT_UP)
        {
            moveUp();
        }
        else if (forwardDirect == Direct::DIRECT_DOWN)
        {
            moveDown();
        }
        else if (forwardDirect == Direct::DIRECT_LEFT)
        {
            moveLeft();
        }
        else if (forwardDirect == Direct::DIRECT_RIGHT)
        {
            moveRight();
        }
    }
}

bool Player::isForwardHaveWall()
{
    return pMazeMap->isHaveWall(roundIndex.x(), roundIndex.y(), forwardDirect);
}

void Player::horizonDiffHandler()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundIndex.x() > floatIndex.x())
    {
        moveRight();
    }
    if (roundIndex.x() < floatIndex.x())
    {
        moveLeft();
    }
}

void Player::verticalDiffHandler()
{
    if (isForwardHaveWall())
    {
        return;
    }
    if (roundIndex.y() > floatIndex.y())
    {
        moveDown();
    }
    if (roundIndex.y() < floatIndex.y())
    {
        moveUp();
    }
}

void Player::moveUp()
{
    if (floatIndex.x() != roundIndex.x())
    {
        horizonDiffHandler();
    }
    else if (floatIndex.y() != roundIndex.y() || !isForwardHaveWall())
    {
        positionY -= MOVE_SPEED;
    }
}

void Player::moveDown()
{
    if (floatIndex.x() != roundIndex.x())
    {
        horizonDiffHandler();
    }
    else if (floatIndex.y() != roundIndex.y() || !isForwardHaveWall())
    {
        positionY += MOVE_SPEED;
    }
}

void Player::moveLeft()
{
    if (floatIndex.y() != roundIndex.y())
    {
        verticalDiffHandler();
    }
    else if (floatIndex.x() != roundIndex.x() || !isForwardHaveWall())
    {
        positionX -= MOVE_SPEED;
    }
}

void Player::moveRight()
{
    if (floatIndex.y() != roundIndex.y())
    {
        verticalDiffHandler();
    }
    else if (floatIndex.x() != roundIndex.x() || !isForwardHaveWall())
    {
        positionX += MOVE_SPEED;
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

double Player::getFloatIndexX()
{
    return (double)(positionX - INIT_POSITION_X) / MazeBlockUnit::BLOCK_SIZE;
}

double Player::getFloatIndexY()
{
    return (double)(positionY - INIT_POSITION_Y) / MazeBlockUnit::BLOCK_SIZE;
}
