#ifndef DENSE_FORWARD_H
#define DENSE_FORWARD_H

#include "../arena.h"
#include "pipeline_types.h"

double *dense_forward(Arena *arena, double *input, double *weights, int m, int n, int p, ActivationType act, double **cache);

#endif
