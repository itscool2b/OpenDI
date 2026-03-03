# denseForward (Session API)

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

const session = o.createSession(65536)
session.denseForward(inputPtr, weightsPtr, m, n, p, activation)
```

## Description

Performs a dense (fully connected) layer forward pass: matrix multiplication followed by an activation function.

Computes `activation(input @ weights)` where input is m x n and weights is n x p, producing an m x p output.

This is a Session API function that works with WASM pointers. Use `session.writeArray()` to write data to the arena first.

Wraps the C `dense_forward()` function via the glue layer.

## Parameters

- `inputPtr`: WASM pointer to input matrix (m x n)
- `weightsPtr`: WASM pointer to weight matrix (n x p)
- `m`: Number of samples (rows in input)
- `n`: Number of input features (columns in input)
- `p`: Number of output features (columns in weights)
- `activation`: Activation type — `'none'`, `'relu'`, `'sigmoid'`, or `'softmax'`

## Return Value

An object with:
- `outputPtr`: WASM pointer to the m x p output matrix
- `cachePtr`: WASM pointer to cached values needed for backward pass

## Example

```js
const session = o.createSession(65536)
const inputPtr = session.writeArray(features)
const fwd = session.denseForward(inputPtr, weights._ptr, 4, 8, 1, 'sigmoid')

// fwd.outputPtr — predictions
// fwd.cachePtr — cached for backward pass
```

## Notes

Cache semantics depend on the activation:
- `'relu'`: cache = pre-activation z
- `'sigmoid'`: cache = post-activation output
- `'softmax'`: cache = null (use `crossEntropyBackward()` for combined gradient)
- `'none'`: cache = null

For softmax + cross-entropy, use `'softmax'` here and `'none'` in `denseBackward()` with `crossEntropyBackward()`.

## See Also

denseBackward(3), initWeights(3), sgdUpdate(3), mseLoss(3), createSession(3)
