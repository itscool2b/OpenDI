# normalize

## Synopsis

```c
#include "statistics/normalize.h"

double *normalize(Arena *arena, double *v, int n);
```

## Description

Computes the z-score normalization of a vector.

The normalization is defined as:
```
mean = (1/n) * sum(v[i])
std = sqrt((1/n) * sum((v[i] - mean)^2))
result[i] = (v[i] - mean) / std
```

After normalization, the result has approximately zero mean and unit standard deviation. This is essential for preprocessing data before feeding it into neural networks.

## Parameters

- `arena`: Arena allocator for memory
- `v`: Pointer to the input vector
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the normalized values.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double v[] = {1.0, 2.0, 3.0, 4.0, 5.0};
double *result = normalize(arena, v, 5);
// result has mean ~0 and std ~1

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

The standard deviation must be non-zero (i.e., not all values should be identical).

## See Also

softmax(3), arena_create(3)
