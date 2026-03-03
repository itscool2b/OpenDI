# batchRelu

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.batchRelu(input)
```

## Description

Applies the ReLU activation function element-wise to an entire array.

For each element, returns `max(0, x)`.

Wraps the C `batch_relu()` function.

## Parameters

- `input`: An array of numbers

## Return Value

A `Float64Array` containing the ReLU-activated values.

## Example

```js
o.batchRelu([-1, 2, -3, 4])    // Float64Array [0, 2, 0, 4]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

relu(3), batchSigmoid(3), batchSoftmax(3), reluBackward(3)
