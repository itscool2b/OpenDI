# denseBackward (Session API)

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

const session = o.createSession(65536)
session.denseBackward(doutPtr, inputPtr, weightsPtr, cachePtr, m, n, p, activation)
```

## Description

Performs the backward pass of a dense layer, computing gradients with respect to weights and input.

Applies the activation backward function, then computes `dWeights = input^T @ dActivated` and `dInput = dActivated @ weights^T`.

This is a Session API function that works with WASM pointers.

Wraps the C `dense_backward()` function via the glue layer.

## Parameters

- `doutPtr`: WASM pointer to upstream gradient (m x p)
- `inputPtr`: WASM pointer to original input (m x n)
- `weightsPtr`: WASM pointer to weight matrix (n x p)
- `cachePtr`: WASM pointer to cache from `denseForward()` (or 0 for none/softmax)
- `m`: Number of samples
- `n`: Number of input features
- `p`: Number of output features
- `activation`: Activation type — `'none'`, `'relu'`, `'sigmoid'`, or `'softmax'`

## Return Value

An object with:
- `dWeightsPtr`: WASM pointer to weight gradients (n x p)
- `dInputPtr`: WASM pointer to input gradients (m x n)

## Example

```js
const dLoss = session.mseBackward(fwd.outputPtr, targPtr, nSamples)
const grad = session.denseBackward(
	dLoss, inputPtr, weights._ptr, fwd.cachePtr,
	nSamples, nFeatures, 1, 'sigmoid'
)

const newW = session.sgdUpdate(weights._ptr, grad.dWeightsPtr, 0.5, nFeatures)
```

## Notes

For softmax + cross-entropy, use `'none'` here with the gradient from `crossEntropyBackward()`.

## See Also

denseForward(3), sgdUpdate(3), mseBackward(3), crossEntropyBackward(3), createSession(3)
