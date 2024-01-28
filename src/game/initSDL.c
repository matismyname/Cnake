#include <SDL2/SDL.h>
#include "constants.h"
#include "clog.h"

SDL_Window* InitializeWindow(void)
{
	//Create a window pointer
	SDL_Window *window = SDL_CreateWindow(GAMENAME,
			WINPOS_X,
			WINPOS_Y,
			SCREEN_W,
			SCREEN_H,
			0);
	//If it failed, exit with a failure
	if (window == NULL)
	{
		Clog_char("SDL_CreateWindow Error: %s\n", SDL_GetError(), "ERROR");
		exit(EXIT_FAILURE);
	}
	return window;
}

SDL_Renderer* InitializeRenderer(SDL_Window* window)
{	
	//Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//If the renderer creation fails, destroy the window and return failure
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		Clog_char("SDL_CreateRenderer Error: %s\n", SDL_GetError(), "ERROR");
		exit(EXIT_FAILURE);
	}
	return renderer;
}

