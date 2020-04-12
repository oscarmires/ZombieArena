//
//  ZombieArena.cpp
//  ZombieArena
//
//  Created by Oscar Miranda Escalante on 07/04/20.
//  Copyright © 2020 Oscar Miranda Escalante. All rights reserved.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"           // "" for working directory file
using namespace sf;

int main() {
    // possible game states
    enum class State {
        PAUSED, LEVELING_UP, GAME_OVER, PLAYING
    };
    State state = State::GAME_OVER;
    
    // define resolution to be equal to monitor's
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    
    // window basics
    VideoMode vm(resolution.x, resolution.y);
    RenderWindow window(vm, "Zombie Arena", Style::Fullscreen);
    window.setFramerateLimit(30);
    
    // main view
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    
    // time
    Clock clock;
    Time gameTimeTotal;
    
    // mouse position
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    
    Player player;
    
    IntRect arena;
    
    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                // pause while playing
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING) {
                    state = State::PAUSED;
                }
                // restart while paused
                else if (event.key.code == Keyboard::Return &&
                        state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                }
                // start new game while in GAME_OVER
                else if (event.key.code == Keyboard::Return &&
                        state == State::GAME_OVER) {
                        state = State::LEVELING_UP;
                }
                if (state == State::PLAYING) {
                    
                }
            }
        }
    }
    
    
    // Handle the player quitting
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    
    // Handle controls while playing
    if (state == State::PLAYING)
    {
        // Handle the pressing and releasing of the WASD keys
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player.moveUp();
        }
        else
        {
            player.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player.moveDown();
        }
        else
        {
            player.stopDown();
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player.moveLeft();
        }
        else
        {
            player.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            player.moveRight();
        }
        else
        {
            player.stopRight();
        }
    }
    
    
    // Handle the levelling up state
    if (state == State::LEVELING_UP)
    {
        // Handle the player levelling up
        if (event.key.code == Keyboard::Num1)
        {
            state = State::PLAYING;
        }

        if (event.key.code == Keyboard::Num2)
        {
            state = State::PLAYING;
        }

        if (event.key.code == Keyboard::Num3)
        {
            state = State::PLAYING;
        }

        if (event.key.code == Keyboard::Num4)
        {
            state = State::PLAYING;
        }

        if (event.key.code == Keyboard::Num5)
        {
            state = State::PLAYING;
        }

        if (event.key.code == Keyboard::Num6)
        {
            state = State::PLAYING;
        }
        
        if (state == State::PLAYING)
        {
            // Prepare thelevel
            // We will modify the next two lines later
            arena.width = 500;
            arena.height = 500;
            arena.left = 0;
            arena.top = 0;

            // We will modify this line of code later
            int tileSize = 50;

            // Spawn the player in the middle of the arena
            player.spawn(arena, resolution, tileSize);
            
            // Reset the clock so there isn't a frame jump
            clock.restart();
        }
    }// End levelling up
    
    
    // Udate frame
    if (state == State::PLAYING)
    {
        // Update the delta time
        Time dt = clock.restart();
        // Update the total game time
        gameTimeTotal += dt;
        // Make a decimal fraction of 1 from the delta time
        float dtAsSeconds = dt.asSeconds();

        // Where is the mouse pointer
        mouseScreenPosition = Mouse::getPosition();

        // Convert mouse position to world coordinates of mainView
        mouseWorldPosition = window.mapPixelToCoords(
            Mouse::getPosition(), mainView);

        // Update the player
        player.update(dtAsSeconds, Mouse::getPosition());

        // Make a note of the players new position
        Vector2f playerPosition(player.getCenter());

        // Make the view centre around the player
        mainView.setCenter(player.getCenter());
    }// End updating the scene
    
    
    // Draw the scene
    if (state == State::PLAYING)
    {
        window.clear();

        // set the mainView to be displayed in the window
        // And draw everything related to it
        window.setView(mainView);

        // Draw the player
        window.draw(player.getSprite());
    }

    if (state == State::LEVELING_UP)
    {
    }

    if (state == State::PAUSED)
    {
    }

    if (state == State::GAME_OVER)
    {
    }

    window.display();
    
    return 0;
}
