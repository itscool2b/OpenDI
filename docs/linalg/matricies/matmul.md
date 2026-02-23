# matmul

## Synopsis

```c
#include "linalg/matricies/matmul.h"

double *matmul(Arena *arena, double *a, double *b, int m, int n, int p);
```

## Description

Performs matrix multiplication.

Given an m×n matrix `a` and an n×p matrix `b`, computes an m×p result:
- `result[i][j] = sum(a[i][k] * b[k][j])` for k = 0 to n-1

## Parameters

- `arena`: Arena allocator for memory
- `a`: Pointer to first matrix (m×n, row-major)
- `b`: Pointer to second matrix (n×p, row-major)
- `m`: Number of rows in matrix a
- `n`: Number of columns in matrix a (must equal rows in b)
- `p`: Number of columns in matrix b

## Return Value

A pointer to memory in the arena containing the m×p product matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

// 2x2 * 2x2 = 2x2
double a[] = {1.0, 2.0, 3.0, 4.0};  // [1 2; 3 4]
double b[] = {5.0, 6.0, 7.0, 8.0};  // [5 6; 7 8]
double *result = matmul(arena, a, b, 2, 2, 2);
// result: {19, 22, 43, 50} = [19 22; 43 50]

arena_destroy(arena);
```

## Notes

The number of columns in the first matrix must equal the number of rows in the second matrix (n).

Matrices are stored in row-major order.

Time complexity: O(m×n×p)

## See Also

matadd(3), matscale(3), mattranspose(3), arena_create(3)
