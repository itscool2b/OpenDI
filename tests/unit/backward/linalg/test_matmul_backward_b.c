#include <stdio.h>
#include <math.h>
#include "../../../../include/backward/linalg/matmul_backward_b.h"
#include "../../../../include/arena.h"

#define EPSILON 1e-10

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
    printf("=== Testing matmul_backward_b ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: 2x2 case
    // Forward: A(2x2) @ B(2x2) = C(2x2)
    // Backward: dL/dB = A^T(2x2) @ dout(2x2)
    double a1[] = {1.0, 2.0, 3.0, 4.0};      // 2x2
    double dout1[] = {1.0, 0.0, 0.0, 1.0};    // 2x2 identity
    // A^T = {1, 3, 2, 4}
    // A^T @ dout = A^T @ I = A^T = {1, 3, 2, 4}
    double *grad = matmul_backward_b(arena, a1, dout1, 2, 2, 2);
    check(fabs(grad[0] - 1.0) < EPSILON &&
          fabs(grad[1] - 3.0) < EPSILON &&
          fabs(grad[2] - 2.0) < EPSILON &&
          fabs(grad[3] - 4.0) < EPSILON,
          "2x2: dout=I gives A^T");

    arena_clear(arena);

    // Test 2: Non-square case
    // Forward: A(2x3) @ B(3x2) = C(2x2)
    // Backward: dL/dB = A^T(3x2) @ dout(2x2) = result(3x2)
    double a2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};  // 2x3
    double dout2[] = {1.0, 0.0, 0.0, 1.0};            // 2x2
    // A^T(3x2) = {1, 4, 2, 5, 3, 6}
    // A^T @ I = A^T = {1, 4, 2, 5, 3, 6}
    grad = matmul_backward_b(arena, a2, dout2, 2, 3, 2);
    check(fabs(grad[0] - 1.0) < EPSILON &&
          fabs(grad[1] - 4.0) < EPSILON &&
          fabs(grad[2] - 2.0) < EPSILON &&
          fabs(grad[3] - 5.0) < EPSILON &&
          fabs(grad[4] - 3.0) < EPSILON &&
          fabs(grad[5] - 6.0) < EPSILON,
          "Non-square: 3x2 @ 2x2 = 3x2 gradient");

    arena_clear(arena);

    // Test 3: All-ones dout
    double a3[] = {1.0, 2.0, 3.0, 4.0};    // 2x2
    double dout3[] = {1.0, 1.0, 1.0, 1.0};  // 2x2
    // A^T = {1, 3, 2, 4}
    // A^T @ dout = {1+3, 1+3, 2+4, 2+4} = {4, 4, 6, 6}
    grad = matmul_backward_b(arena, a3, dout3, 2, 2, 2);
    check(fabs(grad[0] - 4.0) < EPSILON &&
          fabs(grad[1] - 4.0) < EPSILON &&
          fabs(grad[2] - 6.0) < EPSILON &&
          fabs(grad[3] - 6.0) < EPSILON,
          "All-ones dout: correct gradient");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
