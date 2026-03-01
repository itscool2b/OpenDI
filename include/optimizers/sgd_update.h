#ifndef SGD_UPDATE_H
#define SGD_UPDATE_H

#include "../arena.h"

double *sgd_update(Arena *arena, double *weights, double *grads, double lr, int n);

#endif
