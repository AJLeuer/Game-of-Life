//
//  Window.m
//  Chess
//
//  Created by Adam James Leuer on 4/23/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifdef __APPLE__


#import <Foundation/Foundation.h>
#import <Foundation/NSKeyedArchiver.h>
#import <AppKit/NSWindow.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSOpenGLView.h>
#import <AppKit/NSOpenGL.h>


#include "Window.h"


namespace sf {
	namespace priv {
		class WindowImplCocoa;
	}
}

@class SFSilentResponder;

@interface SFOpenGLView : NSOpenGLView
{
	sf::priv::WindowImplCocoa*    m_requester;      ///< View's requester
	BOOL                          m_useKeyRepeat;   ///< Key repeat setting
	BOOL                          m_mouseIsIn;      ///< Mouse positional state
	NSTrackingArea*               m_trackingArea;   ///< Mouse tracking area
	BOOL                          m_fullscreen;     ///< Indicate whether the window is fullscreen or not
	CGFloat                       m_scaleFactor;    ///< Display scale factor (e.g. 1x for classic display, 2x for retina)
	
	// Hidden text view used to convert key event to actual chars.
	// We use a silent responder to prevent sound alerts.
	SFSilentResponder*  m_silentResponder;
	NSTextView*         m_hiddenTextView;
}

@end



@interface CustomOpenGLView : SFOpenGLView {
    Transparency transparency;
    int * opacity;
}

- (instancetype)init:(Transparency)transparency;

- (instancetype)initByCopy:(SFOpenGLView *)other withTransparency:(Transparency)transparency;

+ (void) copy:(SFOpenGLView *)other to_self:(CustomOpenGLView *)to_self;

- (BOOL)isOpaque ;

@end

@implementation CustomOpenGLView {
	
}

-(instancetype)init:(Transparency)transparency {
    self = [super init];
    
    self->transparency = transparency;
    opacity = (int *) & transparency;
    
    auto context = [self openGLContext] ;
    [context setValues:opacity forParameter:NSOpenGLContextParameterSurfaceOpacity];
    
    return self;
}

- (instancetype)initByCopy:(SFOpenGLView *)other withTransparency:(Transparency)transparency {
    self = [self init : transparency] ;
	
	[CustomOpenGLView copy: other to_self:self] ;
    
	return self ;
}


+ (void) copy:(SFOpenGLView *)other to_self:(CustomOpenGLView *)to_self {
	to_self->m_requester = other->m_requester ;
	to_self->m_useKeyRepeat = other->m_useKeyRepeat ;
	to_self->m_mouseIsIn = other->m_mouseIsIn ;
	to_self->m_trackingArea = other->m_trackingArea ;
	to_self->m_fullscreen = other->m_fullscreen ;
	to_self->m_scaleFactor = other->m_scaleFactor ;
	to_self->m_silentResponder = other->m_silentResponder ;
	to_self->m_hiddenTextView = other->m_hiddenTextView ;
	
	[to_self setOpenGLContext: [other openGLContext]] ;
	[[to_self openGLContext] setView: to_self] ;
	[to_self setPixelFormat: [other pixelFormat]] ;
}

- (BOOL)isOpaque {
    if (transparency == Transparency::transparent) {
        return NO;
    }
    else {
        return YES;
    }
}

@end



Window::Window(const string & title, const TrueColor backgroundColor) :
    RenderWindow(videoMode, title, sf::Style::Default, sf::ContextSettings()),
    backgroundColor(backgroundColor),
    transparency((backgroundColor.A_float() < 1.0) ? Transparency::transparent : Transparency::opaque)
{
	
	text.setFont(font) ;
	text.setCharacterSize(60) ;
	
    replaceViewWithCustomView();
    
    this->RenderWindow::setVisible(true);
}

void Window::display() {
	/* for some reason we need to call the native update method as well as SFML's */
    NSWindow * this_window = (__bridge NSWindow *)(this->getSystemHandle()) ;
    [this_window displayIfNeeded] ;
	
	this->RenderWindow::display() ;
}



void Window::setBackgroundColor(const TrueColor color) {
    this->backgroundColor = color;
	
	NSWindow * this_window = (__bridge NSWindow *)(this->getSystemHandle()) ;
	
	NSColor * nativeBackgroundColor = [NSColor colorWithDeviceRed:backgroundColor.R_float() green:backgroundColor.G_float() blue:backgroundColor.B_float() alpha:backgroundColor.A_float()];
	
    auto opaque = (transparency == Transparency::opaque) ? YES : NO;
    auto transparentTitlebar = (transparency == Transparency::transparent) ? YES : NO;
    
    [this_window setOpaque:opaque];
    [this_window setTitlebarAppearsTransparent:transparentTitlebar];
	[this_window setBackgroundColor:nativeBackgroundColor];
    [this_window setAlphaValue:CGFloat(backgroundColor.A_float())];
}

void Window::replaceViewWithCustomView() {
    NSWindow * this_window = (__bridge NSWindow *)(this->getSystemHandle()) ;
    SFOpenGLView * view = [this_window contentView] ;
    CustomOpenGLView * replacementView = [[CustomOpenGLView alloc] initByCopy:view withTransparency:transparency] ;
    this_window.contentView = replacementView ;
    this->setBackgroundColor(backgroundColor);
}
























#endif
