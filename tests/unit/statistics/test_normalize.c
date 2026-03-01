#include <stdio.h>
#include <math.h>
#include "../../../include/statistics/normalize.h"
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
    printf("=== Testing normalize ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Known z-scores
    // v = {1, 2, 3}, mean=2, std=0.8165
    // z = {-1.2247, 0.0, 1.2247}
    double v1[] = {1.0, 2.0, 3.0};
    double *result = normalize(arena, v1, 3);
    check(fabs(result[1]) < EPSILON, "Middle value normalizes to ~0");
    check(result[0] < 0.0 && result[2] > 0.0, "Below mean is negative, above is positive");

    arena_clear(arena);

    // Test 2: Normalized values have mean ~0
    double v2[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    result = normalize(arena, v2, 5);
    double sum = 0.0;
    for (int i = 0; i < 5; i++) sum += result[i];
    check(fabs(sum) < EPSILON, "Normalized values have mean ~0");

    // Test 3: Normalized values have std ~1
    double mean = sum / 5.0;
    double var_sum = 0.0;
    for (int i = 0; i < 5; i++) {
        var_sum += (result[i] - mean) * (result[i] - mean);
    }
    double std = sqrt(var_sum / 5.0);
    check(fabs(std - 1.0) < EPSILON, "Normalized values have std ~1");

    arena_clear(arena);

    // Test 4: Two elements
    double v3[] = {0.0, 10.0};
    result = normalize(arena, v3, 2);
    // mean=5, std=5, z = {-1, 1}
    check(fabs(result[0] - (-1.0)) < EPSILON &&
          fabs(result[1] - 1.0) < EPSILON,
          "Two elements: {0,10} -> {-1,1}");

    arena_clear(arena);

    // Test 5: Negative values
    double v4[] = {-10.0, -5.0, 0.0, 5.0, 10.0};
    result = normalize(arena, v4, 5);
    sum = 0.0;
    for (int i = 0; i < 5; i++) sum += result[i];
    check(fabs(sum) < EPSILON, "Negative values: mean still ~0");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
