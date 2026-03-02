# batch_sigmoid

## Synopsis

```c
#include "pipeline/batch_sigmoid.h"

double *batch_sigmoid(Arena *arena, double *input, int n);
```

## Description

Applies the sigmoid activation function element-wise to an array of n values.

Each element is transformed as:
```
result[i] = 1 / (1 + exp(-input[i]))
```

## Parameters

- `arena`: Arena allocator for memory
- `input`: Pointer to the input array
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the activated values. All values are in the range (0, 1).

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double input[] = {-2.0, 0.0, 2.0};
double *result = batch_sigmoid(arena, input, 3);
// result: {0.119, 0.5, 0.881}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Internally calls `sigmoid()` on each element.

## See Also

sigmoid(3), batch_relu(3), batch_softmax(3)
