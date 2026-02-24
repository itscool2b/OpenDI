# exponents

## Synopsis

```c
#include "primitive/exponents.h"

double exponents(double value, double exponent);
```

## Description

Computes the power of a number using `pow()` from libm.

## Parameters

- `value`: The base value
- `exponent`: The exponent

## Return Value

`value` raised to the power of `exponent` as a `double`.

## Example

```c
double result1 = exponents(2.0, 3.0);    // Returns 8.0
double result2 = exponents(4.0, 0.5);    // Returns 2.0 (sqrt)
double result3 = exponents(2.0, -2.0);   // Returns 0.25
double result4 = exponents(0.0, 0.0);    // Returns 1.0
```

## Notes

If both `value` and `exponent` are 0, returns 1.0 (mathematical convention).

## See Also

No related functions.
