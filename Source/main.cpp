//
//  main.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 9/5/17.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#include <iostream>
#include <thread>

#include "Model/Cell.hpp"
#include "Game.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    auto positionGetter = [] () -> vec2<unsigned int> {
        return {1, 1};
    };
    
    Cell cell(positionGetter);
    auto pos = cell.getPosition();
    


    Game gameOfLife;

    gameOfLife.run();

    return 0;
}
