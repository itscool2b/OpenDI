# veccross

## Synopsis

```c
#include "linalg/vectors/veccross.h"

double *veccross(const double *vec1, const double *vec2);
```

## Description

Computes the cross product of two 3-dimensional vectors.

The cross product produces a vector that is perpendicular to both input vectors. For vectors `a = (a₁, a₂, a₃)` and `b = (b₁, b₂, b₃)`:
- `result[0] = a₂b₃ - a₃b₂`
- `result[1] = a₃b₁ - a₁b₃`
- `result[2] = a₁b₂ - a₂b₁`

## Parameters

- `vec1`: Pointer to the first 3D vector
- `vec2`: Pointer to the second 3D vector

## Return Value

A pointer to a newly allocated 3-element array containing the cross product.

Returns `NULL` if memory allocation fails.

## Example

```c
// Standard basis vectors
double i[] = {1.0, 0.0, 0.0};  // x-axis
double j[] = {0.0, 1.0, 0.0};  // y-axis
double *k = veccross(i, j);    // Returns {0.0, 0.0, 1.0} (z-axis)
free(k);  // Remember to free the allocated memory

// General case
double a[] = {1.0, 2.0, 3.0};
double b[] = {4.0, 5.0, 6.0};
double *result = veccross(a, b);  // Returns {-3.0, 6.0, -3.0}
free(result);
```

## Notes

**Memory Management:** This function dynamically allocates memory for the result vector using `malloc()`. The caller is responsible for freeing this memory using `free()` when it is no longer needed to prevent memory leaks.

This function only works with 3-dimensional vectors. Both input vectors must have exactly 3 elements.

Properties of the cross product:
- Anti-commutative: `a × b = -(b × a)`
- Self-cross is zero: `a × a = 0`
- Perpendicular to both inputs

## See Also

vecdot(3), vecnorm(3)
