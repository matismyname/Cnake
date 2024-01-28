#include "Cnake.h"
#include "fruit.h"
#include "moves.h"
#include "fruit.h"
#include "gamestate.h"
#include <stdlib.h>
#include "gamelogic.h"
#include "structlogic.h"
#include "AI.h"


void MinimizeManhattanDistance(struct Cnake* cnake, struct Fruit* fruit, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]) {	
	//Initialize Mock
	struct Gamestate* mockGamestate = InitializeGamestate();
	
	int fruitXpos = fruit->xpos;
	int fruitYpos = fruit->ypos;

	struct Cnake* mockCnakeToMinimize = InitializeCnake();
	struct Cnake* mockCnakeToCheckIfGameOver = InitializeCnake();
	CopyCnake(cnake, mockCnakeToMinimize);
	CopyCnake(cnake, mockCnakeToCheckIfGameOver);

	//First Minimize X, then Y	
	MinimizeX(mockCnakeToMinimize, fruitXpos, computerMoves);
	MinimizeY(mockCnakeToMinimize, fruitYpos, computerMoves);

	//If the Cnake died, then minimize Y and then X
	bool IllegalMoves = CheckIfCnakeDies(mockCnakeToCheckIfGameOver, mockGamestate, computerMoves);
	
	//If minimizing X first fails, minimize Y first instead
	if (IllegalMoves) {
		CopyCnake(cnake, mockCnakeToMinimize); //Reset
		CopyCnake(cnake, mockCnakeToCheckIfGameOver); //Reset
		for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
			//All the rest moves are zero
			if (computerMoves[i]->xmove == 0 && computerMoves[i]->ymove == 0) {
				i = NUMOFCOMPUTERMOVES;
			}
			computerMoves[i]->xmove = 0;
			computerMoves[i]->ymove = 0;
		}
		MinimizeY(mockCnakeToMinimize, fruitYpos, computerMoves);
		MinimizeX(mockCnakeToMinimize, fruitXpos, computerMoves);
		IllegalMoves = CheckIfCnakeDies(mockCnakeToCheckIfGameOver, mockGamestate, computerMoves);
	}
	
	if (IllegalMoves) {
		for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
			computerMoves[i]->xmove = 0;
			computerMoves[i]->ymove = 0;
		}
		CalculateRandomPath(cnake, mockGamestate, computerMoves);
	}
	

	FreeGamestate(mockGamestate);
	FreeCnake(mockCnakeToMinimize);
	FreeCnake(mockCnakeToCheckIfGameOver);
	return;
}

void CalculateRandomPath(struct Cnake* cnake, struct Gamestate* mockGamestate, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]) {
	//Random number to determine Y or X
	int randChoose = 0;
	int randChooseStep = 0;
	int Xsteps[2] = {HEAD_W, -HEAD_W};
	int Ysteps[2] = {HEAD_H, -HEAD_H};
	int chosenStep = 0;
	bool IllegalMoves = false;
	struct Cnake* mockCnakeToCheckIfGameOver = InitializeCnake();

	//How many paths there are
	int flag = 0;
	for (int i=0; i<RANDOMRUNS; i++) {
		CopyCnake(cnake, mockCnakeToCheckIfGameOver);
		//For each path, the number of steps
		for (int j=0; j<RANDOMPATHLENGTH; j++) {
			randChoose = rand() % 2;
			randChooseStep = rand() % 2;
			//X is chosen
			if (randChoose == 0) {
				computerMoves[j]->ymove = 0;
				chosenStep = Xsteps[randChooseStep];
				//No step has been taken yet
				if (j == 0) {
					computerMoves[j]->xmove = chosenStep;
					continue;
				}
				//The last step was a zero
				if (computerMoves[j - 1]->xmove == 0) {
					computerMoves[j]->xmove = chosenStep;
					continue;
				}
				//Continue moving the way the Cnake is moving in the X direction
				computerMoves[j]->xmove = computerMoves[j-1]->xmove;
				
			} else {
				computerMoves[j]->xmove = 0;
				chosenStep = Ysteps[randChooseStep];
				//No step has been taken yet
				if (j == 0) {
					computerMoves[j]->ymove = chosenStep;
					continue;
				}
				//The last step was a zero
				if (computerMoves[j - 1]->ymove == 0) {
					computerMoves[j]->ymove = chosenStep;
					continue;
				}
				//Continue moving the way the Cnake is moving in the X direction
				computerMoves[j]->ymove = computerMoves[j-1]->ymove;
			}
		}
		//Check if the random path is valid
		IllegalMoves = CheckIfCnakeDies(mockCnakeToCheckIfGameOver, mockGamestate, computerMoves);
		if (IllegalMoves) {
			for (int k=0; k<RANDOMPATHLENGTH; k++) {
				computerMoves[k]->xmove = 0;
				computerMoves[k]->ymove = 0;
			}
		} else {
			FreeCnake(mockCnakeToCheckIfGameOver);
			break;
		}
		flag++;
	}
}

