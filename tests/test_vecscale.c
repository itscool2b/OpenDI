#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg/vectors/vecscale.h"

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

    // Test 1: Basic scaling
    double v1[] = {1.0, 2.0, 3.0};
    double *result = vecscale(v1, 2.0, 3);
    check(result != NULL, "Basic scaling: returns non-null pointer");
    check(fabs(result[0] - 2.0) < EPSILON && 
          fabs(result[1] - 4.0) < EPSILON && 
          fabs(result[2] - 6.0) < EPSILON, "Basic scaling by 2");
    free(result);

    // Test 2: Scale by 1 (identity)
    double v2[] = {5.0, 10.0, 15.0};
    result = vecscale(v2, 1.0, 3);
    check(fabs(result[0] - 5.0) < EPSILON && 
          fabs(result[1] - 10.0) < EPSILON && 
          fabs(result[2] - 15.0) < EPSILON, "Scale by 1 (identity)");
    free(result);

    // Test 3: Scale by 0 (zero vector)
    double v3[] = {5.0, 10.0, 15.0};
    result = vecscale(v3, 0.0, 3);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "Scale by 0 (zero vector)");
    free(result);

    // Test 4: Scale by -1 (negation)
    double v4[] = {1.0, -2.0, 3.0};
    result = vecscale(v4, -1.0, 3);
    check(fabs(result[0] + 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] + 3.0) < EPSILON, "Scale by -1 (negation)");
    free(result);

    // Test 5: Single element
    double v5[] = {5.0};
    result = vecscale(v5, 3.0, 1);
    check(fabs(result[0] - 15.0) < EPSILON, "Single element scaling");
    free(result);

    // Test 6: Fractional scaling
    double v6[] = {10.0, 20.0, 30.0};
    result = vecscale(v6, 0.5, 3);
    check(fabs(result[0] - 5.0) < EPSILON && 
          fabs(result[1] - 10.0) < EPSILON && 
          fabs(result[2] - 15.0) < EPSILON, "Fractional scaling (0.5)");
    free(result);

    // Test 7: Large scalar
    double v7[] = {1.0, 2.0, 3.0};
    result = vecscale(v7, 1e10, 3);
    check(fabs(result[0] - 1e10) < EPSILON && 
          fabs(result[1] - 2e10) < EPSILON && 
          fabs(result[2] - 3e10) < EPSILON, "Large scalar scaling");
    free(result);

    // Test 8: Small scalar
    double v8[] = {1.0, 2.0, 3.0};
    result = vecscale(v8, 1e-10, 3);
    check(fabs(result[0] - 1e-10) < EPSILON && 
          fabs(result[1] - 2e-10) < EPSILON && 
          fabs(result[2] - 3e-10) < EPSILON, "Small scalar scaling");
    free(result);

    // Test 9: Associative property (a * (b * v) = (a * b) * v)
    double v9[] = {1.0, 2.0, 3.0};
    double *temp = vecscale(v9, 2.0, 3);
    double *result1 = vecscale(temp, 3.0, 3);
    free(temp);
    double *result2 = vecscale(v9, 6.0, 3);
    check(fabs(result1[0] - result2[0]) < EPSILON && 
          fabs(result1[1] - result2[1]) < EPSILON && 
          fabs(result1[2] - result2[2]) < EPSILON, "Associative property: a*(b*v) = (a*b)*v");
    free(result1);
    free(result2);

    // Test 10: Distributive over vector addition (scalar * (v1 + v2))
    double v10[] = {1.0, 2.0, 3.0};
    double v11[] = {4.0, 5.0, 6.0};
    // We'll manually compute: 2 * (v10 + v11)
    double expected[] = {10.0, 14.0, 18.0};  // 2 * (5, 7, 9)
    result = vecscale(v10, 2.0, 3);  // First scale v10
    // But we need 2*(v10+v11), so let's scale both and check manually
    double *r1 = vecscale(v10, 2.0, 3);
    double *r2 = vecscale(v11, 2.0, 3);
    check(fabs(r1[0] + r2[0] - expected[0]) < EPSILON && 
          fabs(r1[1] + r2[1] - expected[1]) < EPSILON && 
          fabs(r1[2] + r2[2] - expected[2]) < EPSILON, "Distributive: scalar * (v1 + v2) = scalar*v1 + scalar*v2");
    free(r1);
    free(r2);
    free(result);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
