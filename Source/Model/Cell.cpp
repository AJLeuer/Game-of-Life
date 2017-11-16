//
//  Cell.cpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Cell.hpp"

vec2<unsigned> Cell::getPosition() const {
    return positionGetter();
}
