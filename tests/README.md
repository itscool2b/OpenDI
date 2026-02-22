# OpenDI Test Suite

This directory contains the complete test suite for OpenDI, organized into three categories:

```
tests/
├── README.md                  # This file
├── unit/                      # Unit tests for individual functions
│   ├── primitive/             # Tests for primitive operations (add, subtract, etc.)
│   ├── calculus/              # Tests for calculus functions (derivatives, integrals)
│   └── linalg/                # Tests for linear algebra
│       └── vectors/           # Tests for vector operations
├── scenarios/                 # Real-world scenario tests (functions used together)
│   ├── tests/                 # Scenario test source code
│   │   └── test_opendi_full_scenario.c
│   └── reports/               # Scenario test documentation
│       └── SCENARIO_TEST_REPORT.md
└── performance/               # Performance benchmarks
    ├── tests/                 # Performance test source code
    │   └── test_opendi_performance.c
    └── reports/               # Performance analysis reports
        └── PERFORMANCE_BENCHMARKS.md
```

## Quick Start

### Running Unit Tests

```bash
# Compile and run vector tests (include arena.h)
gcc -I../../include unit/linalg/vectors/test_vecadd.c src/linalg/vectors/vecadd.c -o test_vecadd -lm
./test_vecadd
```

### Running Scenario Tests

Scenario tests show how multiple functions work together in real programs:

```bash
# Compile with all source files
gcc -I../../include \
    scenarios/tests/test_opendi_full_scenario.c \
    src/primitive/*/*.c \
    src/calculus/*/*/*.c \
    src/linalg/vectors/*.c \
    -o test_scenarios -lm

./test_scenarios
```

### Running Performance Benchmarks

```bash
# Compile with optimization
gcc -O2 -I../../include \
    performance/tests/test_opendi_performance.c \
    src/primitive/*/*.c \
    src/calculus/*/*/*.c \
    src/linalg/vectors/*.c \
    -o test_performance -lm

./test_performance
```

## Test Categories

### 1. Unit Tests (`unit/`)

Tests individual functions in isolation with edge cases.

**Structure:**
- `unit/primitive/` - Tests for basic arithmetic operations
- `unit/calculus/` - Tests for numerical differentiation and integration
- `unit/linalg/vectors/` - Tests for vector operations (add, dot, cross, norm, scale)

**Each unit test should:**
- Test normal operation
- Test edge cases (zero, negative, large values)
- Test error conditions (NULL, empty inputs)
- Report pass/fail for each test case

### 2. Scenario Tests (`scenarios/`)

Tests multiple functions working together in realistic, real-world programs.

**Current Tests:**
- `test_opendi_full_scenario.c` - Chains all 18 functions in physics simulation scenarios
  - Particle motion analysis (position, velocity, acceleration)
  - Force field analysis (work, energy)
  - Statistical pipeline (mean, distances)
  - Precision workflow (PI approximation)

**Reports:**
- `SCENARIO_TEST_REPORT.md` - Documents test scenarios, results, and time savings

### 3. Performance Tests (`performance/`)

Hardware-level benchmarks measuring execution time, throughput, and memory usage.

**Current Benchmarks:**
- `test_opendi_performance.c` - Comprehensive performance suite
  - Vector addition throughput (FLOPS, memory bandwidth)
  - Cache efficiency (OpenDI vs manual loops)
  - Differentiation accuracy vs speed
  - Integration convergence speed
  - Memory allocation overhead
  - Cross product overhead analysis

**Reports:**
- `PERFORMANCE_BENCHMARKS.md` - Detailed analysis with real numbers
  - 4.25 billion elements/sec peak throughput
  - 0.31% function call overhead (excellent!)
  - 97 GB/s memory bandwidth utilization
  - Cache efficiency analysis

## Adding New Tests

### Adding a Unit Test

1. Create `unit/<category>/test_<function>.c`
2. Include the header: `#include "../../../../include/<path>/<header>.h"`
3. Follow the template:
   ```c
   #include <stdio.h>
   #include <math.h>
   #include "../../../../include/path/to/header.h"
   
   #define EPSILON 1e-10
   
   int main() {
       // Test normal case
       // Test edge cases
       // Test error conditions
       printf("Results: pass=X, fail=Y\n");
       return 0;
   }
   ```

### Adding a Scenario Test

1. Create `scenarios/tests/test_<scenario>.c`
2. Chain multiple OpenDI functions in a realistic program
3. Document the function chain in the header comments
4. Add report to `scenarios/reports/`

### Adding a Performance Benchmark

1. Create `performance/tests/benchmark_<operation>.c`
2. Use `clock_gettime(CLOCK_MONOTONIC, ...)` for timing
3. Compare against manual implementation
4. Add findings to `performance/reports/`

## Test Binaries

Compiled test binaries should be placed in `/opendi/test_bin/` (not committed to git).

## Continuous Integration

Recommended CI pipeline:
```bash
# 1. Build all unit tests
# 2. Run all unit tests (must all pass)
# 3. Build scenario tests
# 4. Run scenario tests (must all pass)
# 5. Build performance tests
# 6. Run performance tests (informational, no pass/fail)
```

## Notes

- Vector tests use arena allocator (arena_create/arena_destroy)
- Performance tests should be compiled with `-O2` or `-O3`
- Include paths use relative paths (`../../../include/`) for portability
- Tests should be self-contained (no external dependencies beyond OpenDI)
