# vecadd

## Synopsis

```c
#include "linalg/vectors/vecadd.h"

double *vecadd(const double *vec1, const double *vec2, size_t length);
```

## Description

Performs element-wise addition of two vectors.

Given two vectors `vec1` and `vec2` of the same length, computes:
- `result[i] = vec1[i] + vec2[i]` for all `i` from `0` to `length-1`

## Parameters

- `vec1`: Pointer to the first input vector
- `vec2`: Pointer to the second input vector
- `length`: Number of elements in each vector

## Return Value

A pointer to a newly allocated array containing the element-wise sum.

Returns `NULL` if memory allocation fails.

## Example

```c
double v1[] = {1.0, 2.0, 3.0};
double v2[] = {4.0, 5.0, 6.0};
double *result = vecadd(v1, v2, 3);
// result now contains: {5.0, 7.0, 9.0}
free(result);  // Remember to free the allocated memory
```

## Notes

**Memory Management:** This function dynamically allocates memory for the result vector using `malloc()`. The caller is responsible for freeing this memory using `free()` when it is no longer needed to prevent memory leaks.

Both input vectors must have at least `length` elements. Passing vectors with fewer elements results in undefined behavior.

## See Also

vecscale(3), vecdot(3), vecnorm(3)
