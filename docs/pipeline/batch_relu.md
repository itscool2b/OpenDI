# batch_relu

## Synopsis

```c
#include "pipeline/batch_relu.h"

double *batch_relu(Arena *arena, double *input, int n);
```

## Description

Applies the ReLU activation function element-wise to an array of n values.

Each element is transformed as:
```
result[i] = max(0, input[i])
```

## Parameters

- `arena`: Arena allocator for memory
- `input`: Pointer to the input array
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the activated values.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double input[] = {-1.0, 0.0, 2.0, -3.0, 5.0};
double *result = batch_relu(arena, input, 5);
// result: {0.0, 0.0, 2.0, 0.0, 5.0}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Internally calls `relu()` on each element.

## See Also

relu(3), batch_sigmoid(3), batch_softmax(3)
