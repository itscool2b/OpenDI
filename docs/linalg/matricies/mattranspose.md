# mattranspose

## Synopsis

```c
#include "linalg/matricies/mattranspose.h"

double *mattranspose(Arena *arena, double *a, int m, int n);
```

## Description

Transposes a matrix (swaps rows and columns).

Given an m×n matrix `a`, produces an n×m matrix where:
- `result[j][i] = a[i][j]`

## Parameters

- `arena`: Arena allocator for memory
- `a`: Pointer to input matrix (m×n, row-major)
- `m`: Number of rows in input matrix
- `n`: Number of columns in input matrix

## Return Value

A pointer to memory in the arena containing the transposed n×m matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

// 2x3 matrix
double a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};  // [1 2 3; 4 5 6]
double *result = mattranspose(arena, a, 2, 3);
// result: {1, 4, 2, 5, 3, 6} = [1 4; 2 5; 3 6] (3x2)

arena_destroy(arena);
```

## Notes

Matrices are stored in row-major order (1D array).

If the input is m×n, the output is n×m.

For a symmetric matrix, the transpose equals the original.

## See Also

matadd(3), matmul(3), matscale(3), arena_create(3)
