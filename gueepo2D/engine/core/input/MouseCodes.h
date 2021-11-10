#pragma once

// from SDL_mouse.h
#define MOUSE_BUTTON(X)       (1 << ((X)-1))
#define MOUSE_BUTTON_LEFT     1
#define MOUSE_BUTTON_MIDDLE   2
#define MOUSE_BUTTON_RIGHT    3
#define MOUSE_BUTTON_X1       4
#define MOUSE_BUTTON_X2       5
#define MOUSE_BUTTON_LMASK    MOUSE_BUTTON(V2D_BUTTON_LEFT)
#define MOUSE_BUTTON_MMASK    MOUSE_BUTTON(V2D_BUTTON_MIDDLE)
#define MOUSE_BUTTON_RMASK    MOUSE_BUTTON(V2D_BUTTON_RIGHT)
#define MOUSE_BUTTON_X1MASK   MOUSE_BUTTON(V2D_BUTTON_X1)
#define MOUSE_BUTTON_X2MASK   MOUSE_BUTTON(V2D_BUTTON_X2)

namespace gueepo {
	typedef enum {
		MOUSE_LEFT		= MOUSE_BUTTON_LEFT,
		MOUSE_MIDDLE	= MOUSE_BUTTON_MIDDLE,
		MOUSE_RIGHT			= MOUSE_BUTTON_RIGHT
	} Mousecode;
}