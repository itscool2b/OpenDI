# abs

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.abs(x)
```

## Description

Returns the absolute value of a number.

Wraps the C `absolute()` function directly.

## Parameters

- `x`: A number

## Return Value

The absolute value of `x` as a `number`.

## Example

```js
o.abs(-5)     // 5
o.abs(3.14)   // 3.14
o.abs(0)      // 0
```

## Notes

No arena allocation needed. Calls the WASM function directly.

## See Also

min(3), max(3), round(3)
