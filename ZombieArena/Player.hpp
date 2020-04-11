//
//  Player.hpp
//  ZombieArena
//
//  Created by Oscar Miranda Escalante on 11/04/20.
//  Copyright © 2020 Oscar Miranda Escalante. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>

class Player {
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    // character basics
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f resolution;
    // related arena
    sf::IntRect arena;
    int tileSize;
    // movement of player
    bool upPressed,
         downPressed,
         leftPressed,
         rightPressed;
    // health
    int health,
        maxHealth;
    sf::Time lastHit;
    // speed
    float speed;
public:
    Player();
    void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
    void resetPlayerStates();
    bool hit(sf::Time timeHit);
    sf::Time getLastHitTime();
    sf::FloatRect getPosition();
    sf::Vector2f getCenter();
    float getRotation();
    sf::Sprite getSprite();
    void moveLeft(),
         moveRight(),
         moveUp(),
         moveDown();
    void stopLeft(),
         stopRight(),
         stopUp(),
         stopDown();
    void update(float elapsedTime, sf::Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    int getHealth();
};

#endif /* Player_hpp */
