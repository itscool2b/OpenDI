# forwarddiff

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.forwarddiff(f, x, h)
```

## Description

Computes the forward difference approximation of the first derivative of a function.

Uses the formula: `f'(x) ≈ (f(x + h) - f(x)) / h`

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `forwarddiff()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `x`: The point at which to evaluate the derivative
- `h`: Step size

## Return Value

The approximate derivative as a `number`.

## Example

```js
o.forwarddiff(x => x * x, 3, 0.001)    // ~6.0
o.forwarddiff(Math.sin, 0, 0.0001)      // ~1.0
```

## Notes

Function pointers are cached per unique JS function reference. Passing the same function repeatedly does not leak WASM table slots.

For better accuracy, use `centralDifference()`.

## See Also

backwarddiff(3), centralDifference(3), secondDerivative(3), centralNth(3), rombergIntegrate(3)
