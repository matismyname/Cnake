#ifndef _GAMEHEADER_H_
#define _GAMEHEADER_H_
#include "menu.h"
#include "gamestate.h"

void InitializeGame(SDL_Renderer* rdr);
void RunGame(struct Menu* menu, struct Gamestate* gamestate, SDL_Renderer* rdr);

#endif
