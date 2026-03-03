# opendi-js

WebAssembly bindings for the OpenDI math and machine learning library. Compiles the pure C99 engine to WASM via Emscripten and wraps it with an idiomatic JavaScript API.

Works in Node.js, Deno, Bun, and browsers.

## Features

- **Primitive Operations** - add, subtract, multiply, divide, abs, min, max, round, pow
- **Calculus** - Forward/backward/central difference, second derivative, nth derivative, Romberg integration
- **Linear Algebra** - Vectors (add, dot, cross, norm, scale) and matrices (multiply, add, scale, transpose)
- **Activations** - relu, sigmoid, softmax
- **Loss Functions** - MSE, cross-entropy
- **Backward Functions** - Gradient computation for activations and matrix operations
- **Optimizers** - SGD weight updates
- **Random** - Seeded uniform and normal distributions
- **Statistics** - Z-score normalization
- **Pipeline** - Batch activations, dense layers, loss gradients, weight initialization
- **Session API** - Pointer-level arena control for training loops
- **Zero Copy Overhead** - WASM heap operations, no serialization

## Two-Tier API

### Tier 1: Simple Functions

Pass JavaScript arrays, get results back. Memory is managed automatically.

```js
import { init } from 'opendi-js'

const o = await init()

o.add(1, 2, 3)                    // 6
o.softmax([1, 2, 3])              // Float64Array [0.09, 0.24, 0.66]
o.matmul([1,2,3,4], [5,6,7,8], 2, 2, 2)  // Float64Array [19,22,43,50]
o.forwarddiff(x => x * x, 3, 0.001)      // ~6.0
```

### Tier 2: Session API

For training loops where performance matters. Work with WASM pointers directly, control arena memory manually.

```js
const session = o.createSession(65536)

const inputPtr = session.writeArray([0.1, 0.3, 0.7, 0.9])
const targetPtr = session.writeArray([0, 0, 1, 1])

const fwd = session.denseForward(inputPtr, weights._ptr, 4, 1, 1, 'sigmoid')
const loss = session.mseLoss(fwd.outputPtr, targetPtr, 4)

session.clear()    // reuse arena memory between epochs
session.destroy()  // free arena when done
```

## Quick Start

### Install

```bash
npm install opendi-js
```

### ESM

```js
import { init } from 'opendi-js'
const o = await init()
```

### CommonJS

```js
const { init } = require('opendi-js')
const o = await init()
```

## API Reference

### Primitives

```js
o.add(1, 2, 3)          // 6 (variadic)
o.subtract(10, 3)       // 7 (variadic)
o.multiply(2, 3, 4)     // 24 (variadic)
o.divide(100, 5, 2)     // 10 (variadic)
o.abs(-5)               // 5
o.min(3, 1, 2)          // 1 (variadic)
o.max(3, 1, 2)          // 3 (variadic)
o.round('floor', 3.7)   // 3 ('floor', 'ceil', 'round')
o.pow(2, 10)            // 1024
```

### Activations

```js
o.relu(5)               // 5
o.relu(-5)              // 0
o.sigmoid(0)            // 0.5
o.softmax([1, 2, 3])    // Float64Array (sums to 1.0)
```

### Vectors

```js
o.vecadd([1,2,3], [4,5,6])    // Float64Array [5,7,9]
o.vecscale([1,2,3], 2)        // Float64Array [2,4,6]
o.veccross([1,0,0], [0,1,0])  // Float64Array [0,0,1]
o.vecdot([1,2,3], [4,5,6])    // 32
o.vecnorm([3, 4])             // 5
```

### Matrices

All matrices are flat arrays in row-major order.

```js
o.matmul([1,2,3,4], [5,6,7,8], 2, 2, 2)    // Float64Array [19,22,43,50]
o.matadd([1,2,3,4], [10,20,30,40], 2, 2)    // Float64Array [11,22,33,44]
o.matscale([1,2,3,4], 3, 2, 2)              // Float64Array [3,6,9,12]
o.mattranspose([1,2,3,4,5,6], 2, 3)         // Float64Array [1,4,2,5,3,6]
```

### Loss Functions

```js
o.mseLoss([1,2,3], [1,2,3])    // 0 (perfect prediction)
o.crossEntropy(pred, targets)   // cross-entropy loss
```

### Backward (Gradients)

```js
o.reluBackward(dout, input)                   // Float64Array
o.sigmoidBackward(dout, output)               // Float64Array
o.softmaxBackward(dout, output)               // Float64Array
o.matmulBackwardA(dout, b, m, n, p)           // Float64Array (gradient w.r.t. A)
o.matmulBackwardB(a, dout, m, n, p)           // Float64Array (gradient w.r.t. B)
```

