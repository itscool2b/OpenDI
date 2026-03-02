# OpenDI Test Suite

This directory contains the test suite for OpenDI, organized into two categories:

```
tests/
├── README.md                  # This file
├── unit/                      # Unit tests for individual functions
│   ├── primitive/             # Tests for primitive operations
│   ├── calculus/              # Tests for calculus functions
│   ├── linalg/                # Tests for linear algebra
│   ├── activations/           # Tests for activation functions
│   ├── backward/              # Tests for backward (gradient) functions
│   ├── loss/                  # Tests for loss functions
│   ├── optimizers/            # Tests for optimizer functions
│   ├── random/                # Tests for random number generation
│   ├── statistics/            # Tests for statistics functions
│   ├── pipeline/              # Tests for pipeline functions
│   └── test_master_header.c   # Tests that opendi.h compiles correctly
└── performance/               # Performance benchmarks
    ├── tests/
    │   └── test_opendi_performance.c
    └── reports/
        └── PERFORMANCE_BENCHMARKS.md
```

## Quick Start

### Running Unit Tests

Each unit test compiles with its function's source file:

```bash
# Example: test a pipeline function
gcc -Iinclude tests/unit/pipeline/test_batch_relu.c \
    src/pipeline/batch_relu.c src/activations/relu.c \
    -o test_bin/test_batch_relu -lm
./test_bin/test_batch_relu

# Example: test an activation function
gcc -Iinclude tests/unit/activations/test_softmax.c \
    src/activations/softmax.c src/primitive/exponents/exponents.c \
    -o test_bin/test_softmax -lm
./test_bin/test_softmax

# Example: test the master header (needs all sources)
gcc -Iinclude tests/unit/test_master_header.c src/**/*.c \
    -o test_bin/test_master_header -lm
./test_bin/test_master_header
```

### Running Performance Benchmarks

```bash
gcc -O2 -Iinclude \
    performance/tests/test_opendi_performance.c \
    src/primitive/*/*.c \
    src/calculus/*/*/*.c \
    src/linalg/vectors/*.c \
    -o test_bin/test_performance -lm
./test_bin/test_performance
```

## Test Categories

### 1. Unit Tests (`unit/`)

Tests individual functions in isolation with edge cases.

Each unit test uses the `check()` helper pattern:
```c
#include <stdio.h>
#include <math.h>
#include "../../../include/path/to/header.h"

#define EPSILON 1e-6

int test_passed = 0;
int test_failed = 0;

void check(int condition, const char *test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
        test_passed++;
    } else {
        printf("[FAIL] %s\n", test_name);
        test_failed++;
    }
}

int main() {
    // Tests here...
    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);
    return test_failed > 0 ? 1 : 0;
}
```

### 2. Performance Tests (`performance/`)

Hardware-level benchmarks measuring execution time, throughput, and memory usage.

Should be compiled with `-O2` or `-O3`.

## Real-World Examples

Real-world examples showing functions working together are in `examples/` at the project root, with documentation in `docs/examples/`.

## Test Binaries

Compiled test binaries are placed in `test_bin/` at the project root (not committed to git).

## Notes

- Functions using the arena allocator need arena_create/arena_destroy in tests
- Include paths use relative paths (`../../../include/`) for portability
- Tests should be self-contained (no external dependencies beyond OpenDI)
