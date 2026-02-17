# OpenDI

A lightweight, portable C library for mathematical computation. Designed for bare-metal environments, embedded systems, and general-purpose numerical computing where minimal dependencies and predictable behavior are required.

## Overview

OpenDI provides fundamental mathematical operations and numerical analysis tools without external dependencies beyond the standard C library. The library is structured into modular components that can be used independently or combined as needed.

## Features

- **Primitive Operations**: Variadic arithmetic, absolute value, min/max, rounding, exponentiation
- **Calculus**: Numerical differentiation (forward, backward, central difference, second derivative)

## Requirements

- C99 or later
- Standard C library (libc)
- Math library (libm)

## Building

Compile specific source files as needed:

```bash
gcc -I./include your_program.c \
    src/primitive/add/add.c \
    src/primitive/multiply/multiply.c \
    -o your_program -lm
```

Or build a static library:

```bash
find src -name "*.c" -exec gcc -I./include -c {} \;
ar rcs libopendi.a *.o
```

## Testing

```bash
mkdir -p test_bin
for test in tests/test_*.c; do
    name=$(basename $test .c)
    gcc -I./include $test \
        src/primitive/*/*.c \
        src/calculus/*/*/*.c \
        -o test_bin/$name -lm
done

for test in test_bin/test_*; do ./$test; done
```

## Documentation

API documentation is located in `docs/`. Each function has its own documentation file.

## Project Structure

```
include/
├── primitive/
└── calculus/

src/
├── primitive/                 [DONE]
│   ├── absolute
│   ├── add
│   ├── subtract
│   ├── multiply
│   ├── divide
│   ├── minmax
│   ├── rounding
│   └── exponents
│
├── calculus/
│   ├── derivatives/           [DONE]
│   │   ├── forwarddiff
│   │   ├── backwarddiff
│   │   ├── centraldiff
│   │   ├── secondderivative
│   │   ├── diff_central_nth
│   │   └── polydiff
│   │
│   ├── integrals/             [TODO]
│   │   ├── trapezoidal
│   │   ├── simpsons
│   │   └── romberg
│   │
│   ├── roots/                 [TODO]
│   │   ├── bisection
│   │   ├── newtonraphson
│   │   └── secant
│   │
│   ├── optimize/              [TODO]
│   │   └── goldensection
│   │
│   └── ode/                   [TODO]
│       ├── euler
│       └── rk4
│
├── elementary/                [TODO]
│   ├── trig/
│   │   ├── sin
│   │   ├── cos
│   │   ├── tan
│   │   ├── asin
│   │   ├── acos
│   │   └── atan
│   │
│   ├── explog/
│   │   ├── exp
│   │   ├── log
│   │   ├── log2
│   │   ├── sqrt
│   │   └── cbrt
│   │
│   └── hyperbolic/
│       ├── sinh
│       ├── cosh
│       └── tanh
│
├── linalg/                    [TODO]
│   ├── vec/
│   │   ├── vecadd
│   │   ├── vecscale
│   │   ├── vecdot
│   │   ├── veccross
│   │   └── vecnorm
│   │
│   └── mat/
│       ├── matmul
│       ├── mattranspose
│       ├── matdet
│       └── matinverse
│
├── special/                   [TODO]
│   ├── gamma
│   ├── erf
│   └── beta
│
├── stats/                     [TODO]
│   ├── mean
│   ├── variance
│   └── linearregression
│
└── utils/                     [TODO]
    ├── clamp
    ├── lerp
    ├── smoothstep
    └── floatequals
```

## Design Principles

- Explicit error handling via return values
- Consistent interface patterns across modules
- Minimal dependencies for maximum portability
- Predictable behavior for edge cases

## Limitations

- Numerical differentiation accuracy depends on step size selection
- Variadic functions require compile-time knowledge of argument count
- Some functions return sentinel values (NAN, 0.0) on error

## License

[Add license information]

## Contributing

[Add contribution guidelines]
