
#include <malloc.h>
#include <stdlib.h>
#include "nbody.h"



void free_memory(body* p)
{
	_mm_free(p);
}

void randomizeBodies(body* data, int n) {
	for (int i = 0; i < n; i++) {
		data.m[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data.x[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data.y[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data.z[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data.vx[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data.vy[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data.vz[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
	}
}
