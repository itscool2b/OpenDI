# exponents

## Synopsis

```c
#include "primitive/exponents.h"

double exponents(float value, float exponent);
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
double result1 = exponents(2.0f, 3.0f);    // Returns 8.0
double result2 = exponents(4.0f, 0.5f);    // Returns 2.0 (sqrt)
double result3 = exponents(2.0f, -2.0f);   // Returns 0.25
double result4 = exponents(0.0f, 0.0f);    // Returns 1.0
```

## Notes

If both `value` and `exponent` are 0, returns 1.0 (mathematical convention).

## See Also

No related functions.
