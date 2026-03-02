#ifndef DENSE_BACKWARD_H
#define DENSE_BACKWARD_H

#include "../arena.h"
#include "pipeline_types.h"

LayerGrad dense_backward(Arena *arena, double *dout, double *input, double *weights, double *cache, int m, int n, int p, ActivationType act);

#endif
