//
//  main.cpp
//  ZombieArena
//
//  Created by Oscar Miranda Escalante on 07/04/20.
//  Copyright © 2020 Oscar Miranda Escalante. All rights reserved.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::VideoMode vm(500, 500);
    sf::RenderWindow window(vm, "ZombieArena");
    window.setFramerateLimit(30);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}
