#include <stdio.h>
#include <math.h>
#include "../../../include/loss/mse_loss.h"

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
    printf("=== Testing mse_loss ===\n\n");

    // Test 1: Perfect predictions (zero loss)
    double pred1[] = {1.0, 2.0, 3.0};
    double targ1[] = {1.0, 2.0, 3.0};
    double result = mse_loss(pred1, targ1, 3);
    check(fabs(result - 0.0) < EPSILON, "Perfect predictions give zero loss");

    // Test 2: Known MSE value
    double pred2[] = {1.0, 2.0, 3.0};
    double targ2[] = {1.5, 2.5, 3.5};
    result = mse_loss(pred2, targ2, 3);
    // Each diff is 0.5, squared is 0.25, sum is 0.75, mean is 0.25
    check(fabs(result - 0.25) < EPSILON, "Known MSE: (0.25+0.25+0.25)/3 = 0.25");

    // Test 3: Single element
    double pred3[] = {3.0};
    double targ3[] = {1.0};
    result = mse_loss(pred3, targ3, 1);
    // diff=2, squared=4, mean=4
    check(fabs(result - 4.0) < EPSILON, "Single element: (3-1)^2 = 4");

    // Test 4: Negative values
    double pred4[] = {-1.0, -2.0};
    double targ4[] = {1.0, 2.0};
    result = mse_loss(pred4, targ4, 2);
    // diffs: -2, -4; squared: 4, 16; sum: 20; mean: 10
    check(fabs(result - 10.0) < EPSILON, "Negative values: MSE = 10.0");

    // Test 5: Symmetry (swapping pred and target gives same result)
    double pred5[] = {1.0, 5.0};
    double targ5[] = {3.0, 2.0};
    double r1 = mse_loss(pred5, targ5, 2);
    double r2 = mse_loss(targ5, pred5, 2);
    check(fabs(r1 - r2) < EPSILON, "Symmetric: mse(a,b) == mse(b,a)");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
