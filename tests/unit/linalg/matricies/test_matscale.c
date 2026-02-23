#include <stdio.h>
#include <math.h>
#include "../../../../include/linalg/matricies/matscale.h"
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
    printf("=== Testing matscale ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic 2x2 scaling
    double a[] = {1.0, 2.0, 3.0, 4.0};  // 2x2 matrix
    double *result = matscale(arena, a, 2.0, 2, 2);
    check(fabs(result[0] - 2.0) < EPSILON && 
          fabs(result[1] - 4.0) < EPSILON && 
          fabs(result[2] - 6.0) < EPSILON && 
          fabs(result[3] - 8.0) < EPSILON, 
          "Basic 2x2 matrix scaling");

    // Test 2: Scale by 1 (identity)
    arena_clear(arena);
    result = matscale(arena, a, 1.0, 2, 2);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 3.0) < EPSILON && 
          fabs(result[3] - 4.0) < EPSILON, 
          "Scale by 1 (identity)");

    // Test 3: Scale by 0
    arena_clear(arena);
    result = matscale(arena, a, 0.0, 2, 2);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON && 
          fabs(result[3]) < EPSILON, 
          "Scale by 0 (zero matrix)");

    // Test 4: Scale by negative
    arena_clear(arena);
    result = matscale(arena, a, -1.0, 2, 2);
    check(fabs(result[0] + 1.0) < EPSILON && 
          fabs(result[1] + 2.0) < EPSILON && 
          fabs(result[2] + 3.0) < EPSILON && 
          fabs(result[3] + 4.0) < EPSILON, 
          "Scale by -1 (negation)");

    // Test 5: 3x3 matrix
    arena_clear(arena);
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    result = matscale(arena, b, 0.5, 3, 3);
    check(fabs(result[4] - 2.5) < EPSILON && 
          fabs(result[8] - 4.5) < EPSILON, 
          "3x3 matrix scaling");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
