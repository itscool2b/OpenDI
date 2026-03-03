# min

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.min(...numbers)
```

## Description

Returns the minimum value among all provided numbers.

Wraps the C `min()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: One or more numbers (or a single array of numbers)

## Return Value

The minimum value as a `number`.

## Example

```js
o.min(3, 1, 2)    // 1
o.min(10, 20)     // 10
```

## Notes

Arguments are flattened, so both `o.min(3, 1, 2)` and `o.min([3, 1, 2])` work identically.

## See Also

max(3), abs(3)
