# subtract

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.subtract(...numbers)
```

## Description

Computes sequential subtraction across all provided numbers. The first value is the starting value, and each subsequent value is subtracted from it.

Wraps the C `subtract_numbers()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: Two or more numbers (or a single array of numbers)

## Return Value

The result of sequential subtraction as a `number`.

## Example

```js
o.subtract(10, 3)       // 7
o.subtract(100, 20, 5)  // 75
```

## Notes

Arguments are flattened, so both `o.subtract(10, 3)` and `o.subtract([10, 3])` work identically.

## See Also

add(3), multiply(3), divide(3)
