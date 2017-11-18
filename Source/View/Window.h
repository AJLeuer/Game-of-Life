//
//  Window.h
//  Chess
//
//  Created by Adam James Leuer on 2/13/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.

#ifndef __Chess__Window__
#define __Chess__Window__

#include <iostream>
#include <string>

#include <OpenGL/gl.h>

#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


#include "../Util/Vect.h"
#include "../Util/Color.h"
#include "../Util/Config.h"

#include "DisplayData.h"

using namespace std ;
using VideoMode = sf::VideoMode;
using Font = sf::Font;
using Text = sf::Text;

enum class Transparency : bool {
    opaque = true,
    transparent = false
};


class Window : public sf::RenderWindow {
	
protected:
	
	static VideoMode videoMode ;
	
	static VideoMode & setVideoMode() ;
	
	/**
	 * The Font used for displaying most text onscreen.
	 * 
	 * Currently using Apple's menlo font (which is based on Bitstream Vera Sans
	 * mono)
	 */
	static Font & font ;
	
	/**
	 * @note Need to create a quick initialization function
	 * for the SFML Font type here, since their constructors don't
	 * allow creating directly from a file, and we need to statically
	 * initialize font
	 */
	static Font & initFont() ;
	
	Text text ;
    
    TrueColor backgroundColor;
    
    Transparency transparency;
    
    void replaceViewWithCustomView();
	
public:
	
	Window(const Window & other) = delete ;
	
    Window(const string & title = "Window", const TrueColor backgroundColor = TrueColor {0x7F, 0x7F, 0x7F, 0xC0}) ;
	
	~Window() {}
	
	Window & operator = (const Window & other) = delete ;

	void display() ;
	
	void setBackgroundColor(const TrueColor color) ;
    const TrueColor & getBackgroundColor() const { return this->backgroundColor ; }
	
	template<class StringType>
	void displayText(const StringType & chars, const TrueColor color, const vec2<int> where) ;
	
};

template<class StringType>
void Window::displayText(const StringType & chars, const TrueColor color, const vec2<int> where) {
	
	text.setString(chars) ;
	text.setFillColor(color) ;
	
	auto textSize = text.getLocalBounds() ;
	
	vec2<unsigned> middle = {static_cast<unsigned>((textSize.width / 2)), static_cast<unsigned>((textSize.height / 2)) } ;
	
	vec2<unsigned> adjustedPos = where - middle ;
	
	text.setPosition(adjustedPos) ;
	
	this->RenderWindow::draw(text) ;
}

#endif /* defined(__Chess__Window__) */
