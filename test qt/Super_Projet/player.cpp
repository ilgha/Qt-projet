#include "player.h"

Player::Player()
{

}

Player::Player(int x, int y)
{
    posX = x;
    posY = y;
}

int Player::getPosX()
{
    return posX;
}

int Player::getPosY()
{
    return posY;
}

void Player::setPosX(int x)
{
    posX = x;
}

void Player::setPosY(int y)
{
    posY = y;
}

void Player::isMovable()
{
    movable = true;
}

void Player::notMovable()
{
    movable = false;
}
