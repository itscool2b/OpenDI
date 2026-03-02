#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/batch_normalize.h"
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
    printf("=== Testing batch_normalize ===\n\n");

    Arena *arena = arena_create(65536);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Each column has mean ~0
    double v1[] = {1.0, 10.0,
                   2.0, 20.0,
                   3.0, 30.0,
                   4.0, 40.0};
    double *result = batch_normalize(arena, v1, 4, 2);

    double mean_col0 = (result[0] + result[2] + result[4] + result[6]) / 4.0;
    double mean_col1 = (result[1] + result[3] + result[5] + result[7]) / 4.0;
    check(fabs(mean_col0) < EPSILON && fabs(mean_col1) < EPSILON,
          "Normalized columns have mean ~0");

    // Test 2: Each column has std ~1
    double var0 = 0.0, var1 = 0.0;
    for (int i = 0; i < 4; i++){
        var0 += result[i * 2] * result[i * 2];
        var1 += result[i * 2 + 1] * result[i * 2 + 1];
    }
    double std0 = sqrt(var0 / 4.0);
    double std1 = sqrt(var1 / 4.0);
    check(fabs(std0 - 1.0) < EPSILON && fabs(std1 - 1.0) < EPSILON,
          "Normalized columns have std ~1");

    arena_clear(arena);

    // Test 3: Single column
    double v3[] = {10.0, 20.0, 30.0};
    result = batch_normalize(arena, v3, 3, 1);
    double mean = (result[0] + result[1] + result[2]) / 3.0;
    check(fabs(mean) < EPSILON, "Single column normalized has mean ~0");

    arena_clear(arena);

    // Test 4: Ordering preserved within column
    double v4[] = {1.0, 2.0, 3.0};
    result = batch_normalize(arena, v4, 3, 1);
    check(result[0] < result[1] && result[1] < result[2],
          "Ordering preserved after normalization");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
