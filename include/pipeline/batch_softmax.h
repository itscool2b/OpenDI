#ifndef BATCH_SOFTMAX_H
#define BATCH_SOFTMAX_H

#include "../arena.h"

double *batch_softmax(Arena *arena, double *input, int rows, int cols);

#endif
