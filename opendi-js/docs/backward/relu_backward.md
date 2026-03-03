# reluBackward

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.reluBackward(dout, input)
```

## Description

Computes the gradient of the ReLU activation function.

For each element, the gradient passes through if the input was positive, otherwise it is zeroed out.

Wraps the C `relu_backward()` function.

## Parameters

- `dout`: Upstream gradient (array of numbers)
- `input`: Original pre-activation input (array of numbers, same length)

## Return Value

A `Float64Array` containing the gradient with respect to the input.

## Example

```js
o.reluBackward([1, 1, 1], [5, -3, 0.1])
// Float64Array [1, 0, 1]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

relu(3), sigmoidBackward(3), softmaxBackward(3), denseBackward(3)
