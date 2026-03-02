# batch_softmax

## Synopsis

```c
#include "pipeline/batch_softmax.h"

double *batch_softmax(Arena *arena, double *input, int rows, int cols);
```

## Description

Applies softmax per-row to a 2D matrix of logits. Allocates one contiguous block and computes softmax inline with max-subtraction for numerical stability.

For each row i:
```
max = max(input[i * cols .. i * cols + cols - 1])
result[i * cols + j] = exp(input[i * cols + j] - max) / sum(exp(input[i * cols + ..] - max))
```

## Parameters

- `arena`: Arena allocator for memory
- `input`: Pointer to the input matrix (row-major, rows x cols)
- `rows`: Number of rows (samples)
- `cols`: Number of columns (classes)

## Return Value

A pointer to memory in the arena containing the softmax probabilities. Each row sums to 1.0.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double logits[] = {1.0, 2.0, 3.0,
                   -1.0, 0.0, 1.0};
double *probs = batch_softmax(arena, logits, 2, 3);
// Each row sums to 1.0

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Unlike calling `softmax()` per-row, this function writes into a single contiguous allocation, avoiding reliance on arena contiguity.

## See Also

softmax(3), batch_relu(3), batch_sigmoid(3)
