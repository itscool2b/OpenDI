# matmul_backward_a

## Synopsis

```c
#include "backward/linalg/matmul_backward_a.h"

double *matmul_backward_a(Arena *arena, double *dout, double *b, int m, int n, int p);
```

## Description

Computes the gradient of the loss with respect to the first matrix in a matrix multiplication.

Given the forward pass `C = A @ B` where A is m×n and B is n×p, the gradient is:
```
dL/dA = dout @ B^T
```

Where dout is the m×p upstream gradient. The result is an m×n matrix matching the shape of A.

## Parameters

- `arena`: Arena allocator for memory
- `dout`: Pointer to the upstream gradient (m×p matrix)
- `b`: Pointer to the second matrix from the forward pass (n×p matrix)
- `m`: Number of rows in A and dout
- `n`: Number of columns in A (rows in B)
- `p`: Number of columns in B and dout

## Return Value

A pointer to memory in the arena containing the m×n gradient matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double dout[] = {1.0, 0.0, 0.0, 1.0};  // 2x2
double b[] = {1.0, 2.0, 3.0, 4.0};      // 2x2
double *grad = matmul_backward_a(arena, dout, b, 2, 2, 2);
// grad = dout @ B^T = {1, 3, 2, 4}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Internally calls `mattranspose` and `matmul`.

## See Also

matmul_backward_b(3), matmul(3), mattranspose(3)
