# rombergIntegrate

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.rombergIntegrate(f, a, b, eps, kMax)
```

## Description

Computes the definite integral of a function over [a, b] using Romberg's method.

Romberg integration applies Richardson extrapolation to the trapezoidal rule, achieving high accuracy with fewer function evaluations.

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `romberg_integrate()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `a`: Lower bound of integration
- `b`: Upper bound of integration
- `eps`: Desired accuracy (tolerance)
- `kMax`: Maximum number of Romberg iterations

## Return Value

The approximate definite integral as a `number`.

## Example

```js
o.rombergIntegrate(x => x * x, 0, 1, 1e-8, 10)    // ~0.333333
o.rombergIntegrate(Math.sin, 0, Math.PI, 1e-8, 10) // ~2.0
```

## Notes

Function pointers are cached per unique JS function reference.

Smaller `eps` and larger `kMax` improve accuracy at the cost of more computation.

## See Also

forwarddiff(3), centralDifference(3), secondDerivative(3)
