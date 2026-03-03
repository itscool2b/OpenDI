# add

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.add(...numbers)
```

## Description

Computes the sum of all provided numbers. Accepts any number of arguments, which may also be passed as an array.

Wraps the C `add_numbers()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: One or more numbers (or a single array of numbers)

## Return Value

The sum of all arguments as a `number`.

## Example

```js
o.add(1, 2, 3)        // 6
o.add(10, 20)          // 30
o.add([5, 10, 15])     // 30
```

## Notes

Arguments are flattened, so both `o.add(1, 2, 3)` and `o.add([1, 2, 3])` work identically.

A temporary WASM arena is created and destroyed for each call.

## See Also

subtract(3), multiply(3), divide(3)
