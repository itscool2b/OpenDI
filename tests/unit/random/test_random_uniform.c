#include <stdio.h>
#include <math.h>
#include "../../../include/random/random_uniform.h"
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
    printf("=== Testing random_uniform ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: All values in [0, 1]
    random_seed(42);
    double *result = random_uniform(arena, 0.0, 1.0, 100);
    int all_in_range = 1;
    for (int i = 0; i < 100; i++) {
        if (result[i] < 0.0 || result[i] > 1.0) {
            all_in_range = 0;
            break;
        }
    }
    check(all_in_range, "All values in [0, 1]");

    arena_clear(arena);

    // Test 2: Custom range [-5, 5]
    random_seed(42);
    result = random_uniform(arena, -5.0, 5.0, 100);
    all_in_range = 1;
    for (int i = 0; i < 100; i++) {
        if (result[i] < -5.0 || result[i] > 5.0) {
            all_in_range = 0;
            break;
        }
    }
    check(all_in_range, "All values in [-5, 5]");

    arena_clear(arena);

    // Test 3: Single element
    random_seed(42);
    result = random_uniform(arena, 0.0, 1.0, 1);
    check(result[0] >= 0.0 && result[0] <= 1.0, "Single element in range");

    arena_clear(arena);

    // Test 4: Reproducibility with same seed
    random_seed(42);
    double *r1 = random_uniform(arena, 0.0, 1.0, 5);
    double saved[5];
    for (int i = 0; i < 5; i++) saved[i] = r1[i];

    arena_clear(arena);

    random_seed(42);
    double *r2 = random_uniform(arena, 0.0, 1.0, 5);
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
