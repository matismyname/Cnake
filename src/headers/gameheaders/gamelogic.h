#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "gamestate.h"
#include "Cnake.h"
#include "Cnakebody.h"
#include "fruit.h"
#include "moves.h"
#include <SDL2/SDL.h>

void HandleGame(struct Gamestate* gamestate, SDL_Renderer* rdr);
void HumanPlays(struct Gamestate* gamestate, SDL_Renderer* rdr);
void NewGame(struct Gamestate* gamestate, SDL_Renderer* rdr);
void AIPlays(struct Gamestate* gamestate, SDL_Renderer* rdr);
void CalculateCnakePosition(struct Cnake* cnake, int xmove, int ymove);
void CheckIfFruitEaten(SDL_Renderer* rdr, struct Fruit* fruit, struct Cnake* cnake, int xmove, int ymove);
bool CheckIfGameOver(struct Cnake* cnake);

#endif
