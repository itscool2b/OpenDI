# softmaxBackward

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.softmaxBackward(dout, output)
```

## Description

Computes the gradient of the softmax activation function.

Wraps the C `softmax_backward()` function.

## Parameters

- `dout`: Upstream gradient (array of numbers)
- `output`: The post-activation softmax output (array of numbers, same length)

## Return Value

A `Float64Array` containing the gradient with respect to the pre-activation input.

## Example

```js
const sm = o.softmax([1, 2, 3])
const grad = o.softmaxBackward([1, 0, 0], sm)
```

## Notes

Memory is automatically managed via a temporary arena.

When using softmax + cross-entropy, prefer the combined shortcut: use `ACTIVATION_SOFTMAX` in `denseForward()`, then `ACTIVATION_NONE` in `denseBackward()` with `crossEntropyBackward()`. This is numerically more stable than calling `softmaxBackward()` separately.

## See Also

softmax(3), reluBackward(3), sigmoidBackward(3), crossEntropyBackward(3)
