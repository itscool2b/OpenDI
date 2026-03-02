#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/batch_relu.h"
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
    printf("=== Testing batch_relu ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Positive values pass through
    double v1[] = {1.0, 2.0, 3.0};
    double *result = batch_relu(arena, v1, 3);
    check(fabs(result[0] - 1.0) < EPSILON &&
          fabs(result[1] - 2.0) < EPSILON &&
          fabs(result[2] - 3.0) < EPSILON,
          "Positive values pass through unchanged");

    arena_clear(arena);

    // Test 2: Negative values become zero
    double v2[] = {-1.0, -2.0, -3.0};
    result = batch_relu(arena, v2, 3);
    check(fabs(result[0]) < EPSILON &&
          fabs(result[1]) < EPSILON &&
          fabs(result[2]) < EPSILON,
          "Negative values become zero");

    arena_clear(arena);

    // Test 3: Mixed values
    double v3[] = {-2.0, 0.0, 3.0, -1.0, 5.0};
    result = batch_relu(arena, v3, 5);
    check(fabs(result[0]) < EPSILON &&
          fabs(result[1]) < EPSILON &&
          fabs(result[2] - 3.0) < EPSILON &&
          fabs(result[3]) < EPSILON &&
          fabs(result[4] - 5.0) < EPSILON,
          "Mixed positive and negative values");

    arena_clear(arena);

    // Test 4: Single element
    double v4[] = {7.0};
    result = batch_relu(arena, v4, 1);
    check(fabs(result[0] - 7.0) < EPSILON, "Single positive element");

    arena_clear(arena);

    // Test 5: Zero input
    double v5[] = {0.0};
    result = batch_relu(arena, v5, 1);
    check(fabs(result[0]) < EPSILON, "Zero input returns zero");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
