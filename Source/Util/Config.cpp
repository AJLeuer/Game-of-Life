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

const vec2<unsigned> calculatePixelCenteringOffset() {
    vec2<int> viewCenter = static_cast<vec2<int>>(mainWindowSizePhysicalPixels() / 2);
    vec2<int> halfGridSize = static_cast<vec2<int>>(gridSizeInPixels() / 2);
    
    vec2<unsigned> offset = viewCenter - halfGridSize;
    
    //for some reason the y offset this calculates pushes content too far down, so pull it back a bit
    offset.value.y = offset.y() / 1.5;
    
    return offset;
}

const vec2<unsigned> pixelCenteringOffset = calculatePixelCenteringOffset();

vec2<unsigned> mainWindowSizeLogicalPixels() {
    vec2<unsigned> mainWindowSizeLogicalPixels = setMainWindowSize();
    return mainWindowSizeLogicalPixels;
}

vec2<unsigned> mainWindowSizePhysicalPixels() {
    vec2<unsigned> mainWindowSizePhysicalPixels = mainWindowSizeLogicalPixels() * DisplayData::getDisplayScalingFactor();
    return mainWindowSizePhysicalPixels;
}

string currentDirectory("") ;
string commandLineArgument("") ;

const string & defaultFontFilePath {"./Assets/Fonts/Menlo-Regular.ttf"} ;
const sf::Font defaultFont = initDefaultFont();



