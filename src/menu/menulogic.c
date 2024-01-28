#include "menu.h"
#include "clog.h"
#include "menurenderer.h"
#include "constants.h"
#include <unistd.h>
#include <SDL2/SDL.h>

void HandleMenu(struct Menu* menu, SDL_Renderer* rdr) {
	if (!menu->rendered) {
		RenderMenu(rdr, menu);
		menu->rendered = true;
		Clog("The menu has been rendered!", "DEBUG");
	}

	SDL_Event event;
	while(menu->rendered) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				Clog("The game has been quit by an SDL_QUIT event!", "DEBUG");
				menu->quitgame = true;
				menu->rendered = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_q: {
							Clog("The player has quit the game from the board!", "DEBUG");
							menu->quitgame = true;
							menu->rendered = false;
							menu->isonmenu = false;
							return; } break;
					case SDLK_p: {
							Clog("The player wants to play!", "DEBUG");
							menu->gamestate->isrunning = true;
							menu->rendered = false; } break;
					case SDLK_c: {
							Clog("The computer will play!", "DEBUG");
							menu->gamestate->isrunning = true;
							menu->gamestate->computerplaying = true;
							menu->rendered = false; } break;
					default: break; 
				}
			}
		}
		sleep(SLEEP);
	}
	return;
}
