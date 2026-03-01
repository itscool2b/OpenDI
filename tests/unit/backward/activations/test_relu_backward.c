#include <stdio.h>
#include <math.h>
#include "../../../../include/backward/activations/relu_backward.h"
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
    printf("=== Testing relu_backward ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Positive inputs pass gradient through
    double dout1[] = {1.0, 2.0, 3.0};
    double input1[] = {1.0, 2.0, 3.0};
    double *grad = relu_backward(arena, dout1, input1, 3);
    check(fabs(grad[0] - 1.0) < EPSILON &&
          fabs(grad[1] - 2.0) < EPSILON &&
          fabs(grad[2] - 3.0) < EPSILON,
          "Positive inputs: gradient passes through");

    arena_clear(arena);

    // Test 2: Negative inputs block gradient
    double dout2[] = {1.0, 2.0, 3.0};
    double input2[] = {-1.0, -2.0, -3.0};
    grad = relu_backward(arena, dout2, input2, 3);
    check(fabs(grad[0]) < EPSILON &&
          fabs(grad[1]) < EPSILON &&
          fabs(grad[2]) < EPSILON,
          "Negative inputs: gradient is zero");

    arena_clear(arena);

    // Test 3: Mixed inputs
    double dout3[] = {5.0, 5.0, 5.0, 5.0};
    double input3[] = {1.0, -1.0, 0.5, -0.5};
    grad = relu_backward(arena, dout3, input3, 4);
    check(fabs(grad[0] - 5.0) < EPSILON &&
          fabs(grad[1]) < EPSILON &&
          fabs(grad[2] - 5.0) < EPSILON &&
          fabs(grad[3]) < EPSILON,
          "Mixed inputs: correct gradient masking");

    arena_clear(arena);

    // Test 4: Zero input blocks gradient
    double dout4[] = {1.0};
    double input4[] = {0.0};
    grad = relu_backward(arena, dout4, input4, 1);
    check(fabs(grad[0]) < EPSILON, "Zero input: gradient is zero");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
