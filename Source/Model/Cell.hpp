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

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Util/Config.h"
#include "../Util/Vect.h"
#include "../Util/Random.hpp"



using namespace std;

/**
 * @brief Represents a Cell in the Game of Life, see the Wikipedia page linked below for more info
 *
 * @link https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules
 */
struct Cell : public sf::RectangleShape {
    
private:
    
    static vec2<unsigned> calculatePositionInPixelCoordinates(const unsigned size, const vec2<unsigned> positionInGridCoordinates);
    
    static constexpr TrueColor livingCellColor = cellColor;
    
    static constexpr TrueColor deadCellColor { 0x00, 0x00, 0x00, 0xC0 };
    
    vec2<unsigned> gridPosition;
    
    vector<Cell *> neighbors;
    
public:
    
    enum class State : bool {
        alive = true,
        dead = false
    } state = State::dead;
        
    Cell(const unsigned size, const vec2<unsigned> positionOnGrid) :
        sf::RectangleShape(vec2<float>{size, size}),
        gridPosition(positionOnGrid)
    {
        this->setPosition(calculatePositionInPixelCoordinates(size, positionOnGrid));
    }
    
    void setNeighbors(const vector<Cell *> & neighbors) {
        this->neighbors = neighbors;
    }
        
    vec2<unsigned> getPosition() const {
        return this->sf::Transformable::getPosition();
    }
        
    const vec2<unsigned> getGridPosition() const {
        return gridPosition;
    }
        
    void update();
};

#endif /* Cell_hpp */
