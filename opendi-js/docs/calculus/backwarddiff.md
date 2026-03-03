# backwarddiff

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.backwarddiff(f, x, h)
```

## Description

Computes the backward difference approximation of the first derivative of a function.

Uses the formula: `f'(x) ≈ (f(x) - f(x - h)) / h`

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `backwarddiff()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `x`: The point at which to evaluate the derivative
- `h`: Step size

## Return Value

The approximate derivative as a `number`.

## Example

```js
o.backwarddiff(x => x * x, 3, 0.001)    // ~6.0
```

## Notes

Function pointers are cached per unique JS function reference.

For better accuracy, use `centralDifference()`.

## See Also

forwarddiff(3), centralDifference(3), secondDerivative(3), centralNth(3)
