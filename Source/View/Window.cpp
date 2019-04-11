//
//  Window.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/13/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Window.h"

 ;
//using namespace sf ;

Font & Window::font = Window::initFont() ;

VideoMode Window::videoMode = setVideoMode() ;

Font & Window::initFont() {
	static Font storedFont ;
	string mainFontFilePathCopy(defaultFontFilePath) ; //debug code
	storedFont.loadFromFile(defaultFontFilePath) ;
	return storedFont ;
}

VideoMode & Window::setVideoMode() {
	const vec2<unsigned> baseWindowSize {mainWindowSizeLogicalPixels().value.x, mainWindowSizeLogicalPixels().value.y} ;
	const float dpiScale (DisplayData::getDisplayScalingFactor<float>()) ;
	vec2<unsigned> scaledWindowSize { static_cast<unsigned>(baseWindowSize.value.x * dpiScale), static_cast<unsigned>(baseWindowSize.value.y * dpiScale) } ;
	videoMode = VideoMode(scaledWindowSize.value.x, scaledWindowSize.value.y) ;
	return videoMode ; //self assigns
}



/* Below are the (unfinished) implementations for non-Apple platforms */

Window::Window(const string & title, const TrueColor backgroundColor) :
	RenderWindow(videoMode, title, sf::Style::Default, getSettings()),
	backgroundColor{0xAA, 0xAA, 0xAA, 0xAA}
{

}



void Window::setBackgroundColor(const TrueColor color) {
	//todo implement for non-Apple unix, win
}

void Window::display()
{
	sf::RenderWindow::display();
}
