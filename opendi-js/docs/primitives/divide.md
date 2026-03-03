# divide

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.divide(...numbers)
```

## Description

Computes sequential division across all provided numbers. The first value is the dividend, and each subsequent value divides the result.

Wraps the C `divide_numbers()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: Two or more numbers (or a single array of numbers)

## Return Value

The result of sequential division as a `number`.

## Example

```js
o.divide(100, 5, 2)    // 10
o.divide(50, 10)       // 5
```

## Notes

Arguments are flattened, so both `o.divide(100, 5)` and `o.divide([100, 5])` work identically.

Division by zero behavior follows C semantics (returns infinity or NaN).

## See Also

add(3), subtract(3), multiply(3)
