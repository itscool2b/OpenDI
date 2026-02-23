# matscale

## Synopsis

```c
#include "linalg/matricies/matscale.h"

double *matscale(Arena *arena, double *a, double s, int m, int n);
```

## Description

Scales (multiplies) a matrix by a scalar value.

Multiplies each element of the matrix by scalar `s`:
- `result[i][j] = a[i][j] × s`

## Parameters

- `arena`: Arena allocator for memory
- `a`: Pointer to input matrix (m×n, row-major)
- `s`: The scaling factor
- `m`: Number of rows
- `n`: Number of columns

## Return Value

A pointer to memory in the arena containing the scaled m×n matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

// 2x2 matrix
double a[] = {1.0, 2.0, 3.0, 4.0};  // [1 2; 3 4]
double *result = matscale(arena, a, 2.0, 2, 2);
// result: {2, 4, 6, 8} = [2 4; 6 8]

arena_destroy(arena);
```

## Notes

Matrices are stored in row-major order (1D array).

Special cases:
- `s = 1`: Returns a copy of the original matrix
- `s = 0`: Returns a zero matrix
- `s = -1`: Returns the negation of the matrix

## See Also

matadd(3), matmul(3), mattranspose(3), arena_create(3)
