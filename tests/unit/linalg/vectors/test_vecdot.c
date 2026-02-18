#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../../../../include/linalg/vectors/vecdot.h"

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
    printf("=== Testing vecdot ===\n\n");

    // Test 1: Basic dot product
    double v1[] = {1.0, 2.0, 3.0};
    double v2[] = {4.0, 5.0, 6.0};
    double result = vecdot(v1, v2, 3);
    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    check(fabs(result - 32.0) < EPSILON, "Basic dot product");

    // Test 2: Dot product with zeros
    double v3[] = {0.0, 0.0, 0.0};
    double v4[] = {1.0, 2.0, 3.0};
    result = vecdot(v3, v4, 3);
    check(fabs(result) < EPSILON, "Dot product with zero vector");

    // Test 3: Dot product of same vector (should be sum of squares)
    double v5[] = {3.0, 4.0};
    result = vecdot(v5, v5, 2);
    // 3*3 + 4*4 = 9 + 16 = 25
    check(fabs(result - 25.0) < EPSILON, "Dot product of vector with itself");

    // Test 4: Single element
    double v6[] = {5.0};
    double v7[] = {3.0};
    result = vecdot(v6, v7, 1);
    check(fabs(result - 15.0) < EPSILON, "Single element dot product");

    // Test 5: Perpendicular vectors (should be 0)
    double v8[] = {1.0, 0.0, 0.0};  // i
    double v9[] = {0.0, 1.0, 0.0};  // j
    result = vecdot(v8, v9, 3);
    check(fabs(result) < EPSILON, "Perpendicular vectors (i . j = 0)");

    // Test 6: Negative values
    double v10[] = {-1.0, -2.0, -3.0};
    double v11[] = {1.0, 2.0, 3.0};
    result = vecdot(v10, v11, 3);
    // -1 - 4 - 9 = -14
    check(fabs(result + 14.0) < EPSILON, "Dot product with negatives");

    // Test 7: Large values
    double v12[] = {1e5, 1e5, 1e5};
    double v13[] = {1e5, 1e5, 1e5};
    result = vecdot(v12, v13, 3);
    // 1e10 + 1e10 + 1e10 = 3e10
    check(fabs(result - 3e10) < EPSILON, "Large values dot product");

    // Test 8: Small values
    double v14[] = {1e-5, 1e-5, 1e-5};
    double v15[] = {1e-5, 1e-5, 1e-5};
    result = vecdot(v14, v15, 3);
    check(fabs(result - 3e-10) < EPSILON, "Small values dot product");

    // Test 9: Commutative property (a . b = b . a)
    double v16[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double v17[] = {5.0, 4.0, 3.0, 2.0, 1.0};
    double r1 = vecdot(v16, v17, 5);
    double r2 = vecdot(v17, v16, 5);
    check(fabs(r1 - r2) < EPSILON, "Commutative property");

    // Test 10: Distributive property (a . (b + c) = a . b + a . c)
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double c[] = {7.0, 8.0, 9.0};
    double b_plus_c[] = {11.0, 13.0, 15.0};
    double left = vecdot(a, b_plus_c, 3);
    double right = vecdot(a, b, 3) + vecdot(a, c, 3);
    check(fabs(left - right) < EPSILON, "Distributive property");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
