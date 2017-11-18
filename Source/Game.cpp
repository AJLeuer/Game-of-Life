//
//  Game.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Game.hpp"


void Game::run() {
    /* Update the grid on another thread... */
    std::thread modelUpdate(& Game::updateModels, this);
    
    /* ... and update the view on this one */
    updateView();
}

void Game::updateView() {
    while (gameIsActive) {
        
        window.clear();
        
        listenForEvents();
        
        render();
        
        window.display();
        
        this_thread::sleep_for(DisplayData::getScreenRefreshInterval());
    }
}

void Game::updateModels() {
    while (gameIsActive) {
        
        update();
        
        this_thread::sleep_for(DisplayData::getScreenRefreshInterval());
    }
}

void Game::listenForEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        ; //todo
    }
}

void Game::update() {
    for (auto & columnOfCells : * grid.cellGrid) {
        for (Cell & cell : columnOfCells) {
            cell.update();
        }
    }
}

void Game::render() {
    for (auto & columnOfCells : * grid.cellGrid) {
        for (Cell & cell : columnOfCells) {
            window.draw(cell);
        }
    }
}

void Game::recenterView() {
    sf::View view = window.getView();
    view.move((-1 * (view.getCenter().x) / 2), (-1 * (view.getCenter().y) / 4));
    window.setView(view);
}






