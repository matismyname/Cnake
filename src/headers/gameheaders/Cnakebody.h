#ifndef _CNAKEBODY_H_
#define _CNAKEBODY_H_

#include "constants.h"

struct Cnakebody {
	int xpos;
	int ypos;
	struct Cnakebody* parentcnakebody;
	struct Cnakebody* childcnakebody;
};

#endif
