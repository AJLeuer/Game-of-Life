//
//  Game.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <thread>
#include <chrono>

#include "./Model/Grid.hpp"
#include "./View/Window.h"
#include "./View/DisplayData.h"
#include "./Util/Config.h"

using namespace std;

class Game {
    
    Grid grid = Grid(gridSize, cellSize);
    
    Window window;
    
    void updateView();
    
    void updateModels();

    void listenForEvents();
    
    void update();
    
    void render();
    
    void recenterView();
    
public:
    
    void run();
    
};

#endif /* Game_hpp */
