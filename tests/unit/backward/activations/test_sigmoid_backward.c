#include <stdio.h>
#include <math.h>
#include "../../../../include/backward/activations/sigmoid_backward.h"
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
    printf("=== Testing sigmoid_backward ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Output of 0.5 gives max gradient
    // sigmoid_backward = dout * output * (1 - output)
    // When output=0.5: grad = 1.0 * 0.5 * 0.5 = 0.25
    double dout1[] = {1.0};
    double output1[] = {0.5};
    double *grad = sigmoid_backward(arena, dout1, output1, 1);
    check(fabs(grad[0] - 0.25) < EPSILON, "Output 0.5: gradient = 0.25");

    arena_clear(arena);

    // Test 2: Output near 0 gives near-zero gradient
    double dout2[] = {1.0};
    double output2[] = {0.01};
    grad = sigmoid_backward(arena, dout2, output2, 1);
    // 1.0 * 0.01 * 0.99 = 0.0099
    check(fabs(grad[0] - 0.0099) < EPSILON, "Output near 0: small gradient");

    arena_clear(arena);

    // Test 3: Output near 1 gives near-zero gradient
    double dout3[] = {1.0};
    double output3[] = {0.99};
    grad = sigmoid_backward(arena, dout3, output3, 1);
    // 1.0 * 0.99 * 0.01 = 0.0099
    check(fabs(grad[0] - 0.0099) < EPSILON, "Output near 1: small gradient");

    arena_clear(arena);

    // Test 4: Multiple elements with scaling
    double dout4[] = {2.0, 3.0};
    double output4[] = {0.5, 0.5};
    grad = sigmoid_backward(arena, dout4, output4, 2);
    check(fabs(grad[0] - 0.5) < EPSILON &&
          fabs(grad[1] - 0.75) < EPSILON,
          "Multiple elements: dout scales gradient");

    arena_clear(arena);

    // Test 5: Output of 0 gives zero gradient
    double dout5[] = {1.0};
    double output5[] = {0.0};
    grad = sigmoid_backward(arena, dout5, output5, 1);
    check(fabs(grad[0]) < EPSILON, "Output 0: gradient is zero");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
