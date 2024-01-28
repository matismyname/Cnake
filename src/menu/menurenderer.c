#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.h"
#include "clog.h"
#include "constants.h"

void RenderMenu(SDL_Renderer* rdr, struct Menu* menu)
{
	SDL_Surface* imageSurface = IMG_Load(menu->img);
	if (!imageSurface)
	{
		Clog_char("IMG_Load: ", IMG_GetError(), "ERROR");
		exit(EXIT_FAILURE);
	}
    	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(rdr, imageSurface);
    	SDL_FreeSurface(imageSurface);

    	SDL_Rect destinationRect = { 0, 0, SCREEN_H, SCREEN_W };
	SDL_RenderClear(rdr);
    	SDL_RenderCopy(rdr, imageTexture, NULL, &destinationRect);
    	SDL_RenderPresent(rdr);
}

