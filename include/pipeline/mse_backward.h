#ifndef MSE_BACKWARD_H
#define MSE_BACKWARD_H

#include "../arena.h"

double *mse_backward(Arena *arena, double *pred, double *targets, int n);

#endif
