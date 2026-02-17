# roundval

## Synopsis

```c
#include "primitive/rounding.h"

double roundval(const char* decision, double x);
```

## Description

Rounds a floating-point number using the specified rounding mode.

## Parameters

- `decision`: Rounding mode string ("floor" or "ceil")
- `x`: Value to round

## Return Value

The rounded value as a `double`:
- `"floor"`: Largest integer less than or equal to `x`
- `"ceil"`: Smallest integer greater than or equal to `x`
- Any other string: Returns `x` unchanged

## Example

```c
double floor_result = roundval("floor", 3.7);   // Returns 3.0
double ceil_result = roundval("ceil", 3.2);     // Returns 4.0
double neg_floor = roundval("floor", -3.7);     // Returns -4.0
double invalid = roundval("round", 3.5);        // Returns 3.5 (unchanged)
```
