#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/mse_backward.h"
#include "../../../include/arena.h"

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
    printf("=== Testing mse_backward ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Perfect predictions give zero gradient
    double pred1[] = {1.0, 0.0, 0.5};
    double tgt1[] = {1.0, 0.0, 0.5};
    double *result = mse_backward(arena, pred1, tgt1, 3);
    check(fabs(result[0]) < EPSILON &&
          fabs(result[1]) < EPSILON &&
          fabs(result[2]) < EPSILON,
          "Perfect predictions give zero gradient");

    arena_clear(arena);

    // Test 2: Known gradient values
    double pred2[] = {0.8, 0.3};
    double tgt2[] = {1.0, 0.0};
    result = mse_backward(arena, pred2, tgt2, 2);
    // grad[0] = 2*(0.8-1.0)/2 = -0.2
    // grad[1] = 2*(0.3-0.0)/2 = 0.3
    check(fabs(result[0] - (-0.2)) < EPSILON &&
          fabs(result[1] - 0.3) < EPSILON,
          "Known gradient values: 2*(pred-target)/n");

    arena_clear(arena);

    // Test 3: Single element
    double pred3[] = {0.7};
    double tgt3[] = {1.0};
    result = mse_backward(arena, pred3, tgt3, 1);
    // grad = 2*(0.7-1.0)/1 = -0.6
    check(fabs(result[0] - (-0.6)) < EPSILON, "Single element gradient");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
