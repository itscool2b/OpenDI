/*
 * Test that the master header opendi.h includes everything correctly
 */

#include "opendi.h"
#include <stdio.h>

int main() {
    printf("Testing master header opendi.h\n");
    printf("==============================\n\n");
    
    // Create arena for vector operations
    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }
    
    // Test primitive operations
    double sum = add_numbers(3, 1.0, 2.0, 3.0);
    printf("add_numbers(1, 2, 3) = %.1f\n", sum);
    
    double product = multiply_numbers(2, 5.0, 4.0);
    printf("multiply_numbers(5, 4) = %.1f\n", product);
    
    float abs_val = absolute(-42.0f);
    printf("absolute(-42) = %.1f\n", abs_val);
    
    // Test calculus
    double f(double x) { return x * x; }
    double deriv = central_difference(f, 3.0, 0.0001);
    printf("derivative of x^2 at x=3: %.4f\n", deriv);
    
    // Test vectors with arena
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    
    double *vec_sum = vecadd(arena, a, b, 3);
    printf("vecadd: [%.1f, %.1f, %.1f]\n", vec_sum[0], vec_sum[1], vec_sum[2]);
    
    double dot = vecdot(a, b, 3);
    printf("vecdot: %.1f\n", dot);
    
    double norm = vecnorm(a, 3);
    printf("vecnorm of a: %.4f\n", norm);
    
    arena_destroy(arena);
    
    printf("\nMaster header opendi.h works correctly!\n");
    printf("All functions accessible from single include.\n");
    
    return 0;
}
