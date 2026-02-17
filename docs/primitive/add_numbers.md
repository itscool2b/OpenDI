# add_numbers

## Synopsis

```c
#include "primitive/add.h"

double add_numbers(int count, ...);
```

## Description

Adds a variable number of double-precision floating-point values.

## Parameters

- `count`: Number of values to add
- `...`: Variable list of double values

## Return Value

The sum of all input values as a `double`.

Returns `0.0` if `count` is 0.

## Example

```c
double result = add_numbers(3, 1.0, 2.0, 3.0);  // Returns 6.0
double result2 = add_numbers(0);                // Returns 0.0
```

## Notes

Returns `0.0` if `count` is 0.

## See Also

subtract_numbers(3), multiply_numbers(3), divide_numbers(3)
