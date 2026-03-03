# pow

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.pow(base, exp)
```

## Description

Computes `base` raised to the power `exp`.

Wraps the C `exponents()` function directly.

## Parameters

- `base`: The base value
- `exp`: The exponent

## Return Value

The result of `base^exp` as a `number`.

## Example

```js
o.pow(2, 10)     // 1024
o.pow(3, 3)      // 27
o.pow(25, 0.5)   // 5
```

## Notes

No arena allocation needed. Calls the WASM function directly.

## See Also

add(3), multiply(3)
