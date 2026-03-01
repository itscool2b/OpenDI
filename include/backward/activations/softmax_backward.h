#ifndef SOFTMAX_BACKWARD_H
#define SOFTMAX_BACKWARD_H

#include "../../arena.h"

double *softmax_backward(Arena *arena, double *dout, double *output, int n);

#endif
