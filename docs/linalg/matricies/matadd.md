# matadd

## Synopsis

```c
#include "linalg/matricies/matadd.h"

double *matadd(Arena *arena, double *a, double *b, int m, int n);
```

## Description

Performs element-wise addition of two matrices.

Given two m×n matrices `a` and `b`, computes:
- `result[i][j] = a[i][j] + b[i][j]`

## Parameters

- `arena`: Arena allocator for memory
- `a`: Pointer to first matrix (m×n, row-major)
- `b`: Pointer to second matrix (m×n, row-major)
- `m`: Number of rows
- `n`: Number of columns

## Return Value

A pointer to memory in the arena containing the m×n sum matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

// 2x2 matrices
double a[] = {1.0, 2.0, 3.0, 4.0};  // [1 2; 3 4]
double b[] = {5.0, 6.0, 7.0, 8.0};  // [5 6; 7 8]
double *result = matadd(arena, a, b, 2, 2);
// result contains: {6, 8, 10, 12} = [6 8; 10 12]

arena_destroy(arena);
```

## Notes

Matrices are stored in row-major order (1D array).

Both input matrices must have dimensions m×n.

## See Also

matmul(3), matscale(3), mattranspose(3), arena_create(3)
