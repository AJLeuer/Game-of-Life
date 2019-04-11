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


int main(int argc, const char * argv[])
{
    Game gameOfLife;

    gameOfLife.start();

    return 0;
}
