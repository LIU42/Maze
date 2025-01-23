#include "cores/player.h"

Player::Player(Map* map)
{
    this->map = map;
}

void Player::reset()
{
    x = PlayerProperties::START_X;
    y = PlayerProperties::START_Y;

    floatX = 0;
    floatY = 0;
    roundX = 0;
    roundY = 0;
}

void Player::compensateX()
{
    if (roundX > floatX)
    {
        x += PlayerProperties::MOVE_SPEED;
    }
    else if (roundX < floatX)
    {
        x -= PlayerProperties::MOVE_SPEED;
    }
}

void Player::compensateY()
{
    if (roundY > floatY)
    {
        y += PlayerProperties::MOVE_SPEED;
    }
    else if (roundY < floatY)
    {
        y -= PlayerProperties::MOVE_SPEED;
    }
}

bool Player::moveUp()
{
    if (floatY == roundY && map->hasWall(roundX, roundY, Directs::UP))
    {
        return false;
    }
    if (floatY == roundY && floatX != roundX)
    {
        compensateX();
    }
    else
    {
        y -= PlayerProperties::MOVE_SPEED;
    }
    return true;
}

bool Player::moveDown()
{
    if (floatY == roundY && map->hasWall(roundX, roundY, Directs::DOWN))
    {
        return false;
    }
    if (floatY == roundY && floatX != roundX)
    {
        compensateX();
    }
    else
    {
        y += PlayerProperties::MOVE_SPEED;
    }
    return true;
}

bool Player::moveLeft()
{
    if (floatX == roundX && map->hasWall(roundX, roundY, Directs::LEFT))
    {
        return false;
    }
    if (floatX == roundX && floatY != roundY)
    {
        compensateY();
    }
    else
    {
        x -= PlayerProperties::MOVE_SPEED;
    }
    return true;
}

bool Player::moveRight()
{
    if (floatX == roundX && map->hasWall(roundX, roundY, Directs::RIGHT))
    {
        return false;
    }
    if (floatX == roundX && floatY != roundY)
    {
        compensateY();
    }
    else
    {
        x += PlayerProperties::MOVE_SPEED;
    }
    return true;
}

void Player::updateLocationInfo()
{
    floatX = getFloatLocationX();
    floatY = getFloatLocationY();

    roundX = qRound(floatX);
    roundY = qRound(floatY);
}

double Player::getFloatLocationX()
{
    return (double)(x - PlayerProperties::START_X) / MapProperties::BLOCK_SIZE;
}

double Player::getFloatLocationY()
{
    return (double)(y - PlayerProperties::START_Y) / MapProperties::BLOCK_SIZE;
}
