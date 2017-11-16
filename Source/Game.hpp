//
//  Game.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#ifndef Game_hpp
#define Game_hpp

#include "./View/Window.h"

class Game {
    
    Window window;
    
    void listenForEvents();
    
public:
    
    void run();
    
};

#endif /* Game_hpp */
