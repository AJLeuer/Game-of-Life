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
    createCells(size);
    initializeAllCellNeighbors();

    auto & firstColumn = cellGrid->at(gridSize - 1);
    auto & secondToLastColumn = cellGrid->at(gridSize - 2); //debug
    auto & lastColumn = cellGrid->at(gridSize - 1);
    bool ignore = true;
}

void Grid::createCells(const unsigned size) {
    for (unsigned x = 0; x < size; x++) {
        vector<Cell> gridColumn = vector<Cell>();
        for (unsigned y = 0; y < size; y++) {
            Cell cell(cellSize, {x, y});
            gridColumn.push_back(std::move(cell));
        }
        cellGrid->push_back(std::move(gridColumn));
    }
}

void Grid::initializeAllCellNeighbors() {
    for (auto & columnOfCells : * cellGrid) {
        for (Cell & cell : columnOfCells) {
            initializeCellNeighbors(cell);
        }
    }
}

void Grid::initializeCellNeighbors(Cell & cell) {
    vector<Cell *> neighbors;
    const vec2<unsigned> position = cell.getGridPosition();
    
    const unsigned neighborSearchStartPositionX = (position.x() <= 0) ? 0 : position.x() - 1;
    const unsigned neighborSearchStartPositionY = (position.y() <= 0) ? 0 : position.y() - 1;
    
    const unsigned neighborSearchEndPositionX = (position.x() >= (gridSize - 1)) ? (gridSize - 1) : position.x() + 1;
    const unsigned neighborSearchEndPositionY = (position.y() >= (gridSize - 1)) ? (gridSize - 1) : position.y() + 1;
    
    for (unsigned x = neighborSearchStartPositionX; x <= neighborSearchEndPositionX; x++) {
        for (unsigned y = neighborSearchStartPositionY; y <= neighborSearchEndPositionY; y++) {
            if ((x == position.x()) && (y == position.y())) {
                continue;
            }
            Cell & cell = cellGrid->at(x).at(y);
            neighbors.push_back(& cell);
        }
    }
    
    cell.setNeighbors(neighbors);
}



