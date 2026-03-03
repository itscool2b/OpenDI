# secondDerivative

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.secondDerivative(f, x, h)
```

## Description

Computes the second derivative of a function using finite differences.

Uses the formula: `f''(x) ≈ (f(x + h) - 2*f(x) + f(x - h)) / h^2`

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `secondderivative()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `x`: The point at which to evaluate the second derivative
- `h`: Step size

## Return Value

The approximate second derivative as a `number`.

## Example

```js
o.secondDerivative(x => x * x, 3, 0.001)    // ~2.0
o.secondDerivative(x => x * x * x, 2, 0.001)  // ~12.0
```

## Notes

Function pointers are cached per unique JS function reference.

For higher-order derivatives, use `centralNth()`.

## See Also

forwarddiff(3), centralDifference(3), centralNth(3)
