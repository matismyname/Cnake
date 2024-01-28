#include "gamestate.h"
#include "gamelogic.h"
#include <SDL2/SDL.h>
#include "clog.h"
#include "constants.h"
#include "rendergame.h"
#include "structlogic.h"
#include "gridlogic.h"
#include "moves.h"
#include "fruit.h"
#include "AI.h"
#include "Cnake.h"
#include "Cnakebody.h"
#include <stdlib.h>
#include "time.h"
#include <unistd.h> //Sleep function

void HandleGame(struct Gamestate* gamestate, SDL_Renderer* rdr) {
	srand(time(NULL));
	if (gamestate->computerplaying)
	{
		AIPlays(gamestate, rdr);
	}
	else
	{
		HumanPlays(gamestate, rdr);
	}
	return;
}

void HumanPlays(struct Gamestate* gamestate, SDL_Renderer* rdr) {
	Clog("The game begins!", "DEBUG");
	struct Cnake* cnake = InitializeCnake();
	struct Fruit* fruit = InitializeFruit();
	int xmove = 0;
	int ymove = 0;
	RenderGame(gamestate, fruit, cnake, rdr);
	struct Cnake* oldCnake = InitializeCnake();
	SDL_Event event;
	while (gamestate->isrunning) {
		if (!gamestate->gameover) {
			CopyCnake(cnake, oldCnake);
			CalculateCnakePosition(cnake, xmove, ymove);
			gamestate->gameover = CheckIfGameOver(cnake);
			if (!gamestate->gameover) {
				CheckIfFruitEaten(rdr, fruit, cnake, xmove, ymove);
				RenderEverything(rdr, cnake, fruit);
				SDL_Delay(SDLSLEEP);
			} else {
				oldCnake->colorR = 255;
				oldCnake->colorB = 0;
				oldCnake->colorG = 0;
				RenderEverything(rdr, oldCnake, fruit);
			}
		}
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					       	Clog("The game has been quit on the board by a QUIT event!", "DEBUG");
					       	gamestate->quitgame = true;
					       	gamestate->isrunning = false;
					       } break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q: {
								     Clog("The game has been quit on the board!", "DEBUG");
								     gamestate->quitgame = true;
								     gamestate->isrunning = false; } break;
						case SDLK_b: {
								     Clog("The player goes to the menu!", "DEBUG");
								     gamestate->isrunning = false;
								     gamestate->menu->isonmenu = true; } break;
						case SDLK_n: {
								     Clog("The player wants to play anew!", "DEBUG");
								     gamestate->isrunning = false;
								     gamestate->newgame = true; } break;
						case SDLK_UP: {
								      Clog("The Schnake is going up!", "DEBUG");
								      ymove = -10;
								      xmove = 0; } break;
						case SDLK_DOWN: {
								      Clog("The Schnake is going down!", "DEBUG");
								      ymove = 10;
								      xmove = 0; } break;
						case SDLK_LEFT: {
								      Clog("The Schnake is going left!", "DEBUG");
								      xmove = -10;
								      ymove = 0; } break;
						case SDLK_RIGHT: {
								      Clog("The Schnake is going right!", "DEBUG");
								      xmove = 10;
								      ymove = 0; } break;
						default: break;
					}
				default: break;
			}
		}
	}
	FreeFruit(fruit);
	FreeCnake(cnake);
	if (gamestate->newgame) {NewGame(gamestate, rdr); }
	return;
}

void NewGame(struct Gamestate* gamestate, SDL_Renderer* rdr) {
	gamestate->isrunning = true;
	gamestate->gameover = false;
	gamestate->newgame = false;
	HandleGame(gamestate, rdr);
}

