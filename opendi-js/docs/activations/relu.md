# relu

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.relu(x)
```

## Description

Computes the Rectified Linear Unit activation function for a single value.

Returns `x` if `x > 0`, otherwise returns `0`.

Wraps the C `relu()` function directly.

## Parameters

- `x`: A number

## Return Value

The ReLU activation of `x` as a `number`.

## Example

```js
o.relu(5)      // 5
o.relu(-5)     // 0
o.relu(0)      // 0
```

## Notes

No arena allocation needed. Calls the WASM function directly.

For batch operation on arrays, use `batchRelu()`.

## See Also

sigmoid(3), softmax(3), batchRelu(3), reluBackward(3)
