#ifndef MATMUL_BACKWARD_B_H
#define MATMUL_BACKWARD_B_H

#include "../../arena.h"

double *matmul_backward_b(Arena *arena, double *a, double *dout, int m, int n, int p);

#endif
