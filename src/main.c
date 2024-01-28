#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "clog.h"
#include "gameflow.h"
#include "initSDL.h"

int main(void) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		 Clog_char("Could not initialize SDL2: ", SDL_GetError(), "ERROR");
		 exit(EXIT_FAILURE);
	}

	SDL_Window* window = InitializeWindow();
	SDL_Renderer* rdr = InitializeRenderer(window);
	Clog("Window and Renderer created!", "DEBUG");
	InitializeGame(rdr); //Takes care of the menus and the actual game
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
