//
//  Cell.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.


#include "Cell.hpp"


vec2<unsigned> centerPixelCoordinates(vec2<unsigned> coordinates) {
    coordinates += pixelCenteringOffset;
    return coordinates;
}

vec2<unsigned> Cell::calculatePositionInPixelCoordinates(const unsigned size, const vec2<unsigned> positionInGridCoordinates) {

    unsigned xPixelCoord = positionInGridCoordinates.x() * size;
    unsigned yPixelCoord = positionInGridCoordinates.y() * size;
    
    const unsigned horizontalGridSpacingOffset = positionInGridCoordinates.x() * cellSpacing;
    const unsigned verticalGridSpacingOffset = positionInGridCoordinates.y() * cellSpacing;
    
    xPixelCoord += horizontalGridSpacingOffset;
    yPixelCoord += verticalGridSpacingOffset;

    vec2<unsigned> initialPixelCoordinates{ xPixelCoord, yPixelCoord };
    
    vec2<unsigned> centeredPixelCoordinates = centerPixelCoordinates(initialPixelCoordinates);
    
    return centeredPixelCoordinates;
}

void Cell::update() {

}

void Cell::die() {
    this->state = State::dead;
    this->setFillColor(Cell::deadCellColor);
}

void Cell::live() {
    this->state = State::alive;
    this->setFillColor(Cell::livingCellColor);
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






