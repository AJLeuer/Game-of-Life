//
//  Cell.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.


#include "Cell.hpp"


vec2<int> centerPixelCoordinates(vec2<int> coordinates) {
    coordinates += pixelCenteringOffset;
    return coordinates;
}

vec2<int> Cell::calculatePositionInPixelCoordinates(const unsigned cellSize, const vec2<unsigned> positionInGridCoordinates) {
    
    int viewableGridAreaAdjustedOffset = (gridSize - displayedGridSize) / 2;
    const vec2 <int> adjustedPositionInGridCoordinates = positionInGridCoordinates - vec2<int>{viewableGridAreaAdjustedOffset, viewableGridAreaAdjustedOffset};

    int xPixelCoord = adjustedPositionInGridCoordinates.x() * cellSize;
    int yPixelCoord = adjustedPositionInGridCoordinates.y() * cellSize;
    
    const int horizontalGridSpacingOffset = adjustedPositionInGridCoordinates.x() * cellSpacing;
    const int verticalGridSpacingOffset = adjustedPositionInGridCoordinates.y() * cellSpacing;
    
    xPixelCoord += horizontalGridSpacingOffset;
    yPixelCoord += verticalGridSpacingOffset;

    vec2<int> initialPixelCoordinates{ xPixelCoord, yPixelCoord };
    
    vec2<int> centeredPixelCoordinates = centerPixelCoordinates(initialPixelCoordinates);
    
    return centeredPixelCoordinates;
}

void Cell::update() {

}

void Cell::die() {
    this->state = State::dead;
    this->setFillColor(Cell::colorWhenDead);
}

void Cell::live() {
    this->state = State::alive;
    this->setFillColor(Cell::colorWhileAlive);
}


const unsigned Cell::countOfNeighborCellsInState(const State state) const {
    unsigned count = 0;
    
    for (Cell * neighborCell : neighbors) {
        if (neighborCell->state == state) {
            count++;
        }
    }
    return count;
}






