#include <stdio.h>
#include <math.h>
#include "../../../include/random/random_normal.h"
#include "../../../include/random/random_seed.h"
#include "../../../include/arena.h"

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
    printf("=== Testing random_normal ===\n\n");

    Arena *arena = arena_create(65536);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Mean is approximately correct (large sample)
    random_seed(42);
    int n = 1000;
    double *result = random_normal(arena, 0.0, 1.0, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += result[i];
    }
    double mean = sum / n;
    check(fabs(mean) < 0.1, "Mean of N(0,1) sample is near 0");

    // Test 2: Standard deviation is approximately correct
    double var_sum = 0.0;
    for (int i = 0; i < n; i++) {
        var_sum += (result[i] - mean) * (result[i] - mean);
    }
    double stddev = sqrt(var_sum / n);
    check(fabs(stddev - 1.0) < 0.15, "Stddev of N(0,1) sample is near 1");

    arena_clear(arena);

    // Test 3: Custom mean and std
    random_seed(42);
    result = random_normal(arena, 5.0, 2.0, n);
    sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += result[i];
    }
    mean = sum / n;
    check(fabs(mean - 5.0) < 0.2, "Mean of N(5,2) sample is near 5");

    arena_clear(arena);

    // Test 4: Reproducibility
    random_seed(42);
    double *r1 = random_normal(arena, 0.0, 1.0, 5);
    double saved[5];
    for (int i = 0; i < 5; i++) saved[i] = r1[i];

    arena_clear(arena);

    random_seed(42);
    double *r2 = random_normal(arena, 0.0, 1.0, 5);
    int same = 1;
    for (int i = 0; i < 5; i++) {
        if (fabs(saved[i] - r2[i]) > 1e-15) {
            same = 0;
            break;
        }
    }
    check(same, "Same seed produces same values");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
