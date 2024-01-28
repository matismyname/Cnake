#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "gamestate.h"
#include "Cnake.h"
#include "Cnakebody.h"
#include "fruit.h"
#include "clog.h"
#include "constants.h"
#include "structlogic.h"

struct Menu* InitializeMenu(void) {
	struct Menu* menu = (struct Menu*)malloc(sizeof(struct Menu));
	if (menu == NULL) {
		Clog("Failed to allocate memory for Menu struct!", "ERROR");
		exit(EXIT_FAILURE);
	}

	menu->img = MAINMENUIMG;
	menu->isonmenu = true;
	menu->quitgame = false;
	menu->rendered = false;
	return menu;
}

struct Gamestate* InitializeGamestate(void) {
	struct Gamestate* gamestate = (struct Gamestate*)malloc(sizeof(struct Gamestate));
	if (gamestate == NULL) {
		Clog("Failed to allocate memory for Gamestate struct!", "ERROR");
		exit(EXIT_FAILURE);
	}
	gamestate->isrunning = false;
	gamestate->gameover = false;
	gamestate->computerplaying = false;
	gamestate->quitgame = false;
	gamestate->newgame = false;
	return gamestate;
}

struct Cnake* InitializeCnake(void) {
	struct Cnake* cnake = (struct Cnake*)malloc(sizeof(struct Cnake));
	cnake->colorR = 255;
	cnake->colorB = 255;
	cnake->colorG = 255;
	cnake->bodysum = 0;
	struct Cnakebody* cnakebody = (struct Cnakebody*)malloc(sizeof(struct Cnakebody));
	return cnake;
}

struct Cnakebody* InitializeCnakebody(int xpos, int ypos) {
	struct Cnakebody* cnakebody = (struct Cnakebody*)malloc(sizeof(struct Cnakebody));
	cnakebody->xpos = xpos;
	cnakebody->ypos = ypos;
	cnakebody->parentcnakebody = NULL;
	cnakebody->childcnakebody = NULL;
	return cnakebody;
}

struct Fruit* InitializeFruit(void) {
	struct Fruit* fruit = (struct Fruit*)malloc(sizeof(struct Fruit));
	fruit->xpos = 0;
	fruit->ypos = 0;
	fruit->colorR = 0;
	fruit->colorB = 0;
	fruit->colorG = 255;
	fruit->isrendered = false;
	return fruit;
}

void LinkMenuAndGamestate(struct Menu* menu, struct Gamestate* gamestate) {
	menu->gamestate = gamestate;
	gamestate->menu = menu;
	return;
}

void FreeMenu(struct Menu* menu) {
	free(menu);
	Clog("Menu freed!", "DEBUG");
	return;
}

void FreeGamestate(struct Gamestate* gamestate) {
	free(gamestate);
	Clog("Gamestate freed!", "DEBUG");
	return;
}

void FreeCnake(struct Cnake* cnake) {
	FreeCnakebody(cnake->cnakebody);
	free(cnake);
	cnake = NULL;
	Clog("Cnake freed!", "DEBUG");
	return;
}

void FreeCnakebody(struct Cnakebody* cnakebody) {
	if (cnakebody->childcnakebody != NULL) { FreeCnakebody(cnakebody->childcnakebody); }
	free(cnakebody);
	Clog("Cnakebody freed!", "DEBUG");
	return;
}

void FreeFruit(struct Fruit* fruit) {
	free(fruit);
	fruit = NULL;
	Clog("Fruit freed!", "DEBUG");
	return;
}

struct Cnakebody* GetLastCnakebody(struct Cnakebody* cnakebody) {
	if (cnakebody->childcnakebody == NULL) {
		Clog("Cnakebody returned!", "DEBUG");
		return cnakebody;
	}
	else {
		return GetLastCnakebody(cnakebody->childcnakebody);
	}
}

void CopyCnake(struct Cnake* original, struct Cnake* copy) {
	int saveswitch = 0;

	//Copy Cnake
	copy->bodysum = original->bodysum;
	copy->colorR = original->colorR;
	copy->colorG = original->colorG;
	copy->colorB = original->colorB;

	struct Cnakebody* originalCnakebody = original->cnakebody;
	struct Cnakebody* head = InitializeCnakebody(0, 0);
	copy->cnakebody = head;
	InitializeAndUpdateCnakebody(head, originalCnakebody);
	return;
}

//Copy all the details of the Cnakebody
void InitializeAndUpdateCnakebody(struct Cnakebody* parent, struct Cnakebody* originalCnakebody) {
	parent->xpos = originalCnakebody->xpos;
	parent->ypos = originalCnakebody->ypos;

	if (originalCnakebody->childcnakebody == NULL) {
		return;
	}
	struct Cnakebody* child = InitializeCnakebody(0, 0);
	parent->childcnakebody = child;
	child->parentcnakebody = parent;
	InitializeAndUpdateCnakebody(child, originalCnakebody->childcnakebody);
	return;
}

