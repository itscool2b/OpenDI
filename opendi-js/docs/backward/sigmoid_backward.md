# sigmoidBackward

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.sigmoidBackward(dout, output)
```

## Description

Computes the gradient of the sigmoid activation function.

The gradient is `dout * output * (1 - output)`.

Wraps the C `sigmoid_backward()` function.

## Parameters

- `dout`: Upstream gradient (array of numbers)
- `output`: The post-activation sigmoid output (array of numbers, same length)

## Return Value

A `Float64Array` containing the gradient with respect to the pre-activation input.

## Example

```js
o.sigmoidBackward([1, 1], [0.5, 0.5])
// Float64Array [0.25, 0.25]   (0.5 * 0.5 = 0.25)
```

## Notes

Memory is automatically managed via a temporary arena.

Note that `output` is the post-activation value (after sigmoid), not the pre-activation input. This matches the cache semantics of `denseForward()` with `ACTIVATION_SIGMOID`.

## See Also

sigmoid(3), reluBackward(3), softmaxBackward(3), denseBackward(3)