### Optimizer

```js
o.sgdUpdate([1,2,3], [0.1,0.2,0.3], 1.0)    // Float64Array [0.9, 1.8, 2.7]
```

### Random

```js
o.randomSeed(42)
o.randomUniform(0, 1, 5)      // Float64Array of 5 values in [0, 1]
o.randomNormal(0, 1, 5)       // Float64Array of 5 values ~ N(0, 1)
```

### Statistics

```js
o.normalize([2,4,4,4,5,5,7,9])    // Float64Array (mean ~0, std ~1)
```

### Calculus

Pass regular JavaScript functions. They are compiled to WASM function pointers internally.

```js
o.forwarddiff(x => x*x, 3, 0.001)         // ~6.0
o.backwarddiff(x => x*x, 3, 0.001)        // ~6.0
o.centralDifference(x => x*x, 3, 0.001)   // ~6.0
o.secondDerivative(x => x*x, 3, 0.001)    // ~2.0
o.centralNth(x => x*x, 3, 0.001, 2)       // ~2.0 (nth derivative)
o.rombergIntegrate(x => x*x, 0, 1, 1e-8, 10)  // ~0.333
```

### Pipeline

```js
o.batchRelu([-1, 2, -3, 4])           // Float64Array [0,2,0,4]
o.batchSigmoid([0, 0])                // Float64Array [0.5, 0.5]
o.batchSoftmax(input, rows, cols)     // Float64Array (per-row softmax)
o.batchNormalize(features, n, nFeat)  // Float64Array (z-score normalized)
o.mseBackward(pred, targets)          // Float64Array (MSE gradient)
o.crossEntropyBackward(pred, targets, nSamples, nClasses)  // Float64Array
o.accuracy(pred, labels, nSamples, nClasses)               // number
```

### Weights

```js
o.randomSeed(42)
const w = o.initWeights(10, 0.0, 0.1)
w.data      // Float64Array of 10 values
w._ptr      // WASM pointer (for session API)
w.length    // 10
w.free()    // free the malloc'd memory
```

### Session API

```js
const session = o.createSession(65536)

session.writeArray([1, 2, 3])          // returns WASM pointer
session.writeI32Array([0, 1, 2])       // returns WASM pointer (int32)
session.readArray(ptr, 3)              // Float64Array from pointer
session.copyToPtr(destPtr, srcArray)   // write JS array to existing pointer

// All math functions available with pointer args:
session.vecadd(aPtr, bPtr, n)
session.matmul(aPtr, bPtr, m, n, p)
session.denseForward(inputPtr, weightsPtr, m, n, p, 'sigmoid')
session.denseBackward(doutPtr, inputPtr, weightsPtr, cachePtr, m, n, p, 'sigmoid')
session.sgdUpdate(weightsPtr, gradsPtr, lr, n)
session.mseLoss(predPtr, targetsPtr, n)

session.clear()      // arena_clear() - reuse memory
session.destroy()    // arena_destroy() - free arena
```

## Training Loop Example

```js
import { init } from 'opendi-js'

const o = await init()
o.randomSeed(42)

const features = [0.1, 0.3, 0.7, 0.9]
const targets = [0, 0, 1, 1]
const nSamples = 4, nFeatures = 1

const weights = o.initWeights(nFeatures, 0.0, 0.1)
const session = o.createSession(65536)

for (let epoch = 0; epoch < 200; epoch++) {
	const featPtr = session.writeArray(features)
	const targPtr = session.writeArray(targets)

	const fwd = session.denseForward(featPtr, weights._ptr, nSamples, nFeatures, 1, 'sigmoid')
	const loss = session.mseLoss(fwd.outputPtr, targPtr, nSamples)

	const dLoss = session.mseBackward(fwd.outputPtr, targPtr, nSamples)
	const grad = session.denseBackward(dLoss, featPtr, weights._ptr, fwd.cachePtr, nSamples, nFeatures, 1, 'sigmoid')

	const newWPtr = session.sgdUpdate(weights._ptr, grad.dWeightsPtr, 1.0, nFeatures)
	session.copyToPtr(weights._ptr, session.readArray(newWPtr, nFeatures))

	session.clear()
}

session.destroy()
weights.free()
```

## Building from Source

Requires [Emscripten](https://emscripten.org/).

```bash
cd opendi-js
bash scripts/build.sh
```

Produces `build/opendi.js` and `build/opendi.wasm`.

## Testing

```bash
node test/test.mjs
```

## Documentation

API documentation is in `docs/`. Each function group has its own documentation file organized by module.

## See Also

- [OpenDI C Library](../README.md) - The underlying C99 engine
- [API Documentation](docs/) - Detailed function reference
