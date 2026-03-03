# multiply

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.multiply(...numbers)
```

## Description

Computes the product of all provided numbers. Accepts any number of arguments.

Wraps the C `multiply_numbers()` variadic function via an array-based glue layer.

## Parameters

- `...numbers`: One or more numbers (or a single array of numbers)

## Return Value

The product of all arguments as a `number`.

## Example

```js
o.multiply(2, 3, 4)    // 24
o.multiply(5, 10)      // 50
```

## Notes

Arguments are flattened, so both `o.multiply(2, 3)` and `o.multiply([2, 3])` work identically.

## See Also

add(3), subtract(3), divide(3)
