#ifndef CROSS_ENTROPY_BACKWARD_H
#define CROSS_ENTROPY_BACKWARD_H

#include "../arena.h"

double *cross_entropy_backward(Arena *arena, double *pred, double *targets, int n_samples, int n_classes);

#endif
