#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "menu.h"
#include "Cnake.h"
#include <stdbool.h>

struct Gamestate {
	bool isrunning;
	bool gameover;
	bool computerplaying;
	bool quitgame;
	bool newgame;
	struct Menu* menu;
};

#endif
