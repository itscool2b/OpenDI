# OpenDI

A lightweight, portable C library for mathematical computation. Designed for bare-metal environments, embedded systems, and general-purpose numerical computing.

## Documentation

API documentation is located in `docs/`. Each function has its own documentation file organized by module.

## Testing

The test suite is organized into three categories:

- **`tests/unit/`** - Unit tests for individual functions
- **`tests/scenarios/`** - Real-world scenario tests (functions working together)
- **`tests/performance/`** - Hardware-level performance benchmarks

See `tests/README.md` for detailed testing instructions.

## Module Checklist

```
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
│   ├── integrals/             [DONE]
│   │   ├── romberg
│   │   ├── trapezoidal        [TODO]
│   │   └── simpsons           [TODO]
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
├── linalg/
│   ├── vectors/               [DONE]
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
