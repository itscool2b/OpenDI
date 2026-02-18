#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg/vectors/veccross.h"

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
    printf("=== Testing veccross ===\n\n");

    // Test 1: Basic cross product (i x j = k)
    double v1[] = {1.0, 0.0, 0.0};  // i
    double v2[] = {0.0, 1.0, 0.0};  // j
    double *result = veccross(v1, v2);
    check(result != NULL, "Basic cross product: returns non-null pointer");
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2] - 1.0) < EPSILON, "i x j = k");
    free(result);

    // Test 2: Anti-commutative property (j x i = -k)
    result = veccross(v2, v1);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2] + 1.0) < EPSILON, "j x i = -k (anti-commutative)");
    free(result);

    // Test 3: Cross product of same vector (should be zero)
    double v3[] = {1.0, 2.0, 3.0};
    result = veccross(v3, v3);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "v x v = 0");
    free(result);

    // Test 4: j x k = i
    double v4[] = {0.0, 1.0, 0.0};  // j
    double v5[] = {0.0, 0.0, 1.0};  // k
    result = veccross(v4, v5);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "j x k = i");
    free(result);

    // Test 5: k x i = j
    double v6[] = {0.0, 0.0, 1.0};  // k
    double v7[] = {1.0, 0.0, 0.0};  // i
    result = veccross(v6, v7);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1] - 1.0) < EPSILON && 
          fabs(result[2]) < EPSILON, "k x i = j");
    free(result);

    // Test 6: Arbitrary vectors
    double v8[] = {1.0, 2.0, 3.0};
    double v9[] = {4.0, 5.0, 6.0};
    result = veccross(v8, v9);
    // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (-3, 6, -3)
    check(fabs(result[0] + 3.0) < EPSILON && 
          fabs(result[1] - 6.0) < EPSILON && 
          fabs(result[2] + 3.0) < EPSILON, "Arbitrary vectors cross product");
    free(result);

    // Test 7: Zero vector cross product
    double v10[] = {0.0, 0.0, 0.0};
    double v11[] = {1.0, 2.0, 3.0};
    result = veccross(v10, v11);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "0 x v = 0");
    free(result);

    // Test 8: Negative values
    double v12[] = {-1.0, -2.0, -3.0};
    double v13[] = {1.0, 2.0, 3.0};
    result = veccross(v12, v13);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "(-v) x v = 0");
    free(result);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
