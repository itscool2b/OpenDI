# forwarddiff

## Synopsis

```c
#include "calculus/forwarddiff.h"

double forwarddiff(double (*f)(double), double x, double h);
```

## Description

Computes the first derivative using the forward difference method.

**Formula:** f'(x) ≈ (f(x + h) - f(x)) / h

## Parameters

- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

## Return Value

The approximate derivative at point `x`.

Returns `0.0` if `h` is 0.

## Error Characteristics

- First-order accurate (error proportional to h)
- Tends to overestimate the derivative

## Example

```c
double f(double x) { return x * x; }
double result = forwarddiff(f, 3.0, 0.0001);  // ≈ 6.0
```

## See Also

backwarddiff(3), central_difference(3)
