#ifndef _CNAKE_H_
#define _CNAKE_H_

#include "constants.h"

struct Cnake {
	int colorR;
	int colorB;
	int colorG;
	int bodysum;
	struct Cnakebody* cnakebody;
};

#endif
