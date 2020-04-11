//
//  Player.cpp
//  ZombieArena
//
//  Created by Oscar Miranda Escalante on 11/04/20.
//  Copyright © 2020 Oscar Miranda Escalante. All rights reserved.
//

#include "Player.hpp"
#include <cmath>

Player::Player()
{
    this->speed = START_SPEED;
    this->health = START_HEALTH;
    this->maxHealth = START_HEALTH;

    // Associate a texture with the sprite
    // !!Watch this space!!
    texture.loadFromFile("graphics/player.png");
    sprite.setTexture(this->texture);

    // Set the origin of the sprite to the centre,
    // for smooth rotation
    sprite.setOrigin(25, 25);
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    // Place the player in the middle of the arena
    this->position.x = arena.width / 2;
    this->position.y = arena.height / 2;

    // Copy the details of the arena to the player's Arena
    this->arena.left = arena.left;
    this->arena.width = arena.width;
    this->arena.top = arena.top;
    this->arena.height = arena.height;

    // Remember how big the tiles are in this arena
    this->tileSize = tileSize;

    // Strore the resolution for future use
    this->resolution.x = resolution.x;
    this->resolution.y = resolution.y;

}

sf::Time Player::getLastHitTime()
{
    return this->lastHit;
}

bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - this->lastHit.asMilliseconds() > 200)// 2 tenths of second
    {
        this->lastHit = timeHit;
        this->health -= 10;
        return true;
    }
    else
    {
        return false;
    }

}

sf::FloatRect Player::getPosition()
{
    return this->sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter()
{
    return this->position;
}

float Player::getRotation()
{
    return this->sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
    return this->sprite;
}

int Player::getHealth()
{
    return this->health;
}

void Player::moveLeft()
{
    this->leftPressed = true;
}

void Player::moveRight()
{
    this->rightPressed = true;
}

void Player::moveUp()
{
    this->upPressed = true;
}

void Player::moveDown()
{
    this->downPressed = true;
}

void Player::stopLeft()
{
    this->leftPressed = false;
}

void Player::stopRight()
{
    this->rightPressed = false;
}

void Player::stopUp()
{
    this->upPressed = false;
}

void Player::stopDown()
{
    this->downPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{

    if (this->upPressed)
    {
        this->position.y -= this->speed * elapsedTime;
    }

    if (this->downPressed)
    {
        this->position.y += this->speed * elapsedTime;
    }

    if (this->rightPressed)
    {
        this->position.x += this->speed * elapsedTime;
    }

    if (this->leftPressed)
    {
        this->position.x -= this->speed * elapsedTime;
    }

    this->sprite.setPosition(this->position);



    // Keep the player in the arena
    if (this->position.x > this->arena.width - this->tileSize)
    {
        this->position.x = this->arena.width - this->tileSize;
    }

    if (this->position.x < this->arena.left + this->tileSize)
    {
        this->position.x = this->arena.left + this->tileSize;
    }

    if (this->position.y > this->arena.height - this->tileSize)
    {
        this->position.y = this->arena.height - this->tileSize;
    }

    if (this->position.y < this->arena.top + this->tileSize)
    {
        this->position.y = this->arena.top + this->tileSize;
    }

    // Calculate the angle the player is facing
    float angle = (std::atan2(mousePosition.y - this->resolution.y / 2,
        mousePosition.x - this->resolution.x / 2)
        * 180) / 3.141;

    this->sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
    // 20% speed upgrade
    this->speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
    // 20% max health upgrade
    this->maxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
    this->health += amount;

    // But not beyond the maximum
    if (this->health > this->maxHealth)
    {
        this->health = this->maxHealth;
    }
}

