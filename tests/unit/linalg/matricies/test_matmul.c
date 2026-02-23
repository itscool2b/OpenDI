#include <stdio.h>
#include <math.h>
#include "../../../../include/linalg/matricies/matmul.h"
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
    printf("=== Testing matmul ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: 2x2 * 2x2 = 2x2
    double a[] = {1.0, 2.0, 3.0, 4.0};  // 2x2
    double b[] = {5.0, 6.0, 7.0, 8.0};  // 2x2
    // Result should be: [19, 22, 43, 50]
    double *result = matmul(arena, a, b, 2, 2, 2);
    check(fabs(result[0] - 19.0) < EPSILON && 
          fabs(result[1] - 22.0) < EPSILON && 
          fabs(result[2] - 43.0) < EPSILON && 
          fabs(result[3] - 50.0) < EPSILON, 
          "Basic 2x2 matrix multiplication");

    // Test 2: Identity matrix
    arena_clear(arena);
    double identity[] = {1.0, 0.0, 0.0, 1.0};
    result = matmul(arena, a, identity, 2, 2, 2);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 3.0) < EPSILON && 
          fabs(result[3] - 4.0) < EPSILON, 
          "Multiplication by identity");

    // Test 3: Zero matrix
    arena_clear(arena);
    double zeros[] = {0.0, 0.0, 0.0, 0.0};
    result = matmul(arena, a, zeros, 2, 2, 2);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON && 
          fabs(result[3]) < EPSILON, 
          "Multiplication by zero matrix");

    // Test 4: 2x3 * 3x2 = 2x2
    arena_clear(arena);
    double c[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};  // 2x3
    double d[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};  // 3x2
    // Result: [58, 64, 139, 154]
    result = matmul(arena, c, d, 2, 3, 2);
    check(fabs(result[0] - 58.0) < EPSILON && 
          fabs(result[1] - 64.0) < EPSILON && 
          fabs(result[2] - 139.0) < EPSILON && 
          fabs(result[3] - 154.0) < EPSILON, 
          "2x3 * 3x2 matrix multiplication");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
