#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameflow.h"
#include "clog.h"
#include "gamestate.h"
#include "menu.h"
#include "constants.h"
#include "structlogic.h"
#include "gamelogic.h"
#include "menulogic.h"
#include <unistd.h>
#include <stdbool.h>

void InitializeGame(SDL_Renderer* rdr) {
	//Initialize Gamestate
	struct Menu* menu = InitializeMenu();

	//Initialize Gamestate
	struct Gamestate* gamestate = InitializeGamestate();

	//Link Menu and Gamestate
	LinkMenuAndGamestate(menu, gamestate);
	RunGame(menu, gamestate, rdr);
	FreeMenu(menu);
	FreeGamestate(gamestate);
	return;
}

void RunGame(struct Menu* menu, struct Gamestate* gamestate, SDL_Renderer* rdr) {
	while (!menu->quitgame && !gamestate->quitgame) {	
		if (gamestate->isrunning) { HandleGame(gamestate, rdr); }
		else if (menu->isonmenu) { HandleMenu(menu, rdr); }
		if (menu->quitgame) {Clog("menu->quitgame is true!", "DEBUG");}
		if (gamestate->quitgame) {Clog("gamestate->quitgame is true!", "DEBUG");}
		sleep(SLEEP);
	}
	return;
}
