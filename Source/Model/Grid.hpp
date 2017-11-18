//
//  Grid.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#ifndef Grid_hpp
#define Grid_hpp


#include "Cell.hpp"
#include "../Util/Config.h"

struct Grid {
    
private:
    
    void createCells(const unsigned size);
    
    void initializeAllCellNeighbors();
    
    void initializeCellNeighbors(Cell & cell);
    
public:
    
    vector< vector<Cell>> * cellGrid;
    
    Grid(const unsigned size, const unsigned cellSize);
    
    Cell & getCell(vec2<unsigned int> pos) { return cellGrid->at(pos.x()).at(pos.y()); }
};

#endif /* Grid_hpp */
