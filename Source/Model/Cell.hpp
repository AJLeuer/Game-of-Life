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


using std::vector;


/**
 * @brief Represents a Cell in the Game of Life, see the Wikipedia page linked below for more info
 *
 * @link https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules
 */
struct Cell : public sf::RectangleShape {
    
private:
    
    static vec2<int> calculatePositionInPixelCoordinates(const unsigned cellSize, const vec2<unsigned> positionInGridCoordinates);
    
    
    static constexpr TrueColor livingCellColor = cellColor;
    
    static constexpr TrueColor deadCellColor { 0xF0, 0xF0, 0xF0, 0xFF };
    
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
        die();
    }
    
    Cell(Cell && other) :
        sf::RectangleShape(std::move(other)),
        gridPosition(std::move(other.gridPosition)),
        neighbors(std::move(other.neighbors))
    {
        
    }
        
    Cell(const Cell & other) = delete;
        
    Cell & operator = (Cell && other) {
        if (this != & other) {
            this->sf::RectangleShape::operator=(other);
            gridPosition = std::move(other.gridPosition);
            neighbors = std::move(other.neighbors);
        }
        return * this;
    }
        
    Cell & operator = (const Cell & other) = delete;
    
    void setNeighbors(const vector<Cell *> & neighbors) {
        this->neighbors = neighbors;
    }
        
    vec2<unsigned> getPosition() const {
        return this->sf::Transformable::getPosition();
    }
        
    const vec2<unsigned> getGridPosition() const {
        return gridPosition;
    }
    
    /**
     * @param state The state to check
     *
     * @return The number of neighbor cells in the State state (i.e. the number alive or the number dead, depending on which state the caller
     * wants to check)
     */
    const unsigned countOfNeighborCellsInState(const State state) const;
        
    void update();
        
    void die();
        
    void live();
};

#endif /* Cell_hpp */
