#include "constants.h"
#include "gridlogic.h"
#include "clog.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int RandomPointSnappedToGrid(int bound, int offset) {
	int randomNum = rand();
	int randomValue = randomNum % (bound - (offset - 1));
	int randomValueSnapped = SnapToGrid(randomValue, offset);
	return randomValueSnapped;
}

//This functions turns a number to the upper left point of a grid cell, whose length is defined by step
int SnapToGrid(int num, int step) {
	bool flag = true;
	int lowerbound = 0;
	int upperbound = step;
	while(flag) {
		if (lowerbound <= num && num < upperbound) {
			return lowerbound;
		}
		lowerbound = upperbound;
		upperbound += step;
		if (upperbound > SCREEN_W || upperbound > SCREEN_H) {
			Clog("There was an error snapping to the grid!", "ERROR");
			exit(EXIT_FAILURE);
		}
	}
}
