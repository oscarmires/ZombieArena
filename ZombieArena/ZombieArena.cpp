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
    RenderWindow window(vm, "Zombie Arena");
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
    
    bool isPressed_W = false;
    bool isPressed_A = false;
    bool isPressed_S = false;
    bool isPressed_D = false;
    bool isPressed_1 = false;
    bool isPressed_2 = false;
    bool isPressed_3 = false;
    bool isPressed_4 = false;
    bool isPressed_5 = false;
    bool isPressed_6 = false;
     
    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            // click on x
            if (event.type == Event::Closed) {
                window.close();
            }
            // key pressed
            if (event.type == Event::KeyPressed) {
                // ESCAPE
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                // GAME STATE
                //  pause while playing
                else if (event.key.code == Keyboard::Enter &&
                    state == State::PLAYING) {
                    state = State::PAUSED;
                    break;
                }
                //  restart while paused
                else if (event.key.code == Keyboard::Enter &&
                        state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                    break;
                }
                //  start new game while in GAME_OVER
                else if (event.key.code == Keyboard::Enter &&
                        state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                    puts("enter");
                    break;
                }
                // WASD INPUT
                else if (event.key.code == Keyboard::W) {
                    isPressed_W = true;
                    break;
                }
                else if (event.key.code == Keyboard::A) {
                    isPressed_A = true;
                    break;
                }
                else if (event.key.code == Keyboard::S) {
                    isPressed_S = true;
                    break;
                }
                else if (event.key.code == Keyboard::D) {
                    isPressed_D = true;
                    break;
                }
                // NUMS INPUT
                if (state == State::LEVELING_UP) {
                    if (event.key.code == Keyboard::Num1) {
                        isPressed_1 = true;
                        puts("1");
                        break;
                    }
                    else if (event.key.code == Keyboard::Num2) {
                        isPressed_2 = true;
                        break;
                    }
                    else if (event.key.code == Keyboard::Num3) {
                        isPressed_3 = true;
                        break;
                    }
                    else if (event.key.code == Keyboard::Num4) {
                        isPressed_4 = true;
                        break;
                    }
                    else if (event.key.code == Keyboard::Num5) {
                        isPressed_5 = true;
                        break;
                    }
                    else if (event.key.code == Keyboard::Num6) {
                        isPressed_6 = true;
                        break;
                    }
                }
                // others
                if (state == State::PLAYING) {
                }
            }
            // key released
            if (event.type == Event::KeyReleased) {
                // WASD INPUT
                if (event.key.code == Keyboard::W) {
                    isPressed_W = false;
                    break;
                }
                else if (event.key.code == Keyboard::A) {
                    isPressed_A = false;
                    break;
                }
                else if (event.key.code == Keyboard::S) {
                    isPressed_S = false;
                    break;
                }
                else if (event.key.code == Keyboard::D) {
                    isPressed_D = false;
                    break;
                }
            }
        }
        
        // Handle controls while playing
        if (state == State::PLAYING)
        {
            // Handle the pressing and releasing of the WASD keys
            if (isPressed_W)
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (isPressed_S)
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (isPressed_A)
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (isPressed_D)
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
            if (isPressed_1)
            {
                state = State::PLAYING;
                isPressed_1 = false;
                puts("not 1");
            }

            if (isPressed_2)
            {
                state = State::PLAYING;
                isPressed_2 = false;
            }

            if (isPressed_3)
            {
                state = State::PLAYING;
                isPressed_3 = false;
            }

            if (isPressed_4)
            {
                state = State::PLAYING;
                isPressed_4 = false;
            }

            if (isPressed_5)
            {
                state = State::PLAYING;
                isPressed_5 = false;
            }

            if (isPressed_6)
            {
                state = State::PLAYING;
                isPressed_6 = false;
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
        }// End leveling up
        
        
        // Update frame
        if (state == State::PLAYING)
        {
            // Update the delta time
            Time dt = clock.restart();
            // Update the total game time
            gameTimeTotal += dt;
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            // Where is the mouse pointed
            mouseScreenPosition = Mouse::getPosition(window);

            // Convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(
                Mouse::getPosition(), mainView);

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition(window));

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
    }
    
    return 0;
}
