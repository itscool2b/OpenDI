#ifndef BATCH_NORMALIZE_H
#define BATCH_NORMALIZE_H

#include "../arena.h"

double *batch_normalize(Arena *arena, double *features, int n_samples, int n_features);

#endif
