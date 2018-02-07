//
//  Config.h
//  Chess
//
//  Created by Adam James Leuer on 3/14/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Config_h
#define Chess_Config_h

#include <iostream>
#include <string>
#include <chrono>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Vect.h"
#include "../View/DisplayData.h"
#include "../Util/Color.h"

using std::string;

static constexpr bool gameIsActive = true;

constexpr auto buttonMain = sf::Mouse::Button::Left ;

/**
 * The number of pixels in each cell
 */
static constexpr unsigned cellSize = 6;

/**
 * The number of pixels between each cell
 */
static constexpr unsigned cellSpacing = 1;

/**
 * The number of cells in each row and column of the grid
 */
static constexpr unsigned gridSize = 384;

static constexpr unsigned displayedGridSize = 384;

/**
 * The number of pixels composing the grid in the x and y directions
 */
static constexpr const vec2<unsigned> gridSizeInPixels() {
    auto pixelCount = (gridSize * cellSize) + (gridSize * cellSpacing);
    return {pixelCount, pixelCount};
}

static constexpr TrueColor cellColor(0x00, 0xC0, 0xFF, 0xFF);

extern vec2<unsigned> mainWindowSizeLogicalPixels() ;
extern vec2<unsigned> mainWindowSizePhysicalPixels() ;

static constexpr std::chrono::milliseconds defaultRefreshRateInterval(384);

extern const vec2<int> pixelCenteringOffset;

extern string currentDirectory ;
extern string commandLineArgument ;

extern const string & defaultFontFilePath ;
extern const sf::Font defaultFont;

#endif
