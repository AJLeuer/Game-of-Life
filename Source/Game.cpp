//
//  Game.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Game.hpp"


void Game::run() {
    
    seed();
    
    /* Update the grid on another thread... */
    //std::thread modelUpdate(& Game::updateModels, this);
    
    /* ... and update the view on this one */
    updateView();
}

void Game::updateView() {
    while (gameIsActive) {
        
        this_thread::sleep_for(defaultRefreshRateInterval);
        
        update(); //debug, put this back in updateModels()
        
        window.clear();
        
        listenForEvents();
        
        render();
        
        window.display();
        
    }
}

void Game::updateModels() {
    while (gameIsActive) {
        
        this_thread::sleep_for(defaultRefreshRateInterval);
        
        update();
    }
}

void Game::listenForEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        ; //todo
    }
}

void Game::update() {
    
    stack<function<void()>> ruleApplicators;
    
    for (auto & columnOfCells : * grid.cellGrid) {
        for (Cell & cell : columnOfCells) {
            checkCellsForRulesToApply(cell, ruleApplicators);
        }
    }
    
    applyRulesToCells(ruleApplicators);
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

void Game::checkCellsForRulesToApply(Cell & cell, stack<function<void()>> & ruleApplicators) {
    for (auto rule : rules) {
        rule->check(cell, ruleApplicators);
    }
}

void Game::applyRulesToCells(stack<function<void()>> & ruleApplicators) {
    while (ruleApplicators.empty() == false) {
        auto & ruleApplication = ruleApplicators.top();
        ruleApplication();
        ruleApplicators.pop();
    }
}

void DiesWhenLessThanTwoNeighboursAliveIfAlive::check(Cell & cell, stack<function<void()>> & ruleApplicators) const {
    if (cell.state == Cell::State::alive) {
        unsigned livingNeighbors = cell.countOfNeighborCellsInState(Cell::State::alive);
        
        if (livingNeighbors < 2) {
            function<void()> killCell = std::bind(& Cell::kill, std::ref(cell));
            ruleApplicators.push(killCell);
        }
    }
}

void LivesWhenTwoToThreeNeighborsAliveIfAlive::check(Cell & cell, stack<function<void()>> & ruleApplicators) const {
    if (cell.state == Cell::State::alive) {
        unsigned livingNeighbors = cell.countOfNeighborCellsInState(Cell::State::alive);
        
        if ((livingNeighbors >= 2) && (livingNeighbors <= 3)) {
            /* Then do nothing, this function is really just here for the sake of modelling the the rules of the game */
        }
    }
}

void DiesWhenMoreThanThreeNeighboursAliveIfAlive::check(Cell & cell, stack<function<void()>> & ruleApplicators) const {
    if (cell.state == Cell::State::alive) {
        unsigned livingNeighbors = cell.countOfNeighborCellsInState(Cell::State::alive);
        
        if (livingNeighbors > 3) {
            function<void()> killCell = std::bind(& Cell::kill, std::ref(cell));
            ruleApplicators.push(killCell);
        }
    }
}

void RegeneratesWhenExactlyThreeNeighborsAliveIfDead::check(Cell & cell, stack<function<void()>> & ruleApplicators) const {
    if (cell.state == Cell::State::dead) {
        unsigned livingNeighbors = cell.countOfNeighborCellsInState(Cell::State::alive);
        
        if (livingNeighbors == 3) {
            function<void()> resurrectCell = std::bind(& Cell::resurrect, std::ref(cell));
            ruleApplicators.push(resurrectCell);
        }
    }
}


void Game::seed() {
    
//    for (unsigned x = 8; x < 12; x++) {
//        for (unsigned y = 8; y < 12; y++) {
//            if (FastRand<bool>::defaultRandom.nextValue() == true) {
//                grid.getCell({x, y}).resurrect();
//            }
//        }
//    }

    grid.getCell({4, 5}).resurrect();
    grid.getCell({4, 6}).resurrect();
    grid.getCell({4, 7}).resurrect();
}



