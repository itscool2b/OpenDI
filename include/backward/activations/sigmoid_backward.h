#ifndef SIGMOID_BACKWARD_H
#define SIGMOID_BACKWARD_H

#include "../../arena.h"

double *sigmoid_backward(Arena *arena, double *dout, double *output, int n);

#endif
