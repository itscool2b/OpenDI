# batchSigmoid

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.batchSigmoid(input)
```

## Description

Applies the sigmoid activation function element-wise to an entire array.

For each element, computes `1 / (1 + e^(-x))`.

Wraps the C `batch_sigmoid()` function.

## Parameters

- `input`: An array of numbers

## Return Value

A `Float64Array` containing the sigmoid-activated values (each in (0, 1)).

## Example

```js
o.batchSigmoid([0, 0])    // Float64Array [0.5, 0.5]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

sigmoid(3), batchRelu(3), batchSoftmax(3), sigmoidBackward(3)
