#ifndef _RENDERGAME_H_
#define _RENDERGAME_H_

#include "gamestate.h"
#include "fruit.h"
#include "Cnake.h"
#include <SDL2/SDL.h>

void RenderGame(struct Gamestate* gamestate, struct Fruit* fruit, struct Cnake* cnake, SDL_Renderer* rdr);
void RenderBoard(SDL_Renderer* rdr);
void RenderFruit(SDL_Renderer* rdr, struct Cnake* cnake, struct Fruit* fruit);
void RenderCnakeHead(SDL_Renderer* rdr, struct Cnake* cnake);
void FillRect(SDL_Renderer* rdr, int xpos, int ypos, int width, int height);
void RenderEverything(SDL_Renderer* rdr, struct Cnake* cnake, struct Fruit* fruit);

#endif
