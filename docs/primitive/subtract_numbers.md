# subtract_numbers

## Synopsis

```c
#include "primitive/subtract.h"

double subtract_numbers(int count, ...);
```

## Description

Subtracts subsequent values from the first value.

## Parameters

- `count`: Number of values
- `...`: Variable list of double values. The first value is the minuend, all subsequent values are subtracted from it.

## Return Value

The result of successive subtraction as a `double`.

## Example

```c
double result = subtract_numbers(3, 10.0, 3.0, 2.0);  // Returns 5.0
```

## Notes

The function processes arguments left to right: `((first - second) - third) ...`

## See Also

add_numbers(3)
