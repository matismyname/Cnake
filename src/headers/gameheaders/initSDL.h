#ifndef _INIT_SDL_H_
#define _INIT_SDL_H_

#include <SDL2/SDL.h>

SDL_Window* InitializeWindow(void);
SDL_Renderer* InitializeRenderer(SDL_Window* window);

#endif
