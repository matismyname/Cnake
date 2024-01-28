#ifndef _MENU_H_
#define _MENU_H_
#include "gamestate.h"
#include <stdbool.h>

struct Menu {
	const char* img;
	bool isonmenu;
	bool rendered;
	bool quitgame;
	struct Gamestate* gamestate;
};

#endif
