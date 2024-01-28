#ifndef _AI_H_
#define _AI_H_

#include "Cnake.h"
#include "fruit.h"
#include "moves.h"

void MinimizeManhattanDistance(struct Cnake* cnake, struct Fruit* fruit, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]);
int MoveToMinimizeX(struct Cnake* cnake, int fruitXpos);
int MoveToMinimizeY(struct Cnake* cnake, int fruitYpos);
bool CheckIfCnakeDies(struct Cnake* cnake, struct Gamestate* mockGamestate, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]);
void CalculateRandomPath(struct Cnake* cnake, struct Gamestate* mockGamestate, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]);
void MinimizeX(struct Cnake* cnake, int fruitXpos, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]);
void MinimizeY(struct Cnake* cnake, int fruitYpos, struct Moves* computerMoves[NUMOFCOMPUTERMOVES]);

#endif
