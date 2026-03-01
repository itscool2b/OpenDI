#ifndef MATMUL_BACKWARD_A_H
#define MATMUL_BACKWARD_A_H

#include "../../arena.h"

double *matmul_backward_a(Arena *arena, double *dout, double *b, int m, int n, int p);

#endif
