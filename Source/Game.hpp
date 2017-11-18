//
//  Game.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#ifndef Game_hpp
#define Game_hpp

#include <vector>

#include "./Model/Grid.hpp"
#include "./View/Window.h"
#include "./Util/Config.h"

class Game {
    
    Grid grid = Grid(gridSize, cellSize);
    
    Window window;

    void listenForEvents();
    
    void render();
    
    void recenterView();
    
public:
    
    void run();
    
};

#endif /* Game_hpp */
