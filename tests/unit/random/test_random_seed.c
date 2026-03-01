#include <stdio.h>
#include <stdlib.h>
#include "../../../include/random/random_seed.h"

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
    printf("=== Testing random_seed ===\n\n");

    // Test 1: Same seed produces same sequence
    random_seed(42);
    int a1 = rand();
    int a2 = rand();
    int a3 = rand();

    random_seed(42);
    int b1 = rand();
    int b2 = rand();
    int b3 = rand();

    check(a1 == b1 && a2 == b2 && a3 == b3, "Same seed produces same sequence");

    // Test 2: Different seeds produce different sequences
    random_seed(42);
    int c1 = rand();

    random_seed(99);
    int d1 = rand();

    check(c1 != d1, "Different seeds produce different first values");

    // Test 3: Seed of 0 works
    random_seed(0);
    int e1 = rand();
    random_seed(0);
    int e2 = rand();
    check(e1 == e2, "Seed of 0 is reproducible");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
