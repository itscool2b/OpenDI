# vecadd

## Synopsis

```c
#include "linalg/vectors/vecadd.h"

double *vecadd(Arena *arena, const double *vec1, const double *vec2, size_t length);
```

## Description

Performs element-wise addition of two vectors.

Given two vectors `vec1` and `vec2` of the same length, computes:
- `result[i] = vec1[i] + vec2[i]` for all `i` from `0` to `length-1`

## Parameters

- `arena`: Arena allocator for memory
- `vec1`: Pointer to the first input vector
- `vec2`: Pointer to the second input vector
- `length`: Number of elements in each vector

## Return Value

A pointer to memory in the arena containing the element-wise sum.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double v1[] = {1.0, 2.0, 3.0};
double v2[] = {4.0, 5.0, 6.0};
double *result = vecadd(arena, v1, v2, 3);
// result now contains: {5.0, 7.0, 9.0}

arena_destroy(arena);  // Frees everything at once
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Both input vectors must have at least `length` elements.

## See Also

vecscale(3), vecdot(3), vecnorm(3), arena_create(3), arena_destroy(3)
