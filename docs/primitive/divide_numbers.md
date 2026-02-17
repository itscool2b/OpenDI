# divide_numbers

## Synopsis

```c
#include "primitive/divide.h"

double divide_numbers(int count, ...);
```

## Description

Divides the first value by all subsequent values in sequence.

## Parameters

- `count`: Number of values
- `...`: Variable list of double values

## Return Value

The result of successive division as a `double`.

Returns `0.0` if:
- `count` is 0
- Any divisor is 0.0 (also prints error message to stdout)

## Example

```c
double result = divide_numbers(3, 24.0, 4.0, 2.0);  // Returns 3.0
```

## Notes

Division by zero is caught and returns 0.0 with an error message.

## See Also

multiply_numbers(3)
