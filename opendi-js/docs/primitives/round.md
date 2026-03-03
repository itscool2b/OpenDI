# round

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.round(mode, x)
```

## Description

Rounds a number according to the specified mode.

Wraps the C `roundval()` function. The mode string is copied to the WASM heap for the C function to parse.

## Parameters

- `mode`: Rounding mode string — `'floor'`, `'ceil'`, or `'round'`
- `x`: The number to round

## Return Value

The rounded value as a `number`.

## Example

```js
o.round('floor', 3.7)    // 3
o.round('ceil', 3.2)     // 4
o.round('round', 3.5)    // 4
```

## Notes

A temporary arena is created to hold the mode string in WASM memory.

## See Also

abs(3), min(3), max(3)
