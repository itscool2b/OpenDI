# createSession

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

const session = o.createSession(arenaBytes)
```

## Description

Creates a Session for pointer-level control over WASM memory. Sessions use an arena allocator: allocations are fast (pointer bump), and `clear()` resets all allocations at once.

Sessions are designed for training loops where per-call arena creation would be wasteful. Write data once, perform multiple operations, clear between epochs, and destroy when done.

## Parameters

- `arenaBytes`: Size of the arena in bytes (default: 65536)

## Return Value

A `Session` object with:

**Memory management:**
- `writeArray(arr)` — Write a JS array to the arena, returns WASM pointer
- `writeI32Array(arr)` — Write a JS int array to the arena, returns WASM pointer
- `readArray(ptr, n)` — Read n doubles from a WASM pointer, returns `Float64Array`
- `copyToPtr(destPtr, srcArray)` — Write a JS array to an existing WASM pointer
- `clear()` — Reset the arena (reuse memory)
- `destroy()` — Free the arena

**Math operations (all take/return WASM pointers):**
- `vecadd`, `vecscale`, `matmul`, `matadd`, `matscale`, `mattranspose`
- `softmax`, `batchRelu`, `batchSigmoid`, `batchSoftmax`, `batchNormalize`
- `reluBackward`, `sigmoidBackward`, `softmaxBackward`
- `matmulBackwardA`, `matmulBackwardB`
- `sgdUpdate`, `normalize`
- `mseBackward`, `crossEntropyBackward`
- `randomUniform`, `randomNormal`

**Dense layer operations:**
- `denseForward(inputPtr, weightsPtr, m, n, p, activation)` — returns `{ outputPtr, cachePtr }`
- `denseBackward(doutPtr, inputPtr, weightsPtr, cachePtr, m, n, p, activation)` — returns `{ dWeightsPtr, dInputPtr }`

**Loss computation:**
- `mseLoss(predPtr, targetsPtr, n)` — returns loss value
- `crossEntropy(predPtr, targetsPtr, n)` — returns loss value
- `accuracy(predPtr, labelsPtr, nSamples, nClasses)` — returns accuracy

## Example

```js
o.randomSeed(42)
const weights = o.initWeights(8, 0.0, 0.1)
const session = o.createSession(65536)

for (let epoch = 0; epoch < 1000; epoch++) {
	const xPtr = session.writeArray(features)
	const yPtr = session.writeArray(targets)

	const fwd = session.denseForward(xPtr, weights._ptr, 20, 8, 1, 'sigmoid')
	const loss = session.mseLoss(fwd.outputPtr, yPtr, 20)

	const dLoss = session.mseBackward(fwd.outputPtr, yPtr, 20)
	const grad = session.denseBackward(
		dLoss, xPtr, weights._ptr, fwd.cachePtr, 20, 8, 1, 'sigmoid'
	)

	const newW = session.sgdUpdate(weights._ptr, grad.dWeightsPtr, 0.5, 8)
	session.copyToPtr(weights._ptr, session.readArray(newW, 8))

	session.clear()
}

session.destroy()
weights.free()
```

## Notes

The arena is allocated once and reused. Call `clear()` between epochs to reset the arena position without freeing the underlying memory.

Weights from `initWeights()` are malloc'd (not arena-allocated) and survive `clear()` calls.

Use `copyToPtr()` to write updated weight values back to the malloc'd pointer after SGD updates.

## See Also

denseForward(3), denseBackward(3), initWeights(3), sgdUpdate(3)
