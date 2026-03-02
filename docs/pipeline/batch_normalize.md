# batch_normalize

## Synopsis

```c
#include "pipeline/batch_normalize.h"

double *batch_normalize(Arena *arena, double *features, int n_samples, int n_features);
```

## Description

Z-score normalizes each column of a feature matrix independently. Each column is transformed to have mean 0 and standard deviation 1.

For each column j:
```
mean_j = mean(features[:, j])
std_j  = std(features[:, j])
result[i, j] = (features[i, j] - mean_j) / std_j
```

## Parameters

- `arena`: Arena allocator for memory
- `features`: Pointer to the feature matrix (row-major, n_samples x n_features)
- `n_samples`: Number of rows (samples)
- `n_features`: Number of columns (features)

## Return Value

A pointer to memory in the arena containing the normalized feature matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(4096);

double features[] = {1.0, 10.0,
                     2.0, 20.0,
                     3.0, 30.0,
                     4.0, 40.0};
double *normed = batch_normalize(arena, features, 4, 2);
// Each column now has mean ~0 and std ~1

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Internally calls `normalize()` per column. Additional arena memory is used for temporary per-column allocations.

## See Also

normalize(3), dense_forward(3)
