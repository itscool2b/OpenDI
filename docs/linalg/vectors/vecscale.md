# vecscale

## Synopsis

```c
#include "linalg/vectors/vecscale.h"

double *vecscale(const double *arr, double scalar, size_t length);
```

## Description

Scales (multiplies) a vector by a scalar value.

Multiplies each element of the input vector by the given scalar:
- `result[i] = arr[i] × scalar` for all `i` from `0` to `length-1`

## Parameters

- `arr`: Pointer to the input vector
- `scalar`: The scaling factor
- `length`: Number of elements in the vector

## Return Value

A pointer to a newly allocated array containing the scaled vector.

Returns `NULL` if memory allocation fails.

## Example

```c
// Basic scaling
double v[] = {1.0, 2.0, 3.0};
double *result = vecscale(v, 2.0, 3);
// result now contains: {2.0, 4.0, 6.0}
free(result);  // Remember to free the allocated memory

// Scale by 0 (zero vector)
double *zero = vecscale(v, 0.0, 3);
// zero contains: {0.0, 0.0, 0.0}
free(zero);

// Negation (scale by -1)
double *neg = vecscale(v, -1.0, 3);
// neg contains: {-1.0, -2.0, -3.0}
free(neg);

// Fractional scaling
double *half = vecscale(v, 0.5, 3);
// half contains: {0.5, 1.0, 1.5}
free(half);
```

## Notes

**Memory Management:** This function dynamically allocates memory for the result vector using `malloc()`. The caller is responsible for freeing this memory using `free()` when it is no longer needed to prevent memory leaks.

Special scalar values:
- `scalar = 1`: Returns a copy of the original vector (identity)
- `scalar = 0`: Returns a zero vector
- `scalar = -1`: Returns the negation of the vector

Properties:
- Associative: `a × (b × v) = (a × b) × v`
- Distributive over vector addition: `s × (v₁ + v₂) = s × v₁ + s × v₂`

## See Also

vecadd(3), vecnorm(3)
