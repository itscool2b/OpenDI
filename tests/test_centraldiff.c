#include <stdio.h>
#include <math.h>
#include "calculus/centraldiff.h"

// Test function: f(x) = x^2, f'(x) = 2x
double test_func1(double x) {
    return x * x;
}

// Test function: f(x) = sin(x), f'(x) = cos(x)
double test_func2(double x) {
    return sin(x);
}

// Test function: f(x) = 3x + 2, f'(x) = 3
double test_func3(double x) {
    return 3 * x + 2;
}

// Test function: f(x) = e^x, f'(x) = e^x
double test_func4(double x) {
    return exp(x);
}

int main() {
    printf("=== Testing central_difference ===\n");
    
    double h = 0.0001;
    
    // Test f(x) = x^2 at x = 3, expected f'(3) = 6
    double result1 = central_difference(test_func1, 3.0, h);
    printf("f(x)=x^2 at x=3: f'(3) ≈ %.6f (expected: ~6.00, error: %.6f)\n", 
           result1, fabs(result1 - 6.0));
    
    // Test f(x) = x^2 at x = 0, expected f'(0) = 0
    double result2 = central_difference(test_func1, 0.0, h);
    printf("f(x)=x^2 at x=0: f'(0) ≈ %.6f (expected: ~0.00, error: %.6f)\n", 
           result2, fabs(result2 - 0.0));
    
    // Test f(x) = sin(x) at x = 0, expected f'(0) = cos(0) = 1
    double result3 = central_difference(test_func2, 0.0, h);
    printf("f(x)=sin(x) at x=0: f'(0) ≈ %.6f (expected: ~1.00, error: %.6f)\n", 
           result3, fabs(result3 - 1.0));
    
    // Test f(x) = 3x + 2 at x = 5, expected f'(5) = 3 (linear should be exact)
    double result4 = central_difference(test_func3, 5.0, h);
    printf("f(x)=3x+2 at x=5: f'(5) ≈ %.6f (expected: ~3.00, error: %.6f)\n", 
           result4, fabs(result4 - 3.0));
    
    // Test f(x) = e^x at x = 1, expected f'(1) = e
    double result5 = central_difference(test_func4, 1.0, h);
    printf("f(x)=e^x at x=1: f'(1) ≈ %.6f (expected: ~%.6f, error: %.6f)\n", 
           result5, exp(1), fabs(result5 - exp(1)));
    
    // Test h = 0 edge case
    double result6 = central_difference(test_func1, 3.0, 0.0);
    printf("h=0 edge case: result = %.2f (expected: 0.00)\n", result6);
    
    return 0;
}
