#include <stdio.h>
#include <math.h>
#include "../../../../include/linalg/vectors/vecscale.h"
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
    printf("=== Testing vecscale ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic scaling
    double v1[] = {1.0, 2.0, 3.0};
    double *result = vecscale(arena, v1, 2.0, 3);
    check(result != NULL, "Basic scaling: returns non-null pointer");
    check(fabs(result[0] - 2.0) < EPSILON && 
          fabs(result[1] - 4.0) < EPSILON && 
          fabs(result[2] - 6.0) < EPSILON, "Basic scaling by 2");

    // Test 2: Scale by 1 (identity)
    double v2[] = {5.0, 10.0, 15.0};
    result = vecscale(arena, v2, 1.0, 3);
    check(fabs(result[0] - 5.0) < EPSILON && 
          fabs(result[1] - 10.0) < EPSILON && 
          fabs(result[2] - 15.0) < EPSILON, "Scale by 1 (identity)");

    // Test 3: Scale by 0 (zero vector)
    double v3[] = {5.0, 10.0, 15.0};
    result = vecscale(arena, v3, 0.0, 3);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "Scale by 0 (zero vector)");

    // Test 4: Scale by -1 (negation)
    double v4[] = {1.0, -2.0, 3.0};
    result = vecscale(arena, v4, -1.0, 3);
    check(fabs(result[0] + 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] + 3.0) < EPSILON, "Scale by -1 (negation)");

    // Test 5: Single element
    double v5[] = {5.0};
    result = vecscale(arena, v5, 3.0, 1);
    check(fabs(result[0] - 15.0) < EPSILON, "Single element scaling");

    // Test 6: Fractional scaling
    double v6[] = {10.0, 20.0, 30.0};
    result = vecscale(arena, v6, 0.5, 3);
    check(fabs(result[0] - 5.0) < EPSILON && 
          fabs(result[1] - 10.0) < EPSILON && 
          fabs(result[2] - 15.0) < EPSILON, "Fractional scaling (0.5)");

    // Test 7: Large scalar
    double v7[] = {1.0, 2.0, 3.0};
    result = vecscale(arena, v7, 1e10, 3);
    check(fabs(result[0] - 1e10) < EPSILON && 
          fabs(result[1] - 2e10) < EPSILON && 
          fabs(result[2] - 3e10) < EPSILON, "Large scalar scaling");

    // Test 8: Small scalar
    double v8[] = {1.0, 2.0, 3.0};
    result = vecscale(arena, v8, 1e-10, 3);
    check(fabs(result[0] - 1e-10) < EPSILON && 
          fabs(result[1] - 2e-10) < EPSILON && 
          fabs(result[2] - 3e-10) < EPSILON, "Small scalar scaling");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
