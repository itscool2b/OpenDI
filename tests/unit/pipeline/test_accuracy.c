#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/accuracy.h"

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
    printf("=== Testing accuracy ===\n\n");

    // Test 1: Binary classification - all correct
    double pred1[] = {0.9, 0.1, 0.8};
    int labels1[] = {1, 0, 1};
    double acc = accuracy(pred1, labels1, 3, 1);
    check(fabs(acc - 1.0) < EPSILON, "Binary: all correct gives 1.0");

    // Test 2: Binary classification - some wrong
    double pred2[] = {0.9, 0.3, 0.8, 0.4};
    int labels2[] = {1, 0, 1, 1};
    acc = accuracy(pred2, labels2, 4, 1);
    check(fabs(acc - 0.75) < EPSILON, "Binary: 3/4 correct gives 0.75");

    // Test 3: Multiclass - all correct
    double pred3[] = {0.1, 0.8, 0.1,
                      0.9, 0.05, 0.05};
    int labels3[] = {1, 0};
    acc = accuracy(pred3, labels3, 2, 3);
    check(fabs(acc - 1.0) < EPSILON, "Multiclass: all correct gives 1.0");

    // Test 4: Multiclass - some wrong
    double pred4[] = {0.1, 0.8, 0.1,
                      0.1, 0.8, 0.1};
    int labels4[] = {1, 2};
    acc = accuracy(pred4, labels4, 2, 3);
    check(fabs(acc - 0.5) < EPSILON, "Multiclass: 1/2 correct gives 0.5");

    // Test 5: Binary threshold at 0.5
    double pred5[] = {0.5, 0.49};
    int labels5[] = {1, 0};
    acc = accuracy(pred5, labels5, 2, 1);
    check(fabs(acc - 1.0) < EPSILON, "Binary: 0.5 maps to class 1");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