void AIPlays(struct Gamestate* gamestate, SDL_Renderer* rdr) {
	struct Cnake* cnake = InitializeCnake();
	struct Fruit* fruit = InitializeFruit();
	RenderGame(gamestate, fruit, cnake, rdr);

	struct Moves* computerMoves[NUMOFCOMPUTERMOVES];
	for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
		computerMoves[i] = (struct Moves*)malloc(sizeof(struct Moves));
		computerMoves[i]->xmove = 0; 
		computerMoves[i]->ymove = 0; 
	}

	//Mock needed to calculate the possible moves of the Cnake without altering the actual game
	struct Cnake* mockCnake = InitializeCnake();
	struct Cnake* oldCnake = InitializeCnake();
	
	SDL_Event event;
	int xmove = 0;
	int ymove = 0;
	CopyCnake(cnake, mockCnake);
	while (gamestate->isrunning) {
		MinimizeManhattanDistance(mockCnake, fruit, computerMoves);
		for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
			if (!gamestate->gameover) {
				xmove = computerMoves[i]->xmove;
				ymove = computerMoves[i]->ymove;
				//The Cnake does not move or has eaten the fruit
				if (xmove == ymove) {
					continue;
				}
				CopyCnake(cnake, oldCnake);
				CalculateCnakePosition(cnake, xmove, ymove);
				gamestate->gameover = CheckIfGameOver(cnake);
				if (!gamestate->gameover) {
					CheckIfFruitEaten(rdr, fruit, cnake, xmove, ymove);
					RenderEverything(rdr, cnake, fruit);
					SDL_Delay(SDLSLEEP);
				} else {
					oldCnake->colorR = 255;
					oldCnake->colorB = 0;
					oldCnake->colorG = 0;
					RenderEverything(rdr, oldCnake, fruit);
				}
				computerMoves[i]->xmove = 0;
				computerMoves[i]->ymove = 0;
			}
		}
		CopyCnake(cnake, mockCnake);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					       	Clog("The game has been quit on the board by a QUIT event!", "DEBUG");
					       	gamestate->quitgame = true;
					       	gamestate->isrunning = false; } break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q: { 
							Clog("The game has been quit on the board by a KEYDOWN event!", "DEBUG");
							gamestate->quitgame = true;
							gamestate->isrunning = false; } break;
						case SDLK_n: {
							Clog("A new game has begun by a KEYDOWN event!", "DEBUG");
							gamestate->isrunning = false;
							gamestate->newgame = true; } break;
						case SDLK_b: {
							Clog("The AI goes back to the menu!", "DEBUG");
							gamestate->isrunning = false;
							gamestate->computerplaying = false;
							gamestate->menu->isonmenu = true; } break;
						default: break;
					}
				default: break;
			}
		}
	}
	//Free memory	
	FreeFruit(fruit);
	FreeCnake(mockCnake);
	FreeCnake(cnake);
	for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
		free(computerMoves[i]);
	}

	if (gamestate->newgame) {NewGame(gamestate, rdr); }
	return;
}

void CalculateCnakePosition(struct Cnake* cnake, int xmove, int ymove) {
	struct Cnakebody* tail = GetLastCnakebody(cnake->cnakebody);
	struct Cnakebody* head = cnake->cnakebody;
	int newX = 0;
	int newY = 0;

	//Update new head position
	newX = head->xpos + xmove;
	newY = head->ypos + ymove;

	//If there is only the head of the Cnake present
	if (head->childcnakebody == NULL) {
		FreeCnakebody(cnake->cnakebody);
		struct Cnakebody* newHead = InitializeCnakebody(newX, newY);
		cnake->cnakebody = newHead;
	} else {
		//Logic for the tail
		tail->parentcnakebody->childcnakebody = NULL; //The parent of the current tail will be the new tail
		tail->childcnakebody = head; //The tail becomes the new head

		//Logic for the head
		head->parentcnakebody = tail; //The parent now becomes the first part of the body after the head

		tail->xpos = newX;
		tail->ypos = newY;

		//Change the head of Cnake
		cnake->cnakebody = tail;
	}
	return;
}

void CheckIfFruitEaten(SDL_Renderer* rdr, struct Fruit* fruit, struct Cnake* cnake, int xmove, int ymove) {
	int fruitxpos = fruit->xpos;
	int fruitypos = fruit->ypos;

	int cnakeheadxpos = cnake->cnakebody->xpos;
	int cnakeheadypos = cnake->cnakebody->ypos;
	Clog_int("Cnake headposx: ", cnakeheadxpos, "DEBUG");
	Clog_int("Cnake headposy: ", cnakeheadypos, "DEBUG");

	if (fruitxpos == cnakeheadxpos && fruitypos == cnakeheadypos) {
		Clog("Nomnom!", "DEBUG");
		struct Cnakebody* tail = GetLastCnakebody(cnake->cnakebody);
		if (tail == NULL) {
			Clog("The tail of the Cnake does not exist!", "ERROR");
			exit(EXIT_FAILURE);
		}
		int xpos = tail->xpos + xmove;
		int ypos = tail->ypos + ymove;

		struct Cnakebody* newTail = InitializeCnakebody(xpos, ypos);
		if (newTail == NULL) {
			Clog("The new Cnake tail is null!", "ERROR");
			exit(EXIT_FAILURE);
		}

		tail->childcnakebody = newTail;
		newTail->parentcnakebody = tail;
		cnake->bodysum++;
		RenderFruit(rdr, cnake, fruit);
	}
	return;
}

bool CheckIfGameOver(struct Cnake* cnake) {
	int cnakeHeadXpos = cnake->cnakebody->xpos;
	int cnakeHeadYpos = cnake->cnakebody->ypos;
	if (cnakeHeadXpos < 0 || cnakeHeadXpos == SCREEN_W || cnakeHeadYpos < 0 || cnakeHeadYpos == SCREEN_H) {
		return true;
	}
	struct Cnakebody* head = cnake->cnakebody;
	struct Cnakebody* child = head->childcnakebody;
	while(child != NULL) {
		if (head->xpos == child->xpos && head->ypos == child->ypos) {
			return true;
		}
		child = child->childcnakebody;
	}
	return false;
}

