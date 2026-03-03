# sigmoid

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.sigmoid(x)
```

## Description

Computes the sigmoid activation function for a single value.

The sigmoid function is defined as: `1 / (1 + e^(-x))`, producing output in the range (0, 1).

Wraps the C `sigmoid()` function directly.

## Parameters

- `x`: A number

## Return Value

The sigmoid activation of `x` as a `number`.

## Example

```js
o.sigmoid(0)      // 0.5
o.sigmoid(10)     // ~0.9999
o.sigmoid(-10)    // ~0.0000
```

## Notes

No arena allocation needed. Calls the WASM function directly.

For batch operation on arrays, use `batchSigmoid()`.

## See Also

relu(3), softmax(3), batchSigmoid(3), sigmoidBackward(3)
