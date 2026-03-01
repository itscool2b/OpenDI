#ifndef RELU_BACKWARD_H
#define RELU_BACKWARD_H

#include "../../arena.h"

double *relu_backward(Arena *arena, double *dout, double *input, int n);

#endif
