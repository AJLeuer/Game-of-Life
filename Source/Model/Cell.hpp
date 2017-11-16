//
//  Cell.hpp
//  Game of Life
//
//  Created by Adam J Leuer on 2017-11-15.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <vector>
#include <functional>

#include <SFML/Graphics/Vertex.hpp>

#include "../Util/Vect.h"

using namespace std;

/**
 * @brief Represents a Cell in the Game of Life, see the Wikipedia page linked below for more info
 *
 * @link https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules
 */
struct Cell : public sf::Vertex {
    
private:
    
    /**
     * Since a cell doesn't store its own position, it must be instantiated with a function object
     * that can provide this cell's location
     */
    function<vec2<unsigned int>()> positionGetter;
    
public:
    
    enum class State : bool {
        alive = true,
        dead = false
    } state = State::dead;
        
    Cell(function<vec2<unsigned int>()> positionGetter) :
        positionGetter(positionGetter)
    {
        
    }
        
    vec2<unsigned int> getPosition() const;
};

#endif /* Cell_hpp */
