#ifndef VECSCALE_H
#define VECSCALE_H

#include <stddef.h>
#include "../../arena.h"

double *vecscale(Arena *arena, const double *arr, double scalar, size_t length);

#endif
