//
//  Game.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Game.hpp"


void Game::run() {
    while (gameIsActive) {
        
        window.clear();
        
        listenForEvents();
        
        window.draw(sf::Text("Hello", defaultFont, 48));
        
        window.display();
    }
}

void Game::listenForEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        ;
    }
}
