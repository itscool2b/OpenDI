# sgdUpdate

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.sgdUpdate(weights, grads, lr)
```

## Description

Updates weights using Stochastic Gradient Descent.

Computes `weights[i] = weights[i] - lr * grads[i]` for each element.

Wraps the C `sgd_update()` function.

## Parameters

- `weights`: Current weight values (array of numbers)
- `grads`: Gradient values (array of numbers, same length)
- `lr`: Learning rate

## Return Value

A `Float64Array` containing the updated weights.

## Example

```js
o.sgdUpdate([1, 2, 3], [0.1, 0.2, 0.3], 1.0)
// Float64Array [0.9, 1.8, 2.7]
```

## Notes

Memory is automatically managed via a temporary arena.

For training loops, use `session.sgdUpdate()` with WASM pointers for better performance.

## See Also

denseForward(3), denseBackward(3), initWeights(3)
