# initWeights

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.initWeights(n, mean, std)
```

## Description

Initializes a weight vector with random values drawn from a normal distribution.

The weights are allocated with `malloc` (not arena), so they survive `session.clear()` calls. The returned object tracks the WASM pointer and provides a `free()` method.

Call `randomSeed()` before this for reproducible initialization.

Wraps the C `init_weights()` function.

## Parameters

- `n`: Number of weights
- `mean`: Mean of the normal distribution (typically 0.0)
- `std`: Standard deviation of the normal distribution (typically 0.1)

## Return Value

A `Weights` object with:
- `data`: `Float64Array` snapshot of the initial weights
- `_ptr`: WASM pointer to the weights (for session API)
- `length`: Number of weights
- `free()`: Frees the malloc'd memory

## Example

```js
o.randomSeed(42)
const w = o.initWeights(10, 0.0, 0.1)
console.log(w.data)      // Float64Array of 10 values
console.log(w._ptr)      // WASM pointer (number > 0)

// Use in session API
const session = o.createSession(65536)
const fwd = session.denseForward(inputPtr, w._ptr, m, n, p, 'sigmoid')

// When done
w.free()
```

## Notes

You must call `w.free()` when done to avoid memory leaks.

The `data` property is a snapshot taken at creation time. If the weights are updated in-place during training (via `session.copyToPtr()`), `data` will not reflect those changes. Read updated values with `session.readArray(w._ptr, w.length)`.

## See Also

randomSeed(3), denseForward(3), denseBackward(3), sgdUpdate(3)
