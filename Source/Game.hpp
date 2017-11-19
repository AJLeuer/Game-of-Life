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
#include "./View/DisplayData.h"
#include "./Util/Config.h"
#include "./Util/Random.hpp"

using namespace std;

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
    
    static void checkCellsForRulesToApply(Cell & cell, stack<function<void()>> & ruleApplicators);
    
    static void applyRulesToCells(stack<function<void()>> & ruleApplicators);
    
    Grid grid = Grid(gridSize, cellSize);
    
    Window window;
    
    void updateView();
    
    void updateModels();

    void listenForEvents();
    
    void update();
    
    void render();
    
    void recenterView();
    
    void seed();
    
public:
    
    void run();
    
};

#endif /* Game_hpp */
