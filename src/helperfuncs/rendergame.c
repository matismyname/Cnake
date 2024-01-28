#include "gamestate.h"
#include "constants.h"
#include "structlogic.h"
#include "gridlogic.h"
#include "rendergame.h"
#include "clog.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <unistd.h>

//Creates the Cnake and a random fruit for the Cnake to eat
void RenderGame(struct Gamestate* gamestate, struct Fruit* fruit, struct Cnake* cnake, SDL_Renderer* rdr) {
	RenderBoard(rdr);
	RenderCnakeHead(rdr, cnake);
	RenderFruit(rdr, cnake, fruit);
	return;
}

void RenderBoard(SDL_Renderer* rdr) {
	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderClear(rdr);
	SDL_RenderPresent(rdr);
	return;
}

void RenderFruit(SDL_Renderer* rdr, struct Cnake* cnake, struct Fruit* fruit) {
	SDL_SetRenderDrawColor(rdr, fruit->colorR, fruit->colorG, fruit->colorB, 255);
	int xpos = 0;
	int ypos = 0;
	xpos = RandomPointSnappedToGrid(SCREEN_W, HEAD_W);
	ypos = RandomPointSnappedToGrid(SCREEN_H, HEAD_H);

	int flag = 1;
	//Make sure that the fruit and the Cnake body do not share the same pixels when the fruit is spawned
	while (flag) {
		struct Cnakebody* cnakebody = cnake->cnakebody;
		flag = 0;
		while (cnakebody != NULL) {
			if (cnakebody->xpos == xpos && cnakebody->ypos == ypos) {
				flag = 1;
				xpos = RandomPointSnappedToGrid(SCREEN_W, HEAD_W);
				ypos = RandomPointSnappedToGrid(SCREEN_H, HEAD_H);
			}
			cnakebody = cnakebody->childcnakebody;
			if (flag) {
				cnakebody = NULL;
			}
		}
	}

	fruit->xpos = xpos;
	fruit->ypos = ypos;

	FillRect(rdr, xpos, ypos, HEAD_W, HEAD_H);
	SDL_RenderPresent(rdr);
	Clog_int("Fruit xpos: ", xpos, "DEBUG");
	Clog_int("Fruit ypos: ", ypos, "DEBUG");
	return;
}

void RenderCnakeHead(SDL_Renderer* rdr, struct Cnake* cnake) {
	SDL_SetRenderDrawColor(rdr, cnake->colorR, cnake->colorG, cnake->colorB, 255);
	int xpos = RandomPointSnappedToGrid(SCREEN_W, HEAD_W);
	int ypos = RandomPointSnappedToGrid(SCREEN_H, HEAD_H);

	//Logging
	Clog_int("Cnake xpos: ", xpos, "DEBUG");
	Clog_int("Cnake ypos: ", ypos, "DEBUG");
	//End Logging
	struct Cnakebody* cnakebody = InitializeCnakebody(xpos, ypos);
	cnake->cnakebody = cnakebody;
	cnake->bodysum++;

	FillRect(rdr, xpos, ypos, HEAD_W, HEAD_H);
	SDL_RenderPresent(rdr);
	return;
}

void FillRect(SDL_Renderer* rdr, int xpos, int ypos, int width, int height) {
	SDL_Rect rect;
	rect.x = xpos;
	rect.y = ypos;
	rect.w = width;
	rect.h = height;

	SDL_RenderFillRect(rdr, &rect);
}

//This function renders the whole board while the Cnake moves
void RenderEverything(SDL_Renderer* rdr, struct Cnake* cnake, struct Fruit* fruit) {
	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderClear(rdr);
	SDL_RenderPresent(rdr);

	//FillRect every part of the Cnake body one by one
	SDL_SetRenderDrawColor(rdr, cnake->colorR, cnake->colorG, cnake->colorB, 255);
	int saveswitch = 0;
	struct Cnakebody* cnakebody = cnake->cnakebody; 
	cnakebody = cnake->cnakebody; 
	while(cnakebody != NULL) {
		Clog("Cnakebody not null!", "DEBUG");
		FillRect(rdr, cnakebody->xpos, cnakebody->ypos, HEAD_W, HEAD_H);
		cnakebody = cnakebody->childcnakebody;
		saveswitch++;
		if (saveswitch > 10000)
		{
			Clog("Something went wrong in the render everything function!", "ERROR");
			exit(EXIT_FAILURE);
		}
	}
	//Finally, render the fruit
	SDL_SetRenderDrawColor(rdr, fruit->colorR, fruit->colorG, fruit->colorB, 255);
	FillRect(rdr, fruit->xpos, fruit->ypos, HEAD_W, HEAD_H);
	SDL_RenderPresent(rdr);
}

