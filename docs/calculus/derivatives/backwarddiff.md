# backwarddiff

## Synopsis

```c
#include "calculus/backwarddiff.h"

double backwarddiff(double (*f)(double), double x, double h);
```

## Description

Computes the first derivative using the backward difference method.

**Formula:** f'(x) ≈ (f(x) - f(x - h)) / h

## Parameters

- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

## Return Value

The approximate derivative at point `x`.

Returns `NAN` if `h` is 0.

## Example

```c
double f(double x) { return x * x; }
double result = backwarddiff(f, 3.0, 0.0001);  // ≈ 6.0
```

## Notes

- First-order accurate (error proportional to h)
- Tends to underestimate the derivative

## See Also

forwarddiff(3), central_difference(3)
