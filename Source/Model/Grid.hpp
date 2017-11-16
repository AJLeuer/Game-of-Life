//
//  Grid.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include "Cell.hpp"
#include "../Util/Config.h"

class Grid {
    
    vector< vector<Cell>> cellGrid;
    
public:
    
    Grid();
    
};

#endif /* Grid_hpp */
