# centralNth

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.centralNth(f, x, h, n)
```

## Description

Computes the nth derivative of a function using recursive central differences.

For n=0 returns f(x), for n=1 returns the first derivative, for n=2 the second, and so on.

The JavaScript function `f` is compiled to a WASM function pointer internally and cached for reuse.

Wraps the C `centralnth()` function.

## Parameters

- `f`: A JavaScript function `(x: number) => number`
- `x`: The point at which to evaluate the derivative
- `h`: Step size
- `n`: Order of the derivative (0, 1, 2, ...)

## Return Value

The approximate nth derivative as a `number`.

## Example

```js
o.centralNth(x => x * x, 3, 0.001, 1)    // ~6.0 (first derivative)
o.centralNth(x => x * x, 3, 0.001, 2)    // ~2.0 (second derivative)
o.centralNth(x => x * x, 3, 0.001, 3)    // ~0.0 (third derivative)
```

## Notes

Function pointers are cached per unique JS function reference.

Higher-order derivatives require smaller step sizes for accuracy but may accumulate floating-point error.

## See Also

forwarddiff(3), centralDifference(3), secondDerivative(3)
