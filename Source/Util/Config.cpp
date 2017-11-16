//
//  Config.cpp
//  Chess
//
//  Created by Adam James Leuer on 3/16/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Config.h"

vec2<unsigned> setMainWindowSize() {
    return DisplayData::getScreenResolution() ;
}

sf::Font initDefaultFont() {
    sf::Font font;
    font.loadFromFile(defaultFontFilePath);
    return font;
}


vec2<unsigned> mainWindowSize = setMainWindowSize() ;

string currentDirectory("") ;
string commandLineArgument("") ;

const string & defaultFontFilePath {"./Assets/Fonts/Menlo-Regular.ttf"} ;
const sf::Font defaultFont = initDefaultFont();