bool CheckIfCnakeDies(struct Cnake* cnake, struct Gamestate* mockGamestate, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]) {
	int xmove = 0;
	int ymove = 0;
	for (int i=0; i<NUMOFCOMPUTERMOVES; i++) {
		xmove = computerMoves[i]->xmove;
		ymove = computerMoves[i]->ymove;
		//I.e. the fruit is eaten since x and y are zero
		if (xmove == ymove) {
			return false;
		}
		CalculateCnakePosition(cnake, xmove, ymove);
		mockGamestate->gameover = CheckIfGameOver(cnake);
		if (mockGamestate->gameover) {
			return true;
		}
	}
	return false;
}

void MinimizeX(struct Cnake* cnake, int fruitXpos, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]) {
	int xmove = 0;
	//The x position is already minimal
	if (cnake->cnakebody->xpos == fruitXpos) {
		return;
	}
	for (int i=0; i<GRIDCELL_W; i++) {
		xmove = MoveToMinimizeX(cnake, fruitXpos);
		if (xmove == 0) {
			return;
		}
		if (computerMoves[i]->ymove == 0) {
			computerMoves[i]->xmove = xmove;
			CalculateCnakePosition(cnake, xmove, 0);
		}
	}
	return;
}

void MinimizeY(struct Cnake* cnake, int fruitYpos, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]) {
	int ymove = 0;
	//The y position is already minimized
	if (cnake->cnakebody->ypos == fruitYpos) {
		return;
	}
	for (int i=0; i<GRIDCELL_H; i++) {
		ymove = MoveToMinimizeY(cnake, fruitYpos);
		if (ymove == 0) {
			return;
		}
		if (computerMoves[i]->xmove == 0) {
			computerMoves[i]->ymove = ymove;
			CalculateCnakePosition(cnake, 0, ymove);
		}
	}
}

//Minimize the x position of the Cnake and the fruit
int MoveToMinimizeX(struct Cnake* cnake, int fruitXpos) {
	int xmove = 0;
	
	//The x position is already minimized
	if (fruitXpos == cnake->cnakebody->xpos) {
		return xmove;
	}

	//Calculate move to the left
	CalculateCnakePosition(cnake, -10, 0); //Go left once
	int fruitDifferenceL = abs(fruitXpos - cnake->cnakebody->xpos);

	CalculateCnakePosition(cnake, 20, 0); //Go right once
	int fruitDifferenceR = abs(fruitXpos - cnake->cnakebody->xpos);

	//If the difference going left is smaller and the game is not over, then go left
	if (fruitDifferenceL < fruitDifferenceR) {
		xmove = -10;
	} else if (fruitDifferenceL > fruitDifferenceR) {
		xmove = 10;
	}

	CalculateCnakePosition(cnake, -10, 0); //Neutral position
	return xmove;
}

//Minimize the y position of the Cnake and the fruit
int MoveToMinimizeY(struct Cnake* cnake, int fruitYpos) {
	int ymove = 0;
	
	//The y position is already minimized
	if (fruitYpos == cnake->cnakebody->ypos) {
		return ymove;
	}

	//Calculation for the Cnake moving up
	CalculateCnakePosition(cnake, 0, -10); //Go up once
	int fruitDifferenceU = abs(fruitYpos - cnake->cnakebody->ypos);

	CalculateCnakePosition(cnake, 0, 20); //Go down once
	int fruitDifferenceD = abs(fruitYpos - cnake->cnakebody->ypos);	

	//If the difference going up is smaller and the game is not over, then go up
	if (fruitDifferenceU < fruitDifferenceD) {
		ymove = -10;
	} else if (fruitDifferenceU > fruitDifferenceD) {
		ymove = 10;
	}

	CalculateCnakePosition(cnake, 0, -10); //Neutral position
	return ymove;
}

