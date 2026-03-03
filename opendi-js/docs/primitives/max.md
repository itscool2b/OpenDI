# max

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.max(...numbers)
```

## Description

Returns the maximum value among all provided numbers.

Wraps the C `max()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: One or more numbers (or a single array of numbers)

## Return Value

The maximum value as a `number`.

## Example

```js
o.max(3, 1, 2)    // 3
o.max(10, 20)     // 20
```

## Notes

Arguments are flattened, so both `o.max(3, 1, 2)` and `o.max([3, 1, 2])` work identically.

## See Also

min(3), abs(3)
