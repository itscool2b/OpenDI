# centralDifference

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.centralDifference(f, x, h)
```

## Description

Computes the central difference approximation of the first derivative of a function.

Uses the formula: `f'(x) ≈ (f(x + h) - f(x - h)) / (2h)`

This is more accurate than forward or backward difference for the same step size.

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `central_difference()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `x`: The point at which to evaluate the derivative
- `h`: Step size

## Return Value

The approximate derivative as a `number`.

## Example

```js
o.centralDifference(x => x * x, 3, 0.0001)    // ~6.0 (very accurate)
```

## Notes

Function pointers are cached per unique JS function reference.

Central difference has O(h^2) accuracy vs O(h) for forward/backward difference.

## See Also

forwarddiff(3), backwarddiff(3), secondDerivative(3), centralNth(3)
