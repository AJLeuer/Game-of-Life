//
//  Game.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <array>
#include <thread>
#include <chrono>
#include <stack>

#include "./Model/Grid.hpp"
#include "./View/Window.h"
#include "View/DisplayData.hpp"
#include "./Util/Config.h"
#include "./Util/Random.hpp"

using std::stack;
using std::function;

struct Rule {
    virtual void check(Cell & cell, stack<function<void()>> & ruleApplicators) const = 0;
    
    //virtual void operator () (Cell & cell) { check(cell); }
};

struct DiesWhenLessThanTwoNeighboursAliveIfAlive : public Rule {
    void check(Cell & cell, stack<function<void()>> & ruleApplicators ) const override;
};

struct LivesWhenTwoToThreeNeighborsAliveIfAlive : public Rule {
    void check(Cell & cell, stack<function<void()>> & ruleApplicators ) const override;
};

struct DiesWhenMoreThanThreeNeighboursAliveIfAlive : public Rule {
    void check(Cell & cell, stack<function<void()>> & ruleApplicators ) const override;
};

struct RegeneratesWhenExactlyThreeNeighborsAliveIfDead : public Rule {
    void check(Cell & cell, stack<function<void()>> & ruleApplicators) const override;
};

class Game {
    
    static constexpr const DiesWhenLessThanTwoNeighboursAliveIfAlive rule0;
    static constexpr const LivesWhenTwoToThreeNeighborsAliveIfAlive rule1;
    static constexpr const DiesWhenMoreThanThreeNeighboursAliveIfAlive rule2;
    static constexpr const RegeneratesWhenExactlyThreeNeighborsAliveIfDead rule3;
    
    static constexpr const std::array<const Rule *, 4> rules { & Game::rule0, & Game::rule1, & Game::rule2, & Game::rule3 };
    
    static void checkCellForRulesToApply(Cell & cell, stack<function<void()>> & ruleApplicators);
    
    void checkCellsForRulesToApply(vector< vector<Cell>> & cells, stack<function<void()>> & ruleApplicators);
    
    static void applyRulesToCells(stack<function<void()>> & ruleApplicators);
    
    Grid grid = Grid(gridSize, cellSize);
    
    Window window;
    
    std::mutex sync;
    
    void updateView();
    
    void updateModels();

    void listenForEvents();
    
    void update();
    
    void render();
    
    float extracted(const sf::View &view);
    
    void recenterView();
    
    void randomSeed();
    
public:
    
    void run();
    
};

#endif /* Game_hpp */
