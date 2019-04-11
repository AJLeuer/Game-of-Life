//
//  Game.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Game.hpp"


void Game::start()
{
	try
	{
		run();
	}
	catch (std::exception e)
	{
		gameIsActive = false;
	}
}

void Game::run() {
    
    randomSeed();
    
    /* Update the grid on another thread... */
    std::thread modelUpdate(& Game::updateModels, this);
    
    /* ... and update the view on this one */
    updateView();
}

void Game::updateView() {
    recenterView();

    while (gameIsActive) {
        
        std::this_thread::sleep_for(defaultRefreshRateInterval);

        window.clear();
        
        listenForEvents();
        
        render();
        
        window.display();
    }
#pragma clang diagnostic pop
}

void Game::updateModels() {
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); //wait for the rendering to get started first
    
    while (gameIsActive) {
        
        std::this_thread::sleep_for(defaultRefreshRateInterval);
        
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
    
    checkCellsForRulesToApply(grid.cellGrid, ruleApplicators);

    applyRulesToCells(ruleApplicators);
}

void Game::render() {
    for (unsigned x = 0; x < grid.cellGrid.size(); x++) {
        
        auto & columnOfCells = grid.cellGrid.at(x);
        
        for (unsigned y = 0; y < columnOfCells.size(); y++) {
            Cell & cell = columnOfCells.at(y);
            window.draw(cell);
        }
    }
}

void Game::recenterView() {
    sf::View view = window.getView();
    
    auto xOffset = -1 * ((view.getCenter().x) / 2);
    auto yOffset = -1 * ((view.getCenter().y) / 4);
    
    view.move(xOffset, yOffset);
    window.setView(view);
}

void Game::checkCellsForRulesToApply(vector< vector<Cell>> & cells, stack<function<void()>> & ruleApplicators) {
    
    for (auto & columnOfCells : cells) {
        for (Cell & cell : columnOfCells) {
            checkCellForRulesToApply(cell, ruleApplicators);
        }
    }
}

void Game::checkCellForRulesToApply(Cell & cell, stack<function<void()>> & ruleApplicators) {
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
            function<void()> killCell = std::bind(& Cell::die, std::ref(cell));
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
            function<void()> killCell = std::bind(& Cell::die, std::ref(cell));
            ruleApplicators.push(killCell);
        }
    }
}

void RegeneratesWhenExactlyThreeNeighborsAliveIfDead::check(Cell & cell, stack<function<void()>> & ruleApplicators) const {
    if (cell.state == Cell::State::dead) {
        unsigned livingNeighbors = cell.countOfNeighborCellsInState(Cell::State::alive);
        
        if (livingNeighbors == 3) {
            function<void()> resurrectCell = std::bind(& Cell::live, std::ref(cell));
            ruleApplicators.push(resurrectCell);
        }
    }
}


void Game::randomSeed() {
    constexpr auto startPos = gridSize * 0.25;
    constexpr auto endPos = gridSize * 0.75;
    
    for (unsigned x = startPos; x < endPos; x++) {
        for (unsigned y = startPos; y < endPos; y++) {
            if (FastRand<unsigned>::defaultRandom.nextValue(0, 5) ==  1) {
                grid.getCell({x, y}).live();
            }
        }
    }

}



