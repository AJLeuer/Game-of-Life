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

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Vect.h"
#include "../View/DisplayData.h"

using namespace std ;

static constexpr bool gameIsActive = true;

constexpr auto buttonMain = sf::Mouse::Button::Left ;

extern vec2<unsigned> mainWindowSize ;

extern string currentDirectory ;
extern string commandLineArgument ;

extern const string & defaultFontFilePath ;
extern const sf::Font defaultFont;

#endif
