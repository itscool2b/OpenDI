#include <stdio.h>
#include <math.h>
#include "../../../include/optimizers/sgd_update.h"
#include "../../../include/arena.h"

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
    printf("=== Testing sgd_update ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic update
    double w1[] = {1.0, 2.0, 3.0};
    double g1[] = {0.1, 0.2, 0.3};
    double *result = sgd_update(arena, w1, g1, 0.1, 3);
    // result = {1.0 - 0.01, 2.0 - 0.02, 3.0 - 0.03}
    check(fabs(result[0] - 0.99) < EPSILON &&
          fabs(result[1] - 1.98) < EPSILON &&
          fabs(result[2] - 2.97) < EPSILON,
          "Basic update: w - lr*g");

    arena_clear(arena);

    // Test 2: Zero learning rate (no update)
    double w2[] = {5.0, 10.0};
    double g2[] = {100.0, 200.0};
    result = sgd_update(arena, w2, g2, 0.0, 2);
    check(fabs(result[0] - 5.0) < EPSILON &&
          fabs(result[1] - 10.0) < EPSILON,
          "Zero learning rate: weights unchanged");

    arena_clear(arena);

    // Test 3: Zero gradients (no update)
    double w3[] = {1.0, 2.0};
    double g3[] = {0.0, 0.0};
    result = sgd_update(arena, w3, g3, 0.1, 2);
    check(fabs(result[0] - 1.0) < EPSILON &&
          fabs(result[1] - 2.0) < EPSILON,
          "Zero gradients: weights unchanged");

    arena_clear(arena);

    // Test 4: Large learning rate
    double w4[] = {10.0};
    double g4[] = {5.0};
    result = sgd_update(arena, w4, g4, 1.0, 1);
    // 10.0 - 1.0 * 5.0 = 5.0
    check(fabs(result[0] - 5.0) < EPSILON, "Large lr: 10 - 1.0*5 = 5");

    arena_clear(arena);

    // Test 5: Negative gradients (weights increase)
    double w5[] = {1.0};
    double g5[] = {-2.0};
    result = sgd_update(arena, w5, g5, 0.5, 1);
    // 1.0 - 0.5 * (-2.0) = 1.0 + 1.0 = 2.0
    check(fabs(result[0] - 2.0) < EPSILON, "Negative gradient: weight increases");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
