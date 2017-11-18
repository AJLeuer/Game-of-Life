//
//  Grid.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Grid.hpp"



Grid::Grid(const unsigned size, const unsigned cellSize) :
    cellGrid(new vector<vector<Cell>>())
{
    for (unsigned x = 0; x < size; x++) {
        
        vector<Cell> gridColumn = vector<Cell>();
        
        for (unsigned y = 0; y < size; y++) {
            
            Cell cell(cellSize, {x, y});
            
            gridColumn.push_back(cell);
            
        }
        
        cellGrid->push_back(gridColumn);
    }
    
    auto cx = cellGrid->at(0);//debug
    bool ignore = true;
}
